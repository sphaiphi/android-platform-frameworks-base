# Implementation Plan: Choreographer

**Feature ID:** 005
**Spec:** /home/roto/git/android-platform-frameworks-base/core/cpp/specs/android/view/Choreographer.md
**Clarifications:** /home/roto/git/android-platform-frameworks-base/core/cpp/specs/android/view/Choreographer_clarifications.md
**Status:** Draft
**Created:** 2026-05-30
**Prerequisite:** Feature 004 (DisplayEventReceiver)

---

## Summary

The Choreographer is the timing and synchronization engine of the Android UI framework. It receives periodic VSync pulses from the display subsystem (via DisplayEventReceiver), maintains a sorted queue of per-frame callbacks organized into five priority stages (INPUT, ANIMATION, INSETS_ANIMATION, TRAVERSAL, COMMIT), and executes them in strict order during each frame. The TRAVERSAL stage triggers ViewRootImpl::perform_traversals(), which drives the measure-layout-draw pipeline.

This plan implements the MVP: a thread-local singleton that drives the frame loop via VSync, with a sorted-vector callback queue and simplified jitter handling. Advanced features (FrameTimeline, FPSDivisor, buffer stuffing, non-VSync fallback) are explicitly deferred per the clarifications document.

---

## Technical Context

| Aspect | Detail |
|--------|--------|
| Language | C++23 (CMake host build) / NDK r29 (on-device) |
| Dependencies | libui (android::DisplayEventReceiver native), liblog (android/log.h), existing Looper/Handler |
| Target platform | Linux host (development) + Android devices (production) |
| Threading | Thread-local singleton per Looper thread; all calls serialized on Looper thread |
| Performance goal | Zero-cost abstractions: callback dispatch overhead < 100ns; frame loop latency < 1ms |
| Constraints | VSync-only mode (no polling fallback); no FrameTimeline in MVP; no animation clock |

---

## Constitution Check

| Principle | Compliance |
|-----------|-----------|
| I. Safety-First Design | All resources managed via RAII (DisplayEventReceiver FD closed in destructor). Smart pointers exclusively. std::function for callbacks with null checks. No pointer arithmetic. Bounds safety via std::span in any buffer operations. Initialization safety: all members initialized in constructor. |
| II. Zero-Cost Abstractions | Callback queue uses sorted std::vector (cache-friendly, no linked-list indirection). No virtual functions in the hot path -- doFrame() is a direct method call. Callback types are enum class with direct array indexing. std::function overhead is acceptable (one allocation per capture, zero per dispatch). |
| III. Test-Driven Development | Tests written first per feature. choreographer_test.cpp covers: constructor validation, callback ordering, frame timing, jitter handling, ViewRootImpl integration. display_event_receiver_test.cpp covers: VSync event reception, FD registration, disposal. Target >80% coverage. |
| IV. Plan as Source of Truth | This plan is the central artifact. Tasks tracked in conductor/tracks/ (to be created). Plan updated before work begins and after completion with commit SHAs. |
| V. Tech Stack Deliberation | Stack matches existing project conventions: C++23, CMake, GoogleTest, smart pointers, std::function. No new dependencies beyond existing Looper/Handler infrastructure and libui (already a transitive dependency via AOSP). |

---

## Project Structure

```
core/cpp/
├── include/android/view/
│   ├── DisplayEventReceiver.h          [NEW] DisplayEventReceiver public header
│   └── Choreographer.h                 [NEW] Choreographer public header
├── src/android/view/
│   ├── DisplayEventReceiver.cpp        [NEW] DisplayEventReceiver implementation
│   └── Choreographer.cpp               [NEW] Choreographer implementation
├── include/android/view/
│   └── ViewRootImpl.h                  [MODIFIED] Add weak_ptr<Choreographer> members
├── src/android/view/
│   └── ViewRootImpl.cpp                [MODIFIED] Add choreographer integration
├── CMakeLists.txt                      [MODIFIED] Add new source files
├── tests/
│   ├── CMakeLists.txt                  [MODIFIED] Add test executables
│   ├── mock_display_event_receiver.h   [NEW] Mock for DisplayEventReceiver FD
│   ├── display_event_receiver_test.cpp [NEW] DisplayEventReceiver tests
│   └── choreographer_test.cpp          [NEW] Choreographer tests
├── specs/android/view/
│   ├── DisplayEventReceiver.md         [EXISTING] Reference spec
│   └── Choreographer.md                [EXISTING] Reference spec
├── specs/005-choreographer/
│   ├── plan.md                         [NEW] This file
│   ├── data-model.md                   [NEW] Data model
│   ├── research.md                     [NEW] Dependency research
│   └── quickstart.md                   [NEW] Developer onboarding
```

---

## Phase 0: Research

### 0.1: DisplayEventReceiver Native API (libui)

The C++ DisplayEventReceiver must wrap android::DisplayEventReceiver from libui. Key questions:

1. Header location: #include <ui/DisplayEventReceiver.h> -- available in AOSP libui. On host builds via mock or system headers.
2. Constructor: DisplayEventReceiver() opens a connection to SurfaceFlinger. Returns error via initCheck().
3. FD access: int getFd() returns the file descriptor for polling.
4. Event reading: bool getNextEvent() reads next event from the FD. Returns false on error.
5. Event types: DisplayEventReceiver::Event union with vsync, hotplug, refresh, contentOrientation variants.
6. VSync event fields: DisplayEventReceiver::VsyncEventData contains timestamp (int64_t nanos), count (uint32_t), vsync_id (uint64_t).
7. scheduleVsync(): void requestVsync() requests a single VSync pulse.
8. close(): void close() shuts down the connection and closes the FD.

Action: Verify header availability in the current build environment. If libui headers are not available on host, create a mock similar to android_mock/.

### 0.2: Looper Integration Pattern

The existing InputEventReceiver provides the reference pattern:
- register_with_looper() calls m_looper_->add_fd(fd, POLLIN, callback, this)
- FD callback captures this raw pointer, calls internal method
- unregister_from_looper() calls m_looper_->remove_fd(cookie)
- dispose() calls both unregister and resource cleanup

This pattern must be replicated for DisplayEventReceiver.

### 0.3: Thread-Local Singleton Pattern

The existing Looper class uses:
- static thread_local std::shared_ptr<Looper> s_thread_local_looper
- static std::shared_ptr<Looper> s_main_looper

Choreographer must follow the same pattern:
- static thread_local std::shared_ptr<Choreographer> s_thread_instance
- static std::shared_ptr<Choreographer> s_main_instance
- get_instance() factory creates on first access
- get_main_instance() returns the main thread instance

### 0.4: Frame Timing Constants

- Standard frame interval at 60Hz: 16,666,667 nanoseconds (1e9 / 60)
- Standard frame interval at 120Hz: 8,333,333 nanoseconds
- Frame interval is determined by the DisplayEventReceiver's reported refresh rate
- For MVP, use 60Hz default (16,666,667ns) with ability to query actual interval

---

## Phase 1: Design

### 1.1: DisplayEventReceiver Design

File: core/cpp/include/android/view/DisplayEventReceiver.h

Wraps the native android::DisplayEventReceiver (from libui) and provides a C++ RAII wrapper with Looper integration.

```cpp
namespace android::view {

// VSync event data delivered to Choreographer
struct VsyncEventData {
    int64_t timestamp;        // VSync timestamp in nanos (from hardware)
    uint32_t count;           // VSync sequence count
    uint64_t vsync_id;        // Monotonic VSync identifier
};

// Display event types
enum class DisplayEventType : int {
    VSYNC = 0,
    HOTPLUG = 1,
    REFRESH = 2,
    CONTENT_ORIENTATION = 3,
};

/**
 * Native wrapper around android::DisplayEventReceiver from libui.
 *
 * Registers the receiver's FD with a Looper for async event delivery.
 * All public methods must be called from the Looper thread.
 *
 * RAII: FD is closed in destructor. Looper registration cleaned up in dispose().
 */
class DisplayEventReceiver {
public:
    using VsyncCallback = std::function<void(const VsyncEventData&)>;

    explicit DisplayEventReceiver(std::shared_ptr<os::Looper> looper,
                                  VsyncCallback callback);
    ~DisplayEventReceiver();

    // Non-copyable, movable
    DisplayEventReceiver(const DisplayEventReceiver&) = delete;
    DisplayEventReceiver& operator=(const DisplayEventReceiver&) = delete;
    DisplayEventReceiver(DisplayEventReceiver&&) noexcept;
    DisplayEventReceiver& operator=(DisplayEventReceiver&&) noexcept;

    /**
     * Request a single VSync pulse from SurfaceFlinger.
     * Must be called from the Looper thread.
     */
    void schedule_vsync();

    /**
     * Dispose of the receiver and release the FD.
     */
    void dispose();

    /**
     * Check if the receiver has been disposed.
     */
    [[nodiscard]] auto is_disposed() const -> bool;

    /**
     * Register the receiver's FD with the Looper for async polling.
     */
    void register_with_looper();

    /**
     * Unregister the FD watcher from the Looper.
     */
    void unregister_from_looper();

    /**
     * Get the associated Looper.
     */
    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;

    /**
     * Get the current frame interval in nanoseconds.
     */
    [[nodiscard]] auto get_frame_interval_nanos() const -> int64_t;

private:
    // Called by FD callback when data is available on the receiver's pipe
    void on_data_available();

    // Parse and dispatch VSync events from the native receiver
    void dispatch_events();

    // Set the VSync callback (called by Choreographer factory)
    void set_vsync_callback(VsyncCallback callback);

    // -- State --
    std::shared_ptr<os::Looper> m_looper_;
    VsyncCallback m_vsync_callback_;

    // Native receiver handle (RAII -- closed in destructor)
    // Wrapped in unique_ptr because native type may not be available on host
    struct NativeReceiver;
    std::unique_ptr<NativeReceiver> m_native_;

    // FD watcher registration
    bool m_disposed_ = false;
    bool m_fd_watcher_registered_ = false;
    int m_fd_watcher_cookie_ = 0;
    int m_fd_ = -1;

    // Frame interval (computed from display refresh rate)
    int64_t m_frame_interval_nanos_ = 16666667; // 60Hz default
};

} // namespace view
} // namespace android
```

Implementation notes (core/cpp/src/android/view/DisplayEventReceiver.cpp):
- On host builds (HOST_BUILD), use a mock native receiver that simulates VSync events written through a pipe pair (similar to MockInputChannel).
- On-device builds, include <ui/DisplayEventReceiver.h> and use the real android::DisplayEventReceiver.
- on_data_available() reads from m_native_->getFd(), dispatches VSync events via m_vsync_callback_.
- schedule_vsync() calls m_native_->requestVsync().
- dispose() unregisters from Looper, then closes native receiver.

Mock strategy: For host tests, create mock_display_event_receiver.h that provides a pipe-based VSimulator. The mock creates an AF_UNIX socket pair, writes VSync "events" through the write end, and the DisplayEventReceiver reads them through the read end. This mirrors the MockInputChannel pattern exactly.

### 1.2: Choreographer Design

File: core/cpp/include/android/view/Choreographer.h

Thread-local singleton managing the frame loop with staged callback execution.

```cpp
namespace android::view {

class Choreographer : public std::enable_shared_from_this<Choreographer> {
public:
    /**
     * Frame callback signature. Called with the frame time in nanoseconds.
     */
    using FrameCallback = std::function<void(int64_t frameTimeNanos)>;

    /**
     * Callback stage types -- matches Java CALLBACK_* constants.
     */
    enum class CallbackType : int {
        INPUT = 0,
        ANIMATION = 1,
        INSETS_ANIMATION = 2,
        TRAVERSAL = 3,
        COMMIT = 4,
        COUNT = 5
    };

    // -- Factory --

    /**
     * Get the thread-local Choreographer instance.
     * Creates one on first access using the current thread's Looper.
     */
    static auto get_instance() -> std::shared_ptr<Choreographer>;

    /**
     * Get the main-thread Choreographer instance.
     */
    static auto get_main_instance() -> std::shared_ptr<Choreographer>;

    // -- Callback Posting --

    /**
     * Schedule a frame callback to run at the start of the next frame.
     */
    void post_frame_callback(FrameCallback cb);

    /**
     * Schedule a frame callback with a delay (milliseconds).
     * The callback runs at the start of the first frame whose time >= due_time.
     */
    void post_frame_callback_delayed(FrameCallback cb, int64_t delay_ms);

    /**
     * Remove a previously posted frame callback.
     */
    void remove_frame_callback(FrameCallback cb);

    // -- Query --

    /**
     * Get the associated Looper.
     */
    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;

    /**
     * Get the frame interval in nanoseconds (1 / refresh_rate).
     */
    [[nodiscard]] auto get_frame_interval_nanos() const -> int64_t;

    /**
     * Get the last frame time in nanoseconds.
     */
    [[nodiscard]] auto get_last_frame_time_nanos() const -> int64_t;

    // -- Internal (for ViewRootImpl integration) --

    /**
     * Register the traversal function. Called by ViewRootImpl during set_view().
     * The traverser is invoked as the CALLBACK_TRAVERSAL callback during doFrame().
     */
    void set_traverser(std::function<void()> traverser);

    /**
     * Remove the traversal function. Called by ViewRootImpl during remove_view().
     */
    void remove_traverser();

private:
    explicit Choreographer(std::shared_ptr<DisplayEventReceiver> display_event_receiver);
    ~Choreographer();

    // Non-copyable
    Choreographer(const Choreographer&) = delete;
    Choreographer& operator=(const Choreographer&) = delete;

    // -- Frame Loop --

    /**
     * Execute all pending callbacks for the current frame, in stage order.
     */
    void do_frame(int64_t frame_time_nanos);

    /**
     * Schedule a new frame. Called after the previous frame completes,
     * or when a new callback is posted and no frame is pending.
     */
    void schedule_frame_locked();

    /**
     * Handle a VSync pulse: calculate frame time, schedule doFrame.
     */
    void on_vsync(const VsyncEventData& data);

    // -- Callback Queue --

    struct CallbackEntry {
        int64_t due_time;          // Nanos when callback is due
        FrameCallback callback;    // The callback to invoke
    };

    // One sorted vector per callback type
    std::array<std::vector<CallbackEntry>, static_cast<int>(CallbackType::COUNT)> m_callback_queues_;

    // Traverser callback (set by ViewRootImpl)
    std::function<void()> m_traverser_;

    // Frame timing state
    int64_t m_last_frame_time_nanos_ = 0;
    int64_t m_frame_scheduled_ = 0; // 0 = no frame pending, otherwise vsync time
    bool m_frame_pending_ = false;

    // Skip detection
    static constexpr int kSkippedFrameWarningLimit = 3;
    int m_skipped_frames_ = 0;

    // Dependencies
    std::shared_ptr<DisplayEventReceiver> m_display_event_receiver_;

    // -- Thread-Local Storage --
    static inline thread_local std::shared_ptr<Choreographer> s_thread_instance = nullptr;
    static inline std::shared_ptr<Choreographer> s_main_instance = nullptr;
};

} // namespace android::view
```

#### get_instance() Factory

```cpp
auto Choreographer::get_instance() -> std::shared_ptr<Choreographer> {
    if (s_thread_instance == nullptr) {
        auto looper = os::Looper::my_looper();
        if (!looper) {
            throw std::runtime_error("Choreographer: no Looper on this thread");
        }

        // Create the VSync callback lambda first (before DisplayEventReceiver can fire)
        VsyncCallback vsync_cb = [self = std::shared_ptr<Choreographer>()](const VsyncEventData& data) {
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
```

Important: The callback capture pattern above uses self = s_thread_instance to capture the just-created shared_ptr. This is safe because s_thread_instance is thread_local and initialization is inherently thread-safe (C++17 inline thread_local).

#### do_frame(int64_t frame_time_nanos)

```
do_frame(frame_time_nanos):
    start_nanos = system_time_nanos()

    // 1. Jitter calculation (simplified)
    if (start_nanos - frame_time_nanos >= frame_interval_nanos):
        // Frame is late -- resync to nearest past VSync
        frame_time_nanos = start_nanos - (jitter_nanos % frame_interval_nanos)

    if (frame_time_nanos > start_nanos):
        // Frame time went backward -- skip this frame
        schedule_next_vsync()
        return

    // 2. Detect skipped frames
    if (start_nanos - m_last_frame_time_nanos > 2 * frame_interval_nanos):
        m_skipped_frames_++
        if m_skipped_frames_ > kSkippedFrameWarningLimit:
            log_warning("Skipped N frames")

    // 3. Execute callbacks in stage order
    for type in [INPUT, ANIMATION, INSETS_ANIMATION, TRAVERSAL, COMMIT]:
        entries = extract_due_callbacks(type, frame_time_nanos)
        for entry in entries:
            try:
                entry.callback(frame_time_nanos)
            catch (...):
                log_error("Callback threw exception")

    // 4. If traverser is registered, call it explicitly
    if m_traverser_:
        m_traverser_()

    // 5. Update state
    m_last_frame_time_nanos_ = frame_time_nanos
    m_frame_pending_ = false
    m_skipped_frames_ = 0

    // 6. Schedule next frame
    schedule_frame_locked()
```

#### schedule_frame_locked()

```
schedule_frame_locked():
    if m_frame_pending_:
        return  // Already scheduled

    frame_time_nanos = system_time_nanos() + frame_interval_nanos
    m_frame_scheduled_ = frame_time_nanos
    m_frame_pending_ = true

    // Request VSync from DisplayEventReceiver
    m_display_event_receiver_->schedule_vsync()
```

#### on_vsync(const VsyncEventData& data)

```
on_vsync(data):
    // VSync arrived -- post doFrame to the message queue
    frame_time = data.timestamp
    post to looper: MSG_DO_FRAME with frame_time
```

The actual posting uses the Looper's send_message with a callback:

```cpp
m_display_event_receiver_->get_looper()->send_message(
    {.callback = [self = shared_from_this(), frame_time]() {
        self->do_frame(frame_time);
    }},
    nullptr
);
```

#### Callback Queue Operations

Sorted insertion (post_frame_callback):
```cpp
void Choreographer::post_frame_callback(FrameCallback cb) {
    auto now = system_time_nanos();
    CallbackEntry entry{.due_time = now, .callback = std::move(cb)};
    auto& queue = m_callback_queues_[static_cast<int>(CallbackType::TRAVERSAL)];
    // Binary search for insertion point
    auto it = std::lower_bound(queue.begin(), queue.end(), entry.due_time,
        [](const CallbackEntry& e, int64_t t) { return e.due_time < t; });
    queue.insert(it, std::move(entry));
}
```

Extraction (inside do_frame):
```cpp
auto extract_due_callbacks(CallbackType type, int64_t frame_time)
    -> std::vector<CallbackEntry> {
    auto& queue = m_callback_queues_[static_cast<int>(type)];
    std::vector<CallbackEntry> due;
    auto it = std::upper_bound(queue.begin(), queue.end(), frame_time,
        [](int64_t t, const CallbackEntry& e) { return t < e.due_time; });
    if (it != queue.begin()) {
        due.assign(queue.begin(), it);
        queue.erase(queue.begin(), it);
    }
    return due;
}
```

Removal (remove_frame_callback):
```cpp
void Choreographer::remove_frame_callback(FrameCallback cb) {
    for (auto& queue : m_callback_queues_) {
        queue.erase(
            std::remove_if(queue.begin(), queue.end(),
                [&cb](const CallbackEntry& e) { return e.callback == cb; }),
            queue.end());
    }
}
```

### 1.3: ViewRootImpl Integration

File: core/cpp/include/android/view/ViewRootImpl.h (MODIFIED)

Add choreographer members:

```cpp
class ViewRootImpl : public std::enable_shared_from_this<ViewRootImpl> {
public:
    // ... existing methods ...

    /**
     * Set the Choreographer for this ViewRootImpl.
     * Called during set_view() to enable choreographer-driven traversals.
     */
    void set_choreographer(std::weak_ptr<Choreographer> choreographer);

    /**
     * Remove the Choreographer reference.
     * Called during remove_view().
     */
    void remove_choreographer();

private:
    // ... existing members ...

    // Choreographer integration
    std::weak_ptr<Choreographer> m_choreographer_;
    bool m_choreographer_set_ = false;
};
```

File: core/cpp/src/android/view/ViewRootImpl.cpp (MODIFIED)

In set_view(), after setting the view, register the traversal callback:

```cpp
void ViewRootImpl::set_view(const std::shared_ptr<View>& view) {
    view_ = view;
    if (view_ && m_choreographer_) {
        auto choreo = m_choreographer_.lock();
        if (choreo) {
            // Keep ViewRootImpl alive during callback via shared_ptr capture
            auto strong_self = shared_from_this();
            choreo->set_traverser([strong_self]() {
                if (strong_self) {
                    strong_self->perform_traversals();
                }
            });
            m_choreographer_set_ = true;
        }
    }
}
```

Note: ViewRootImpl is currently not enable_shared_from_this. For the integration to work properly, it must inherit from std::enable_shared_from_this<ViewRootImpl>. This is a minimal change to the class definition.

### 1.4: Data Flow

```
                    +----------------------+
                    |   SurfaceFlinger      |
                    |   (Display Hardware)  |
                    +----------+------------+
                               | VSync Pulse
                               v
                    +----------------------+
                    | DisplayEventReceiver  |
                    |  (libui native)       |
                    |  FD -> Looper poll    |
                    +----------+------------+
                               | onVsync(data)
                               v
                    +----------------------+
                    |     Looper            |
                    |  (message queue)      |
                    |  MSG_DO_FRAME         |
                    +----------+------------+
                               | callback
                               v
                    +----------------------+
                    |    Choreographer      |
                    |  do_frame(frame_time) |
                    +----------+------------+
                               |
              +----------------+----------------+
              v                v                 v
         +-----------+  +-----------+    +---------------+
         |  INPUT    |  |ANIMATION  |    |  TRAVERSAL    |
         | callbacks |  |callbacks  |    |  callbacks    |
         +-----------+  +-----------+    +-------+-------+
                                                | m_traverser_
                                                v
                                       +------------------+
                                       | ViewRootImpl     |
                                       |perform_traversals|
                                       | (measure/layout) |
                                       +--------+---------+
                                                |
                                                v
                                       +------------------+
                                       |    perform_draw  |
                                       +--------+---------+
                                                |
                                                v
                                       schedule_frame_locked()
                                       -> DisplayEventReceiver.schedule_vsync()
```

### 1.5: Error Model

| Error Condition | Handling |
|----------------|----------|
| DisplayEventReceiver creation fails (no display / SurfaceFlinger unreachable) | Choreographer constructor throws std::runtime_error (no fallback to polling) |
| VSync starvation (Looper blocked) | doFrame detects skipped frames > threshold, logs warning, continues |
| Frame time going backward | Skip frame, log warning, request next VSync |
| Callback throws exception | Catch, log, continue to next callback (do not break the frame loop) |
| DisplayEventReceiver disposed while Choreographer alive | Choreographer detects disposed state, logs error, stops scheduling |
| No Looper on thread | get_instance() throws std::runtime_error |

---

## Phase 2: Testing Strategy

### 2.1: DisplayEventReceiver Tests

File: core/cpp/tests/display_event_receiver_test.cpp

| Test | Purpose |
|------|---------|
| ConstructorWithValidLooper | Verifies construction with valid Looper |
| ConstructorWithNullLooperThrows | Null Looper -> exception |
| ScheduleVsyncNoopWhenDisposed | schedule_vsync after dispose is no-op |
| RegisterUnregisterLooper | FD registration and cleanup |
| VsyncCallbackInvoked | Mock VSync event triggers callback with correct timestamp |
| DisposeClosesFd | FD is closed after dispose |
| MoveConstructorPreservesState | Move semantics work correctly |
| FrameIntervalDefault60Hz | Default frame interval is 16666667ns |

Mock strategy: Use a pipe pair where the test writes raw VSync event data to the write end. The DisplayEventReceiver reads from the read end via its Looper-registered FD.

### 2.2: Choreographer Tests

File: core/cpp/tests/choreographer_test.cpp

| Test | Purpose |
|------|---------|
| GetInstanceCreatesOnFirstCall | thread_local singleton created on first access |
| GetInstanceReturnsSameInstance | Second call returns same shared_ptr |
| PostFrameCallbackExecutedInOrder | Callbacks execute in posted order within same frame |
| PostFrameCallbackDelayedExecutedAtRightTime | Delayed callback waits for correct frame |
| RemoveFrameCallbackPreventsExecution | Removed callback does not fire |
| DoFrameExecutesStagesInOrder | INPUT fires before ANIMATION before TRAVERSAL |
| DoFrameSkippedFrameWarning | >3 skipped frames triggers warning (verifiable via mock log) |
| DoFrameBackwardTimeSkipsFrame | Backward frame time -> no callback execution |
| SetTraverserCallsPerformTraversals | ViewRootImpl traverser invoked during TRAVERSAL stage |
| GetFrameIntervalNanos | Returns correct interval |
| GetLastFrameTimeNanos | Returns last frame time after doFrame |
| JitterResyncToNearestVsync | Late frame resyncs to nearest past VSync |
| MultipleCallbacksSameStage | Multiple callbacks in same stage all execute |
| CallbackExceptionDoesNotBreakFrameLoop | Throwing callback -> next callback still runs |

### 2.3: ViewRootImpl Integration Tests

File: core/cpp/tests/view_root_impl_choreographer_test.cpp (NEW test file)

| Test | Purpose |
|------|---------|
| SetChoreographerRegistersTraverser | set_choreographer + set_view registers traverser |
| ChoreographerTraversalTriggersPerformTraversals | doFrame with TRAVERSAL calls ViewRootImpl |
| RemoveChoreographerRemovesTraverser | remove_choreographer clears the traverser |
| WeakPtrExpiryDoesNotCrash | Weak_ptr expires -> traverser is no-op |

### 2.4: Build Integration

Add to core/cpp/CMakeLists.txt:
- src/android/view/DisplayEventReceiver.cpp
- src/android/view/Choreographer.cpp

Add to core/cpp/tests/CMakeLists.txt:
- display_event_receiver_test.cpp
- choreographer_test.cpp
- view_root_impl_choreographer_test.cpp
- mock_display_event_receiver.h

---

## Dependencies

```
DisplayEventReceiver --> Choreographer --> ViewRootImpl integration
     (libui)              (thread_local)       (weak_ptr)
```

Hard dependencies:
- DisplayEventReceiver (feature 004) must exist before Choreographer
- Looper (existing) for FD registration and message posting
- Handler (existing) for message dispatch (used indirectly via Looper::send_message)

Soft dependencies:
- ViewRootImpl integration is additive -- existing ViewRootImpl continues to work without Choreographer

---

## Open Questions

- [ ] libui availability on host: Verify <ui/DisplayEventReceiver.h> is available in the build environment. If not, the mock strategy needs to be defined (pipe-based VSimulator in android_mock/).
- [ ] ViewRootImpl enable_shared_from_this: Adding enable_shared_from_this to ViewRootImpl is a breaking change if anyone constructs it on the stack. Confirm this is acceptable.
- [ ] VSync event format on host: The mock VSync event must match the native DisplayEventReceiver::Event wire format. Define the exact mock format.
- [ ] Log integration: Should use android/log.h (LOG_WARN) for skip warnings. Verify log library is linked in host build.
