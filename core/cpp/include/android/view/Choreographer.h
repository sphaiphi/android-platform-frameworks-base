#pragma once

/**
 * Choreographer — VSync-driven frame loop with staged callback execution.
 *
 * Thread-local singleton that receives periodic VSync pulses from the display
 * subsystem (via DisplayEventReceiver), maintains a sorted queue of per-frame
 * callbacks organized into five priority stages, and executes them in strict
 * order during each frame.
 *
 * Callback stages (in execution order):
 *   INPUT (0)      — Input event processing
 *   ANIMATION (1)  — Animation updates
 *   INSETS_ANIMATION (2) — Window inset animation (reserved for future use)
 *   TRAVERSAL (3)  — Measure/layout/draw traversal trigger
 *   COMMIT (4)     — Post-frame commit actions
 *
 * Thread safety: The Choreographer is a thread-local singleton. All callbacks
 * are executed on the Looper thread. post_* methods may be called from any
 * thread (they serialize on the Looper).
 *
 * MVP scope (per clarifications):
 *   - VSync-only mode (no polling fallback)
 *   - No FrameTimeline, FPSDivisor, buffer stuffing, or animation clock
 *   - Simplified jitter handling
 *   - Token-based callback identity omitted (std::function equality used)
 */

#include <android/view/DisplayEventReceiver.h>
#include <android/os/Looper.h>
#include <functional>
#include <memory>
#include <vector>
#include <cstdint>

namespace android::view {

/**
 * Callback type constants matching Java's CALLBACK_* values.
 */
enum class CallbackType : int {
    INPUT = 0,
    ANIMATION = 1,
    INSETS_ANIMATION = 2,
    TRAVERSAL = 3,
    COMMIT = 4,
    COUNT = 5
};

/**
 * Frame callback signature: invoked with the frame time in nanos.
 */
using FrameCallback = std::function<void(int64_t frameTimeNanos)>;

/**
 * Traverser callback: invoked during the TRAVERSAL stage.
 */
using TraverserCallback = std::function<void()>;

/**
 * Choreographer — the timing and synchronization engine of the Android UI framework.
 *
 * Receives periodic VSync pulses, queues callbacks by stage, and executes them
 * in order during each frame. The TRAVERSAL stage triggers ViewRootImpl::
 * perform_traversals() to drive the measure-layout-draw pipeline.
 */
class Choreographer : public std::enable_shared_from_this<Choreographer> {
public:
    /**
     * Get the thread-local instance, creating it on first access.
     *
     * @throws std::runtime_error if no Looper is available on the current thread.
     */
    static auto get_instance() -> std::shared_ptr<Choreographer>;

    /**
     * Get the main-thread instance. Returns nullptr if called from a non-main thread
     * or if the main Choreographer hasn't been created yet.
     */
    static auto get_main_instance() -> std::shared_ptr<Choreographer>;

    // Non-copyable, movable
    Choreographer(const Choreographer&) = delete;
    Choreographer& operator=(const Choreographer&) = delete;
    Choreographer(Choreographer&&) noexcept;
    Choreographer& operator=(Choreographer&&) noexcept;

    /**
     * Post a frame callback to be executed in the next frame's TRAVERSAL stage.
     * Returns a callback ID that can be used to remove the callback.
     *
     * @param cb  The callback to post. Takes frameTimeNanos as parameter.
     * @return    A unique callback ID for removal.
     */
    uint64_t post_frame_callback(FrameCallback cb);

    /**
     * Post a frame callback delayed by the given number of milliseconds.
     * The callback is executed in the next frame whose start time >= due time.
     *
     * @param cb     The callback to post.
     * @param delay_ms Delay in milliseconds before the callback becomes due.
     * @return       A unique callback ID for removal.
     */
    uint64_t post_frame_callback_delayed(FrameCallback cb, int64_t delay_ms);

    /**
     * Remove a previously posted frame callback.
     *
     * @param id  The callback ID returned by post_frame_callback.
     */
    void remove_frame_callback(uint64_t id);

    /**
     * Get the associated Looper.
     */
    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;

    /**
     * Get the current frame interval in nanoseconds (default 60Hz = 16666667ns).
     */
    [[nodiscard]] auto get_frame_interval_nanos() const -> int64_t;

    /**
     * Get the last frame time in nanoseconds. Returns 0 if no frame has been processed.
     */
    [[nodiscard]] auto get_last_frame_time_nanos() const -> int64_t;

    /**
     * Set the traverser callback, invoked during the TRAVERSAL stage.
     * Used by ViewRootImpl to trigger perform_traversals().
     *
     * @param traverser  The traverser callback.
     */
    void set_traverser(TraverserCallback traverser);

    /**
     * Remove the traverser callback.
     */
    void remove_traverser();

    /**
     * Signal that a new frame is needed (schedule VSync).
     * Called internally when a callback is posted and no frame is pending.
     */
    void schedule_frame();

    /**
     * Destructor: disposes of the DisplayEventReceiver.
     */
    ~Choreographer();

    /**
     * Constructor: creates the DisplayEventReceiver and registers with the Looper.
     * Called internally by get_instance(). Public because std::make_shared needs access.
     */
    explicit Choreographer(std::shared_ptr<DisplayEventReceiver> der);

    // Called by DisplayEventReceiver when a VSync event arrives
    void on_vsync(const VsyncEventData& data);

    // Execute all due callbacks for this frame, in stage order
    void do_frame(int64_t frameTimeNanos);

    // Schedule the next VSync pulse
    void schedule_vsync_locked();

    // Check if a frame is already pending
    auto has_pending_frame() const -> bool;

    // Get current monotonic time in nanoseconds
    static auto system_time_nanos() -> int64_t;

    // -- Callback entry --
    struct CallbackEntry {
        uint64_t id;
        int64_t due_time;
        FrameCallback callback;
    };

    // Extract and execute callbacks due by the given time from a queue
    void extract_due_callbacks(std::vector<CallbackEntry>& queue,
                               std::vector<CallbackEntry>& due);

    // -- State --
    std::shared_ptr<DisplayEventReceiver> m_display_event_receiver_;

    // Callback queues per stage (sorted by due_time)
    std::vector<CallbackEntry> m_callback_queues_[static_cast<int>(CallbackType::COUNT)];

    // Traverser callback (set by ViewRootImpl)
    TraverserCallback m_traverser_;

    // Frame timing state
    int64_t m_last_frame_time_nanos_ = 0;
    bool m_frame_pending_ = false;

    // Jitter tracking
    static constexpr int64_t kFrameIntervalNanos = 16666667; // 60Hz
    static constexpr int kSkippedFrameWarningLimit = 3;
    int m_skipped_frames_ = 0;

    // Callback ID counter
    uint64_t m_next_callback_id_ = 1;

    // -- Thread-Local Storage --
    static inline thread_local std::shared_ptr<Choreographer> s_thread_instance = nullptr;
    static inline std::shared_ptr<Choreographer> s_main_instance = nullptr;
};

} // namespace android::view
