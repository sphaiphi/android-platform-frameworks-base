#include <android/view/Choreographer.h>
#include <android/os/Looper.h>

#include <chrono>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace android::view {

// ============================================================================
// Static helpers
// ============================================================================

auto Choreographer::system_time_nanos() -> int64_t {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()
    ).count();
}

// ============================================================================
// Constructor / Destructor
// ============================================================================

Choreographer::Choreographer(std::shared_ptr<DisplayEventReceiver> der)
    : m_display_event_receiver_(std::move(der))
    , m_last_frame_time_nanos_(0)
    , m_frame_pending_(false)
    , m_skipped_frames_(0)
    , m_next_callback_id_(1) {
    // Callback queues are default-constructed as empty vectors
}

Choreographer::~Choreographer() {
    // Dispose of the DisplayEventReceiver
    if (m_display_event_receiver_) {
        m_display_event_receiver_->dispose();
        m_display_event_receiver_.reset();
    }
}

Choreographer::Choreographer(Choreographer&& other) noexcept
    : m_display_event_receiver_(std::move(other.m_display_event_receiver_))
    , m_traverser_(std::move(other.m_traverser_))
    , m_last_frame_time_nanos_(other.m_last_frame_time_nanos_)
    , m_frame_pending_(other.m_frame_pending_)
    , m_skipped_frames_(other.m_skipped_frames_) {
    // Move callback queues
    for (int i = 0; i < static_cast<int>(CallbackType::COUNT); i++) {
        m_callback_queues_[i] = std::move(other.m_callback_queues_[i]);
    }
    other.m_last_frame_time_nanos_ = 0;
    other.m_frame_pending_ = false;
    other.m_skipped_frames_ = 0;
}

Choreographer& Choreographer::operator=(Choreographer&& other) noexcept {
    if (this != &other) {
        m_display_event_receiver_ = std::move(other.m_display_event_receiver_);
        m_traverser_ = std::move(other.m_traverser_);
        m_last_frame_time_nanos_ = other.m_last_frame_time_nanos_;
        m_frame_pending_ = other.m_frame_pending_;
        m_skipped_frames_ = other.m_skipped_frames_;
        for (int i = 0; i < static_cast<int>(CallbackType::COUNT); i++) {
            m_callback_queues_[i] = std::move(other.m_callback_queues_[i]);
        }
        other.m_last_frame_time_nanos_ = 0;
        other.m_frame_pending_ = false;
        other.m_skipped_frames_ = 0;
    }
    return *this;
}

// ============================================================================
// Factory methods
// ============================================================================

auto Choreographer::get_instance() -> std::shared_ptr<Choreographer> {
    if (s_thread_instance == nullptr) {
        auto looper = os::Looper::my_looper();
        if (!looper) {
            throw std::runtime_error("Choreographer: no Looper on this thread");
        }

        // Create the VSync callback lambda first (before DisplayEventReceiver can fire)
        DisplayEventReceiver::VsyncCallback vsync_cb =
            [self = std::shared_ptr<Choreographer>()](const VsyncEventData& data) {
                if (self) self->on_vsync(data);
            };

        // Create DisplayEventReceiver with the callback ready
        auto der = std::make_shared<DisplayEventReceiver>(looper, std::move(vsync_cb));

        // Create Choreographer and wire the receiver
        s_thread_instance = std::make_shared<Choreographer>(std::move(der));

        // Register with Looper (callback is already set, safe to receive events)
        s_thread_instance->m_display_event_receiver_->register_with_looper();

        if (os::Looper::get_main_looper() == looper) {
            s_main_instance = s_thread_instance;
        }
    }
    return s_thread_instance;
}

auto Choreographer::get_main_instance() -> std::shared_ptr<Choreographer> {
    return s_main_instance;
}

// ============================================================================
// Callback posting
// ============================================================================

uint64_t Choreographer::post_frame_callback(FrameCallback cb) {
    return post_frame_callback_delayed(std::move(cb), 0);
}

uint64_t Choreographer::post_frame_callback_delayed(FrameCallback cb, int64_t delay_ms) {
    int64_t due_time = system_time_nanos() + (delay_ms * 1000000LL);
    uint64_t id = m_next_callback_id_++;

    CallbackEntry entry{id, due_time, std::move(cb)};

    // Insert into TRAVERSAL queue using sorted insertion (lower_bound)
    auto& queue = m_callback_queues_[static_cast<int>(CallbackType::TRAVERSAL)];
    auto it = std::lower_bound(queue.begin(), queue.end(), entry,
        [](const CallbackEntry& a, const CallbackEntry& b) {
            return a.due_time < b.due_time;
        });
    queue.insert(it, std::move(entry));

    // Schedule a frame if not already pending
    if (!m_frame_pending_) {
        schedule_frame();
    }

    return id;
}

void Choreographer::remove_frame_callback(uint64_t id) {
    // Search all queues and remove matching callback by ID
    for (int i = 0; i < static_cast<int>(CallbackType::COUNT); i++) {
        auto& queue = m_callback_queues_[i];
        auto it = std::find_if(queue.begin(), queue.end(),
            [id](const CallbackEntry& entry) {
                return entry.id == id;
            });
        if (it != queue.end()) {
            queue.erase(it);
            break;
        }
    }
}

// ============================================================================
// Traverser
// ============================================================================

void Choreographer::set_traverser(TraverserCallback traverser) {
    m_traverser_ = std::move(traverser);
}

void Choreographer::remove_traverser() {
    m_traverser_ = nullptr;
}

// ============================================================================
// Frame scheduling
// ============================================================================

void Choreographer::schedule_frame() {
    m_frame_pending_ = true;
    schedule_vsync_locked();
}

void Choreographer::schedule_vsync_locked() {
    if (m_display_event_receiver_) {
        m_display_event_receiver_->schedule_vsync();
    }
}

auto Choreographer::has_pending_frame() const -> bool {
    return m_frame_pending_;
}

// ============================================================================
// VSync handling
// ============================================================================

void Choreographer::on_vsync(const VsyncEventData& data) {
    if (m_frame_pending_) {
        // Frame already pending — this is a late VSync.
        // The pending frame will handle the timing.
        return;
    }

    // Check for backward frame time (system clock adjustment)
    int64_t frameTime = static_cast<int64_t>(data.timestamp);
    if (m_last_frame_time_nanos_ > 0 && frameTime < m_last_frame_time_nanos_) {
        // Backward frame time: skip this frame and request next VSync
        m_frame_pending_ = false;
        schedule_vsync_locked();
        return;
    }

    do_frame(frameTime);
}

// ============================================================================
// Frame execution
// ============================================================================

void Choreographer::do_frame(int64_t frameTimeNanos) {
    m_frame_pending_ = false;

    // Jitter handling: resync to nearest past VSync if we're late
    if (m_last_frame_time_nanos_ > 0) {
        int64_t delta = frameTimeNanos - m_last_frame_time_nanos_;
        if (delta >= kFrameIntervalNanos) {
            // We're at least one frame interval late — resync
            m_last_frame_time_nanos_ = frameTimeNanos - (delta % kFrameIntervalNanos);
        }

        // Count skipped frames
        int64_t skipped = delta / kFrameIntervalNanos - 1;
        if (skipped > 0) {
            m_skipped_frames_ += static_cast<int>(skipped);
            if (m_skipped_frames_ >= kSkippedFrameWarningLimit) {
                // Log warning for excessive frame skips
                // In MVP: use cerr as a simple log proxy
                // TODO: Replace with android/log.h in production
                std::cerr << "Choreographer: Skipped " << m_skipped_frames_
                          << " frames!" << std::endl;
            }
        } else {
            m_skipped_frames_ = 0;
        }
    }

    m_last_frame_time_nanos_ = frameTimeNanos;

    // Execute callbacks in stage order: INPUT -> ANIMATION -> TRAVERSAL -> COMMIT
    // (INSETS_ANIMATION is reserved, no callbacks registered in MVP)
    for (int stage = 0; stage < static_cast<int>(CallbackType::COUNT); stage++) {
        // Extract all due callbacks from this stage's queue
        std::vector<CallbackEntry> due;
        extract_due_callbacks(m_callback_queues_[stage], due);

        // Execute each callback, catching exceptions to prevent frame loop breakage
        for (auto& entry : due) {
            try {
                entry.callback(frameTimeNanos);
            } catch (const std::exception& e) {
                // Exception in callback: log and continue to next callback
                std::cerr << "Choreographer: callback exception in stage "
                          << stage << ": " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "Choreographer: unknown callback exception in stage "
                          << stage << std::endl;
            }
        }
    }

    // If there are still pending callbacks, schedule the next frame
    bool has_more = false;
    for (int i = 0; i < static_cast<int>(CallbackType::COUNT); i++) {
        if (!m_callback_queues_[i].empty()) {
            has_more = true;
            break;
        }
    }

    if (has_more) {
        schedule_frame();
    }
}

void Choreographer::extract_due_callbacks(std::vector<CallbackEntry>& queue,
                                           std::vector<CallbackEntry>& due) {
    // Scan from the beginning; due callbacks are at the front (sorted by due_time)
    size_t i = 0;
    int64_t now = system_time_nanos();
    while (i < queue.size() && queue[i].due_time <= now) {
        due.push_back(std::move(queue[i]));
        i++;
    }
    // Remove executed entries from the front
    if (i > 0) {
        queue.erase(queue.begin(), queue.begin() + static_cast<std::ptrdiff_t>(i));
    }
}

// ============================================================================
// Query methods
// ============================================================================

auto Choreographer::get_looper() const -> std::shared_ptr<os::Looper> {
    return m_display_event_receiver_ ? m_display_event_receiver_->get_looper() : nullptr;
}

auto Choreographer::get_frame_interval_nanos() const -> int64_t {
    return m_display_event_receiver_ ? m_display_event_receiver_->get_frame_interval_nanos()
                                      : kFrameIntervalNanos;
}

auto Choreographer::get_last_frame_time_nanos() const -> int64_t {
    return m_last_frame_time_nanos_;
}

} // namespace android::view
