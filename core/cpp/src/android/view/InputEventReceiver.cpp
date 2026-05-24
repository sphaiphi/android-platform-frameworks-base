#define _GNU_SOURCE
#include <android/view/InputEventReceiver.h>
#include <android/view/InputChannel.h>
#include <android/os/Looper.h>

#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>
#include <stdexcept>
#include <limits>

namespace android {
namespace view {

// ── Wire Protocol Constants ──

// Event type constants (matching Android InputEvent wire format)
static constexpr uint8_t WIRE_EVENT_TYPE_MOTION = 1;
static constexpr uint8_t WIRE_EVENT_TYPE_KEY    = 2;

// Wire protocol header: 19 bytes
//   [0..3]   uint32_t sequence_number
//   [4]      uint8_t  event_type
//   [5]      uint8_t  action
//   [6..9]   int32_t  device_id
//   [10..13] uint32_t source flags
//   [14]     uint8_t  history_size
//   [15..18] uint32_t pointer_count (MotionEvent only)
static constexpr size_t WIRE_HEADER_SIZE = 19;

// MotionEvent base payload (without per-pointer data)
static constexpr size_t WIRE_MOTION_BASE_SIZE = 48;
// KeyEvent payload
static constexpr size_t WIRE_KEY_BASE_SIZE = 24;
// Per-pointer data (x + y = 2 floats)
static constexpr size_t WIRE_POINTER_SIZE = 16;
// Per-history-entry size
static constexpr size_t WIRE_HISTORY_ENTRY_SIZE = 48;

// ── Constructor ──

InputEventReceiver::InputEventReceiver(std::shared_ptr<InputChannel> channel,
                                       std::shared_ptr<os::Looper> looper,
                                       InputEventCallback callback)
    : m_channel_(std::move(channel)),
      m_looper_(std::move(looper)),
      m_callback_(std::move(callback)) {
    if (!m_channel_ || !m_channel_->is_valid()) {
        throw std::invalid_argument("InputEventReceiver: InputChannel must be valid");
    }
    if (!m_looper_) {
        throw std::invalid_argument("InputEventReceiver: Looper must not be null");
    }
    if (!m_callback_) {
        throw std::invalid_argument("InputEventReceiver: callback must not be null");
    }
}

InputEventReceiver::~InputEventReceiver() {
    if (!m_disposed_) {
        dispose();
    }
}

InputEventReceiver::InputEventReceiver(InputEventReceiver&& other) noexcept
    : m_channel_(std::move(other.m_channel_)),
      m_looper_(std::move(other.m_looper_)),
      m_callback_(std::move(other.m_callback_)),
      m_current_event_(std::move(other.m_current_event_)),
      m_current_event_has_value_(other.m_current_event_has_value_),
      m_sequence_counter_(other.m_sequence_counter_),
      m_disposed_(other.m_disposed_),
      m_fd_watcher_registered_(other.m_fd_watcher_registered_),
      m_has_focus_(other.m_has_focus_),
      m_in_touch_mode_(other.m_in_touch_mode_),
      m_pointer_capture_enabled_(other.m_pointer_capture_enabled_) {
    other.m_current_event_has_value_ = false;
    other.m_sequence_counter_ = 0;
    other.m_disposed_ = true;
    other.m_fd_watcher_registered_ = false;
}

InputEventReceiver& InputEventReceiver::operator=(InputEventReceiver&& other) noexcept {
    if (this != &other) {
        if (!m_disposed_) {
            dispose();
        }
        m_channel_ = std::move(other.m_channel_);
        m_looper_ = std::move(other.m_looper_);
        m_callback_ = std::move(other.m_callback_);
        m_current_event_ = std::move(other.m_current_event_);
        m_current_event_has_value_ = other.m_current_event_has_value_;
        m_sequence_counter_ = other.m_sequence_counter_;
        m_disposed_ = other.m_disposed_;
        m_fd_watcher_registered_ = other.m_fd_watcher_registered_;
        m_has_focus_ = other.m_has_focus_;
        m_in_touch_mode_ = other.m_in_touch_mode_;
        m_pointer_capture_enabled_ = other.m_pointer_capture_enabled_;

        other.m_current_event_has_value_ = false;
        other.m_sequence_counter_ = 0;
        other.m_disposed_ = true;
        other.m_fd_watcher_registered_ = false;
    }
    return *this;
}

// ── Core Event Consumption ──

auto InputEventReceiver::consume_events() -> std::vector<InputEventWrapper> {
    if (m_disposed_) return {};

    std::vector<InputEventWrapper> events;
    int fd = m_channel_->read_fd();
    if (fd < 0) return {};

    // Read all available data from the socket
    constexpr size_t buffer_size = 4096;
    std::vector<uint8_t> buffer(buffer_size);

    ssize_t bytes_read = ::read(fd, buffer.data(), buffer_size);
    if (bytes_read <= 0) {
        return {};
    }

    // Parse events from the buffer
    size_t offset = 0;
    while (offset + WIRE_HEADER_SIZE <= static_cast<size_t>(bytes_read)) {
        // Read header fields
        uint32_t sequence_number = 0;
        uint8_t event_type = 0;
        int32_t device_id = 0;
        uint32_t source = 0;

        std::memcpy(&sequence_number, buffer.data() + offset, sizeof(uint32_t));
        std::memcpy(&event_type, buffer.data() + offset + 4, sizeof(uint8_t));
        std::memcpy(&device_id, buffer.data() + offset + 6, sizeof(int32_t));
        std::memcpy(&source, buffer.data() + offset + 10, sizeof(uint32_t));

        size_t header_end = offset + WIRE_HEADER_SIZE;

        if (header_end >= static_cast<size_t>(bytes_read)) {
            break; // Incomplete header
        }

        m_sequence_counter_ = sequence_number;

        if (event_type == WIRE_EVENT_TYPE_MOTION) {
            uint8_t history_size = 0;
            uint32_t pointer_count = 0;

            std::memcpy(&history_size, buffer.data() + offset + 14, sizeof(uint8_t));

            size_t pc_offset = offset + 15;
            if (pc_offset + sizeof(uint32_t) <= static_cast<size_t>(bytes_read)) {
                std::memcpy(&pointer_count, buffer.data() + pc_offset, sizeof(uint32_t));
            }

            size_t base_payload = WIRE_MOTION_BASE_SIZE;
            // Per-pointer data only for pointers beyond the first (x,y already in base)
            size_t pointer_data = (pointer_count > 0 ? pointer_count - 1 : 0) * WIRE_POINTER_SIZE;
            size_t history_data = history_size * WIRE_HISTORY_ENTRY_SIZE;
            size_t payload_size = base_payload + pointer_data + history_data;

            if (header_end + payload_size > static_cast<size_t>(bytes_read)) {
                break; // Incomplete event
            }

            auto motion_result = parse_motion_event(
                std::span(buffer).subspan(header_end),
                base_payload);
            if (motion_result) {
                InputEventWrapper wrapper;
                wrapper.event = *motion_result;
                wrapper.sequence_number = sequence_number;
                events.push_back(std::move(wrapper));
            }

            offset = header_end + payload_size;
        }
        else if (event_type == WIRE_EVENT_TYPE_KEY) {
            if (header_end + WIRE_KEY_BASE_SIZE > static_cast<size_t>(bytes_read)) {
                break; // Incomplete event
            }

            size_t key_offset = WIRE_KEY_BASE_SIZE;
            auto key_result = parse_key_event(
                std::span(buffer).subspan(header_end),
                key_offset);
            if (key_result) {
                InputEventWrapper wrapper;
                wrapper.event = *key_result;
                wrapper.sequence_number = sequence_number;
                events.push_back(std::move(wrapper));
            }

            offset = header_end + WIRE_KEY_BASE_SIZE;
        }
        else {
            break; // Unknown event type
        }
    }

    return events;
}

// ── Wire Protocol Parsers ──

auto InputEventReceiver::parse_motion_event(std::span<const uint8_t> data, size_t& offset)
    -> std::expected<MotionEvent, InputError> {
    if (data.size() < WIRE_MOTION_BASE_SIZE) {
        return std::unexpected(InputError::WIRE_FORMAT_ERROR);
    }

    size_t pos = 0;

    // Skip meta_state, button_state, edge_flags, mode (16 bytes)
    pos += 16;

    // event_time (int64_t)
    int64_t event_time = 0;
    std::memcpy(&event_time, data.data() + pos, sizeof(int64_t));
    pos += 8;
    (void)event_time;

    // x, y (pointer 0)
    float x = 0.f, y = 0.f;
    std::memcpy(&x, data.data() + pos, sizeof(float));
    pos += sizeof(float);
    std::memcpy(&y, data.data() + pos, sizeof(float));
    pos += sizeof(float);

    MotionEvent motion(MotionEvent::ACTION_DOWN, x, y);
    offset = pos;
    return motion;
}

auto InputEventReceiver::parse_key_event(std::span<const uint8_t> data, size_t& offset)
    -> std::expected<KeyEvent, InputError> {
    if (data.size() < WIRE_KEY_BASE_SIZE) {
        return std::unexpected(InputError::WIRE_FORMAT_ERROR);
    }

    size_t pos = 0;

    // Skip meta_state (4 bytes)
    pos += 4;

    // Skip repeat_count (4 bytes)
    pos += 4;

    // Skip device_id (4 bytes, already in header)
    pos += 4;

    // event_time (int64_t)
    pos += 8;

    // key_code (int32_t)
    int32_t key_code = 0;
    std::memcpy(&key_code, data.data() + pos, sizeof(int32_t));
    pos += sizeof(int32_t);

    KeyEvent key(KeyEvent::ACTION_DOWN, key_code);
    offset = pos;
    return key;
}

// ── Event Dispatch ──

void InputEventReceiver::dispatch_event(InputEventWrapper wrapper) {
    if (m_disposed_ || !m_callback_) return;

    m_current_event_ = std::move(wrapper);
    m_current_event_has_value_ = true;

    m_callback_(m_current_event_);
}

// ── Completion ──

auto InputEventReceiver::finish_input_event(bool handled) -> std::expected<void, InputError> {
    if (m_disposed_) {
        return std::unexpected(InputError::DISPOSED);
    }

    if (!m_current_event_has_value_) {
        return std::unexpected(InputError::NO_EVENT_IN_PROGRESS);
    }

    auto result = m_channel_->send_handled(handled);
    if (result < 0) {
        return std::unexpected(InputError::SOCKET_WRITE_ERROR);
    }

    // Reset current event
    m_current_event_has_value_ = false;
    m_current_event_ = InputEventWrapper();

    return std::expected<void, InputError>{};
}

// ── Disposal ──

void InputEventReceiver::dispose() {
    if (m_disposed_) return;

    m_disposed_ = true;
    m_current_event_has_value_ = false;
    m_callback_ = nullptr;

    unregister_from_looper();

    if (m_channel_) {
        m_channel_->close();
        m_channel_ = nullptr;
    }
}

auto InputEventReceiver::is_disposed() const -> bool {
    return m_disposed_;
}

// ── Batch Processing ──

auto InputEventReceiver::consume_batched_input_events() -> bool {
    if (m_disposed_) return false;

    auto events = consume_events();
    if (events.empty()) return false;

    for (auto& event : events) {
        dispatch_event(std::move(event));
    }

    return true;
}

// ── FD Polling ──

auto InputEventReceiver::probably_has_input() -> bool {
    if (m_disposed_) return false;

    int fd = m_channel_->read_fd();
    if (fd < 0) return false;

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;

    int ret = poll(&pfd, 1, 0); // timeout = 0 (non-blocking)
    if (ret > 0) {
        return (pfd.revents & POLLIN) != 0;
    }
    return false;
}

// ── Timeline (stub) ──

void InputEventReceiver::report_timeline(int64_t /*frame_time_nanos*/) {
    // No-op stub for input latency reporting
}

// ── Special Event Callbacks ──

void InputEventReceiver::on_focus_event(bool has_focus) {
    if (m_disposed_) return;
    m_has_focus_ = has_focus;
}

void InputEventReceiver::on_touch_mode_changed(bool in_touch_mode) {
    if (m_disposed_) return;
    m_in_touch_mode_ = in_touch_mode;
}

void InputEventReceiver::on_pointer_capture_event(bool enabled) {
    if (m_disposed_) return;
    m_pointer_capture_enabled_ = enabled;
}

auto InputEventReceiver::get_has_focus() const -> bool {
    return m_has_focus_;
}

auto InputEventReceiver::get_in_touch_mode() const -> bool {
    return m_in_touch_mode_;
}

auto InputEventReceiver::get_pointer_capture_enabled() const -> bool {
    return m_pointer_capture_enabled_;
}

// ── Looper Integration ──

void InputEventReceiver::register_with_looper() {
    if (m_disposed_ || m_fd_watcher_registered_ || !m_looper_ || !m_channel_) return;

    int fd = m_channel_->read_fd();
    if (fd < 0) return;

    // Store raw pointer to 'this' for the callback (caller ensures lifetime)
    InputEventReceiver* self = this;

    int cookie = m_looper_->add_fd(fd, POLLIN,
        [self](int, int, void*) -> int {
            auto events = self->consume_events();
            for (auto& event : events) {
                self->dispatch_event(std::move(event));
            }
            return 1; // consumed
        },
        this);

    if (cookie > 0) {
        m_fd_watcher_registered_ = true;
        m_fd_watcher_cookie_ = cookie;
    }
}

void InputEventReceiver::unregister_from_looper() {
    if (!m_fd_watcher_registered_ || !m_looper_) return;

    m_looper_->remove_fd(m_fd_watcher_cookie_);
    m_fd_watcher_registered_ = false;
    m_fd_watcher_cookie_ = 0;
}

// ── Accessors ──

auto InputEventReceiver::get_channel() const -> std::shared_ptr<InputChannel> {
    return m_channel_;
}

auto InputEventReceiver::get_looper() const -> std::shared_ptr<os::Looper> {
    return m_looper_;
}

} // namespace view
} // namespace android
