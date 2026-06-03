#include <android/view/DisplayEventReceiver.h>

#ifdef HOST_BUILD
#include <android_mock/ui/DisplayEventReceiver.h>
#endif

#include <cstring>
#include <stdexcept>

namespace android::view {

// ============================================================================
// NativeReceiver — on-device (libui) or host (mock) implementation
// ============================================================================

#ifdef HOST_BUILD

struct DisplayEventReceiver::NativeReceiver {
    std::unique_ptr<ui::MockDisplayEventReceiver> m_mock;

    NativeReceiver()
        : m_mock(std::make_unique<ui::MockDisplayEventReceiver>()) {
        if (!m_mock->isValid()) {
            throw std::runtime_error("DisplayEventReceiver: failed to create mock socket pair");
        }
    }

    auto getFd() const -> int {
        return m_mock->getFd();
    }

    void requestVsync() {
        // No-op on mock: VSync events are injected by tests via write_vsync_event()
    }

    void close() {
        m_mock->close();
    }

    auto isValid() const -> bool {
        return m_mock->isValid();
    }
};

#else

// On-device: forward to real libui DisplayEventReceiver
#include <ui/DisplayEventReceiver.h>

struct DisplayEventReceiver::NativeReceiver {
    android::DisplayEventReceiver m_native;

    NativeReceiver() : m_native() {}

    auto getFd() const -> int {
        return m_native.getFd();
    }

    void requestVsync() {
        m_native.requestVsync();
    }

    void close() {
        m_native.close();
    }

    auto isValid() const -> bool {
        return true; // Real receiver is always valid if constructed
    }
};

#endif

// ============================================================================
// DisplayEventReceiver implementation
// ============================================================================

DisplayEventReceiver::DisplayEventReceiver(std::shared_ptr<os::Looper> looper,
                                           VsyncCallback callback)
    : m_looper_(std::move(looper))
    , m_vsync_callback_(std::move(callback))
    , m_fd_watcher_cookie_(0)
    , m_fd_(-1)
    , m_frame_interval_nanos_(16666667) // 60Hz default
{
    if (!m_looper_) {
        throw std::runtime_error("DisplayEventReceiver: looper must not be null");
    }

    m_native_ = std::make_unique<NativeReceiver>();
    if (!m_native_->isValid()) {
        throw std::runtime_error("DisplayEventReceiver: native receiver initialization failed");
    }

    m_fd_ = m_native_->getFd();
}

DisplayEventReceiver::~DisplayEventReceiver() {
    dispose();
}

DisplayEventReceiver::DisplayEventReceiver(DisplayEventReceiver&& other) noexcept
    : m_looper_(std::move(other.m_looper_))
    , m_vsync_callback_(std::move(other.m_vsync_callback_))
    , m_native_(std::move(other.m_native_))
    , m_disposed_(other.m_disposed_)
    , m_fd_watcher_registered_(other.m_fd_watcher_registered_)
    , m_fd_watcher_cookie_(other.m_fd_watcher_cookie_)
    , m_fd_(other.m_fd_)
    , m_frame_interval_nanos_(other.m_frame_interval_nanos_) {
    other.m_fd_ = -1;
    other.m_fd_watcher_cookie_ = 0;
    other.m_fd_watcher_registered_ = false;
}

DisplayEventReceiver& DisplayEventReceiver::operator=(DisplayEventReceiver&& other) noexcept {
    if (this != &other) {
        dispose(); // Clean up current state

        m_looper_ = std::move(other.m_looper_);
        m_vsync_callback_ = std::move(other.m_vsync_callback_);
        m_native_ = std::move(other.m_native_);
        m_disposed_ = other.m_disposed_;
        m_fd_watcher_registered_ = other.m_fd_watcher_registered_;
        m_fd_watcher_cookie_ = other.m_fd_watcher_cookie_;
        m_fd_ = other.m_fd_;
        m_frame_interval_nanos_ = other.m_frame_interval_nanos_;

        other.m_fd_ = -1;
        other.m_fd_watcher_cookie_ = 0;
        other.m_fd_watcher_registered_ = false;
    }
    return *this;
}

void DisplayEventReceiver::schedule_vsync() {
    if (m_disposed_) return;
    if (m_native_) {
        m_native_->requestVsync();
    }
}

void DisplayEventReceiver::dispose() {
    if (m_disposed_) return;
    m_disposed_ = true;

    unregister_from_looper();

    if (m_native_) {
        m_native_->close();
        m_native_.reset();
    }

    m_fd_ = -1;
    m_vsync_callback_ = nullptr;
}

auto DisplayEventReceiver::is_disposed() const -> bool {
    return m_disposed_;
}

void DisplayEventReceiver::register_with_looper() {
    if (m_disposed_ || m_fd_watcher_registered_ || m_fd_ < 0) return;

    m_fd_watcher_registered_ = true;
    m_fd_watcher_cookie_ = m_looper_->add_fd(
        m_fd_,
        1, // ALOOPER_EVENT_INPUT = 1
        [=](int /*fd*/, int /*events*/, void* data) -> int {
            auto* self = static_cast<DisplayEventReceiver*>(data);
            self->on_data_available();
            return 1; // Continue watching
        },
        this
    );

    if (m_fd_watcher_cookie_ == 0) {
        m_fd_watcher_registered_ = false;
    }
}

void DisplayEventReceiver::unregister_from_looper() {
    if (!m_fd_watcher_registered_ || m_fd_watcher_cookie_ == 0) return;

    m_looper_->remove_fd(m_fd_watcher_cookie_);
    m_fd_watcher_registered_ = false;
    m_fd_watcher_cookie_ = 0;
}

auto DisplayEventReceiver::get_looper() const -> std::shared_ptr<os::Looper> {
    return m_looper_;
}

auto DisplayEventReceiver::get_frame_interval_nanos() const -> int64_t {
    return m_frame_interval_nanos_;
}

void DisplayEventReceiver::set_vsync_callback(VsyncCallback callback) {
    m_vsync_callback_ = std::move(callback);
}

void DisplayEventReceiver::on_data_available() {
    if (m_disposed_) return;
    dispatch_events();
}

void DisplayEventReceiver::dispatch_events() {
    if (m_disposed_ || !m_native_) return;

    // Read raw event data from the native receiver's FD.
    // On host builds, this reads from the mock's socket pair.
    // On-device, this reads from the libui pipe.
    //
    // The wire format is DisplayEvent (type + union payload).
    // We only handle VSYNC events in MVP; other types are silently ignored.

    ui::DisplayEvent event{};
    ssize_t n = 0;

#ifdef HOST_BUILD
    // Mock: read from the socket pair
    n = ::read(m_fd_, &event, sizeof(event));
#else
    // On-device: read from libui's pipe
    // The real android::DisplayEventReceiver uses an Event union with the same layout
    n = ::read(m_fd_, &event, sizeof(event));
#endif

    if (n < static_cast<ssize_t>(sizeof(ui::DisplayEventType))) {
        // Incomplete or error — ignore
        return;
    }

    if (event.type == ui::DisplayEventType::VSYNC && m_vsync_callback_) {
        VsyncEventData vsync_data{event.vsync.timestamp, event.vsync.count, event.vsync.vsync_id};
        m_vsync_callback_(vsync_data);
    }
    // HOTPLUG and other types are ignored in MVP
}

} // namespace android::view
