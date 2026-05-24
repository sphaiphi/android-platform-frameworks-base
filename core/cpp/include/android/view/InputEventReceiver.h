#pragma once

#include <android/view/InputEvent.h>
#include <android/view/InputError.h>
#include <android/view/MotionEvent.h>
#include <android/view/KeyEvent.h>
#include <android/view/InputChannel.h>
#include <android/os/Looper.h>
#include <memory>
#include <vector>
#include <cstdint>
#include <functional>
#include <expected>
#include <optional>
#include <span>

namespace android {
namespace view {

/**
 * Core receiver class that bridges the input channel socket to application callbacks.
 *
 * Lock-free, single-threaded design — all calls must be made exclusively from
 * the Looper thread. No internal mutexes or synchronization primitives.
 *
 * Events arrive via an InputChannel socket pair watched by a Looper. The receiver
 * reads events from the socket, parses the Android InputEvent wire protocol,
 * and delivers them through the onInputEvent() callback.
 */
class InputEventReceiver {
public:
    /**
     * Callback signature for event delivery.
     */
    using InputEventCallback = std::function<void(const InputEventWrapper& wrapper)>;

    /**
     * Construct an InputEventReceiver bound to an InputChannel and Looper.
     */
    InputEventReceiver(std::shared_ptr<InputChannel> channel,
                       std::shared_ptr<os::Looper> looper,
                       InputEventCallback callback);

    ~InputEventReceiver();

    // Non-copyable, movable
    InputEventReceiver(const InputEventReceiver&) = delete;
    InputEventReceiver& operator=(const InputEventReceiver&) = delete;
    InputEventReceiver(InputEventReceiver&&) noexcept;
    InputEventReceiver& operator=(InputEventReceiver&&) noexcept;

    /**
     * Consume all available events from the input channel.
     */
    auto consume_events() -> std::vector<InputEventWrapper>;

    /**
     * Signal completion of the current event to the InputDispatcher.
     */
    auto finish_input_event(bool handled) -> std::expected<void, InputError>;

    /**
     * Dispose of the receiver and release all resources.
     */
    void dispose();

    /**
     * Check if the receiver has been disposed.
     */
    [[nodiscard]] auto is_disposed() const -> bool;

    /**
     * Consume and dispatch all batched input events.
     */
    auto consume_batched_input_events() -> bool;

    /**
     * Check if input data is available on the read FD.
     */
    auto probably_has_input() -> bool;

    /**
     * Report input latency timeline data (stub — no-op for now).
     */
    void report_timeline(int64_t frame_time_nanos);

    /**
     * Handle focus change event.
     */
    void on_focus_event(bool has_focus);

    /**
     * Handle touch mode change event.
     */
    void on_touch_mode_changed(bool in_touch_mode);

    /**
     * Handle pointer capture event (stub).
     */
    void on_pointer_capture_event(bool enabled);

    /**
     * Get current focus state.
     */
    [[nodiscard]] auto get_has_focus() const -> bool;

    /**
     * Get current touch mode state.
     */
    [[nodiscard]] auto get_in_touch_mode() const -> bool;

    /**
     * Get current pointer capture state.
     */
    [[nodiscard]] auto get_pointer_capture_enabled() const -> bool;

    /**
     * Register the input channel read FD with the Looper for async polling.
     */
    void register_with_looper();

    /**
     * Unregister the FD watcher from the Looper.
     */
    void unregister_from_looper();

    /**
     * Get the associated input channel.
     */
    [[nodiscard]] auto get_channel() const -> std::shared_ptr<InputChannel>;

    /**
     * Get the associated Looper.
     */
    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;

    /**
     * Dispatch a single parsed event via the callback (test helper).
     */
    void dispatch_event(InputEventWrapper wrapper);

 private:
    /**
     * Parse a single MotionEvent from the wire protocol buffer.
     */
    auto parse_motion_event(std::span<const uint8_t> data, size_t& offset)
        -> std::expected<MotionEvent, InputError>;

    /**
     * Parse a single KeyEvent from the wire protocol buffer.
     */
    auto parse_key_event(std::span<const uint8_t> data, size_t& offset)
        -> std::expected<KeyEvent, InputError>;

    // ── State ──
    std::shared_ptr<InputChannel> m_channel_;
    std::shared_ptr<os::Looper> m_looper_;
    InputEventCallback m_callback_;

    // Current event being processed (sequential invariant)
    InputEventWrapper m_current_event_;
    bool m_current_event_has_value_ = false;

    // Sequence number counter
    uint32_t m_sequence_counter_ = 0;

    // Disposal state
    bool m_disposed_ = false;

    // FD watcher registration state
    bool m_fd_watcher_registered_ = false;
    int m_fd_watcher_cookie_ = 0;

    // State tracking
    bool m_has_focus_ = false;
    bool m_in_touch_mode_ = false;
    bool m_pointer_capture_enabled_ = false;
};

} // namespace view
} // namespace android
