# Implementation Design: Choreographer + DisplayEventReceiver + ViewRootImpl Integration

**Feature ID:** 005
**Designed from:** plan.md, tasks.md, Choreographer.md, Choreographer_clarifications.md, DisplayEventReceiver.md
**Date:** 2026-05-30

> This is a design document, not a plan.
> It defines what the implementation looks like -- component shapes, interfaces,
> data flows, behaviours, and structure.
> The implement agent builds from this blueprint without redesigning.

---

## 1. Component Design

### DisplayEventReceiver

**Responsibility:** Low-level wrapper around the native `android::DisplayEventReceiver` (from libui) that registers its event pipe FD with a Looper for async VSync event delivery and dispatches parsed VSync data to a callback.

**Public interface:**

```cpp
namespace android::view {

struct VsyncEventData {
    int64_t timestamp;    // VSync timestamp in nanos (from hardware)
    uint32_t count;       // VSync sequence count
    uint64_t vsync_id;    // Monotonic VSync identifier
};

enum class DisplayEventType : int {
    VSYNC = 0,
    HOTPLUG = 1,
    REFRESH = 2,
    CONTENT_ORIENTATION = 3,
};

class DisplayEventReceiver {
public:
    using VsyncCallback = std::function<void(const VsyncEventData&)>;

    explicit DisplayEventReceiver(std::shared_ptr<os::Looper> looper,
                                  VsyncCallback callback);
    ~DisplayEventReceiver();

    DisplayEventReceiver(const DisplayEventReceiver&) = delete;
    DisplayEventReceiver& operator=(const DisplayEventReceiver&) = delete;
    DisplayEventReceiver(DisplayEventReceiver&&) noexcept;
    DisplayEventReceiver& operator=(DisplayEventReceiver&&) noexcept;

    void schedule_vsync();
    void dispose();
    [[nodiscard]] auto is_disposed() const -> bool;
    void register_with_looper();
    void unregister_from_looper();
    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;
    [[nodiscard]] auto get_frame_interval_nanos() const -> int64_t;

private:
    void on_data_available();
    void dispatch_events();
    void set_vsync_callback(VsyncCallback callback);

    std::shared_ptr<os::Looper> m_looper_;
    VsyncCallback m_vsync_callback_;
    struct NativeReceiver;
    std::unique_ptr<NativeReceiver> m_native_;
    bool m_disposed_ = false;
    bool m_fd_watcher_registered_ = false;
    int m_fd_watcher_cookie_ = 0;
    int m_fd_ = -1;
    int64_t m_frame_interval_nanos_ = 16666667; // 60Hz default
};

} // namespace view
} // namespace android
```

**Internal structure:**
- `NativeReceiver` opaque inner class (defined in `.cpp`) wrapping either the real `android::DisplayEventReceiver` (libui) or the mock (`android_mock/ui/DisplayEventReceiver.h`) on host builds.
- FD watcher cookie from `Looper::add_fd()` for clean unregistration.
- `m_fd_` cached from `m_native_->getFd()` to avoid repeated calls.

**Lifecycle:**
- Created by `Choreographer::get_instance()` factory via `std::make_shared<DisplayEventReceiver>`.
- Registered with Looper immediately after construction (before any VSync can fire).
- Destroyed when the last `shared_ptr` is released; destructor calls `dispose()` if not already disposed.
- Movable (transfers ownership of FD and Looper registration); source left in disposed state.

**Boundary -- never does:**
- Does not parse VSync events into Choreographer-level semantics (jitter, frame scheduling). It only parses the wire format and invokes the callback.
- Does not manage Choreographer callback queues.
- Does not call `schedule_frame_locked()` or any Choreographer method.

---

### Choreographer

**Responsibility:** Thread-local singleton that drives the Android frame loop: receives VSync pulses from DisplayEventReceiver, maintains a sorted per-stage callback queue, executes callbacks in strict stage order (INPUT -> ANIMATION -> INSETS_ANIMATION -> TRAVERSAL -> COMMIT), and triggers ViewRootImpl traversal.

**Public interface:**

```cpp
namespace android::view {

class Choreographer : public std::enable_shared_from_this<Choreographer> {
public:
    using FrameCallback = std::function<void(int64_t frameTimeNanos)>;

    enum class CallbackType : int {
        INPUT = 0,
        ANIMATION = 1,
        INSETS_ANIMATION = 2,
        TRAVERSAL = 3,
        COMMIT = 4,
        COUNT = 5
    };

    static auto get_instance() -> std::shared_ptr<Choreographer>;
    static auto get_main_instance() -> std::shared_ptr<Choreographer>;

    void post_frame_callback(FrameCallback cb);
    void post_frame_callback_delayed(FrameCallback cb, int64_t delay_ms);
    void remove_frame_callback(FrameCallback cb);

    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;
    [[nodiscard]] auto get_frame_interval_nanos() const -> int64_t;
    [[nodiscard]] auto get_last_frame_time_nanos() const -> int64_t;

    void set_traverser(std::function<void()> traverser);
    void remove_traverser();

private:
    explicit Choreographer(std::shared_ptr<DisplayEventReceiver> der);
    ~Choreographer();

    void do_frame(int64_t frame_time_nanos);
    void schedule_frame_locked();
    void on_vsync(const VsyncEventData& data);

    struct CallbackEntry {
        int64_t due_time;
        FrameCallback callback;
    };

    std::array<std::vector<CallbackEntry>, static_cast<int>(CallbackType::COUNT)> m_callback_queues_;
    std::function<void()> m_traverser_;
    int64_t m_last_frame_time_nanos_ = 0;
    int64_t m_frame_scheduled_ = 0;
    bool m_frame_pending_ = false;
    static constexpr int kSkippedFrameWarningLimit = 3;
    int m_skipped_frames_ = 0;
    std::shared_ptr<DisplayEventReceiver> m_display_event_receiver_;

    static inline thread_local std::shared_ptr<Choreographer> s_thread_instance = nullptr;
    static inline std::shared_ptr<Choreographer> s_main_instance = nullptr;
};

} // namespace android::view
} // namespace android
```

**Internal structure:**
- `m_callback_queues_`: `std::array<std::vector<CallbackEntry>, 5>` -- one sorted vector per stage. Sorted by `due_time` ascending.
- `m_traverser_`: `std::function<void()>` set by ViewRootImpl. Invoked during TRAVERSAL stage after all TRAVERSAL callbacks.
- `m_frame_pending_`: boolean guard preventing duplicate frame scheduling.
- `m_skipped_frames_`: counter for missed-frame detection.
- `system_time_nanos()`: private static helper using `std::chrono::steady_clock::now()`.

**Lifecycle:**
- Created via `get_instance()` on first thread-local access.
- Factory creates VSync callback lambda first, then DisplayEventReceiver, then Choreographer, then registers with Looper. This ordering ensures no window exists where VSync data could arrive before the receiver is ready.
- Destroyed when the thread exits (thread_local destruction) or when all `shared_ptr`s are released.

**Boundary -- never does:**
- Does not parse VSync wire format (delegates to DisplayEventReceiver).
- Does not directly interact with SurfaceFlinger.
- Does not manage ViewRootImpl lifecycle (uses `std::function<void()>` traverser, not a raw pointer).

---

### ViewRootImpl (Modified)

**Responsibility:** Existing UI root class extended to optionally register a traverser callback with Choreographer, enabling VSync-driven measure/layout/draw cycles.

**Modified public interface (additions only):**

```cpp
class ViewRootImpl : public std::enable_shared_from_this<ViewRootImpl> {
public:
    // ... existing methods unchanged ...

    void set_choreographer(std::weak_ptr<Choreographer> choreographer);
    void remove_choreographer();
};
```

**Modified private members (additions only):**

```cpp
private:
    std::weak_ptr<Choreographer> m_choreographer_;
    bool m_choreographer_set_ = false;
```

**Internal structure:**
- `set_view()` is modified to register the traverser callback when both a view and a choreographer are present. The traverser captures a `shared_ptr<ViewRootImpl>` via `shared_from_this()` to keep the object alive during callback execution.
- `remove_view()` is modified to call `remove_choreographer()` before destroying the view.

**Lifecycle:**
- `set_choreographer()` can be called at any time before `set_view()`.
- `set_view()` is the integration point: if a choreographer is present, the traverser is registered.
- `remove_choreographer()` clears the weak_ptr and flag.
- `remove_view()` calls `remove_choreographer()` for cleanup.

**Boundary -- never does:**
- Does not know about Choreographer callback queues or stages.
- Does not manage Choreographer lifetime (uses `weak_ptr`).
- Does not call `schedule_frame_locked()` or any Choreographer scheduling method.

---

### MockDisplayEventReceiver (Test Helper)

**Responsibility:** Pipe-based VSimulator for host-unit testing. Creates an AF_UNIX socket pair, exposes the read end as the "FD", and provides a static method to write wire-format VSync events through the write end.

**Public interface:**

```cpp
namespace android {
namespace view {
namespace test {

class MockDisplayEventReceiver {
public:
    static auto create() -> std::pair<int, int>; // {read_fd, write_fd}
    static void write_vsync_event(int write_fd, int64_t timestamp,
                                  uint32_t count, uint64_t vsync_id);
    static void close(int read_fd, int write_fd);
};

} // namespace test
} // namespace view
} // namespace android
```

**Internal structure:**
- `create()`: calls `socketpair(AF_UNIX, SOCK_DGRAM, 0, fds)`, sets both FDs to `O_NONBLOCK`, returns `{fds[0], fds[1]}`.
- `write_vsync_event()`: writes a 32-byte struct matching `android::DisplayEventReceiver::Event` wire format:
  ```
  Offset  Size  Field
  0       4     event_type (uint32_t) = 0 (DISPLAY_EVENT_VSYNC)
  4       8     timestamp (int64_t)
  12      4     count (uint32_t)
  16      8     vsync_id (uint64_t)
  24      4     padding (reserved)
  ```
- `close()`: calls `::close()` on both FDs.

**Boundary -- never does:**
- Does not implement a full SurfaceFlinger. It is a byte-instrument, not a model.
- Does not handle HOTPLUG, REFRESH, or CONTENT_ORIENTATION events in MVP.

---

## 2. Data Flow Design

### VSync Pulse -> Frame Callback Execution

```
SurfaceFlinger hardware timer (60Hz / 16.667ms)
  |
  | VSync pulse (hardware interrupt)
  v
DisplayEventReceiver::NativeReceiver (libui android::DisplayEventReceiver)
  | Reads event from FD pipe
  | Parses Event union: event_type == DISPLAY_EVENT_VSYNC
  | Extracts: VsyncEventData{timestamp, count, vsync_id}
  v
DisplayEventReceiver::m_vsync_callback_(VsyncEventData)
  | Callback is [self = shared_ptr<Choreographer>] lambda
  v
Choreographer::on_vsync(const VsyncEventData& data)
  | frame_time = data.timestamp
  | Posts MSG_DO_FRAME to Looper:
  |   send_message(Message{.callback = [self, frame_time] { self->do_frame(frame_time); }}, nullptr)
  v
Looper::loop() processes message
  | Executes callback on Looper thread
  v
Choreographer::do_frame(int64_t frame_time_nanos)
  | start_nanos = steady_clock::now() (nanos)
  | Jitter: if (start_nanos - frame_time_nanos >= frame_interval)
  |   frame_time_nanos = start_nanos - ((start_nanos - frame_time_nanos) % frame_interval)
  | Backward check: if (frame_time_nanos > start_nanos) -> skip, schedule next
  | Skipped frame: if (start_nanos - m_last_frame_time_nanos > 2 * frame_interval)
  |   m_skipped_frames_++
  | Execute stages in order:
  |   for type in [INPUT, ANIMATION, INSETS_ANIMATION, TRAVERSAL, COMMIT]:
  |     entries = extract_due_callbacks(type, frame_time_nanos)
  |     for entry in entries:
  |       try { entry.callback(frame_time_nanos); } catch (...) { log; }
  |   if (m_traverser_) m_traverser_()
  | m_last_frame_time_nanos_ = frame_time_nanos
  | m_frame_pending_ = false
  | m_skipped_frames_ = 0
  | schedule_frame_locked()
  v
Choreographer::schedule_frame_locked()
  | m_frame_scheduled_ = steady_clock::now() + frame_interval
  | m_frame_pending_ = true
  | m_display_event_receiver_->schedule_vsync()
  v
DisplayEventReceiver::schedule_vsync()
  | m_native_->requestVsync()
  v
SurfaceFlinger schedules next VSync pulse
```

**Null/missing value handling at each point:**
- At VSync callback: if `self` is null (Choreographer destroyed), the lambda is a no-op. No crash.
- At `do_frame` backward time check: skips frame entirely, returns early, schedules next. No callbacks executed.
- At callback execution: if callback is null (should not happen with `std::function`), the call is a no-op. Exception caught, logged, next callback continues.
- At traverser: if `m_traverser_` is empty (no ViewRootImpl registered), skipped. No crash.
- At `schedule_frame_locked()`: if `m_display_event_receiver_` is null (should not happen), throws `std::runtime_error`.

### Callback Posting Pipeline

```
post_frame_callback(FrameCallback cb)
  | now = steady_clock::now() (nanos)
  | entry = CallbackEntry{due_time: now, callback: std::move(cb)}
  | queue = m_callback_queues_[TRAVERSAL]
  | it = lower_bound(queue.begin(), queue.end(), entry.due_time,
  |     [](const CallbackEntry& e, int64_t t) { return e.due_time < t; })
  | queue.insert(it, std::move(entry))
  | if (!m_frame_pending_) schedule_frame_locked()
```

**Null/missing value handling:**
- If `cb` is null at post time: `std::move` of empty `std::function` is valid. The entry will be a no-op at execution time.
- If `schedule_frame_locked()` is called but `m_display_event_receiver_` is null: throws `std::runtime_error`.

### ViewRootImpl Traverser Registration Pipeline

```
ViewRootImpl::set_view(shared_ptr<View> view)
  | view_ = view
  | if (view_ && m_choreographer_):
  |   choreo = m_choreographer_.lock()
  |   if (choreo):
  |     strong_self = shared_from_this()
  |     choreo->set_traverser([strong_self]() {
  |       if (strong_self) strong_self->perform_traversals();
  |     })
  |     m_choreographer_set_ = true
  | else:
  |   // No choreographer or no view: no traverser registered
  |   // ViewRootImpl continues to work without choreographer (backward compatible)
```

**Null/missing value handling:**
- If `m_choreographer_` is empty: no traverser registered. Backward compatible.
- If `m_choreographer_.lock()` returns `nullptr` (Choreographer destroyed): no traverser registered. No crash.
- If `strong_self` is null (ViewRootImpl destroyed): traverser is no-op. No crash.

---

## 3. Interface Design

### Internal Interfaces

```cpp
// DisplayEventReceiver -> Choreographer: VSync event delivery
// Owner: Choreographer (consumer defines what it needs)
// Implementer: DisplayEventReceiver (producer delivers)
// Contract: DisplayEventReceiver invokes the callback with parsed VsyncEventData
// Precondition: Callback was set via constructor parameter
// Postcondition: Callback is invoked on the Looper thread with valid data
// Error contract: If native receiver fails to read, callback is not invoked (lossy, VSync is periodic)

// Choreographer -> Looper: Message posting for doFrame
// Owner: Choreographer (consumer)
// Implementer: Looper (producer, existing)
// Contract: send_message schedules a callback for execution on the Looper thread
// Precondition: Looper is running (loop() called)
// Postcondition: Callback will be executed exactly once on the Looper thread
// Error contract: If Looper is quitting, message may be dropped silently (existing Looper behavior)

// Choreographer -> ViewRootImpl: Traverser invocation
// Owner: Choreographer (consumer defines traverser type)
// Implementer: ViewRootImpl (producer sets the traverser function)
// Contract: set_traverser(std::function<void()>) stores a callable invoked during TRAVERSAL stage
// Precondition: Traverser is set before do_frame is called
// Postcondition: Traverser is invoked exactly once during the TRAVERSAL stage
// Error contract: If traverser throws, exception is caught and logged (does not break frame loop)

// DisplayEventReceiver -> NativeReceiver: VSync scheduling and event reading
// Owner: DisplayEventReceiver (consumer)
// Implementer: NativeReceiver (producer, either real or mock)
// Contract: NativeReceiver provides getFd(), requestVsync(), close()
// Precondition: NativeReceiver is constructed
// Postcondition: FD is valid, requestVsync() schedules a VSync pulse
// Error contract: getFd() returns -1 on failure (checked before Looper registration)
```

### Error Type Hierarchy

```cpp
// Base
class ChoreographerError : public std::runtime_error {
public:
    explicit ChoreographerError(const std::string& msg) : std::runtime_error(msg) {}
};

// Construction errors
class NoLooperOnThreadError : public ChoreographerError {
public:
    NoLooperOnThreadError() : ChoreographerError("Choreographer: no Looper on this thread") {}
};

class DisplayEventReceiverCreationError : public ChoreographerError {
public:
    DisplayEventReceiverCreationError() : ChoreographerError("Choreographer: DisplayEventReceiver creation failed") {}
};

// VSync timing errors
class BackwardFrameTimeError : public ChoreographerError {
public:
    BackwardFrameTimeError(int64_t frame_time, int64_t now)
        : ChoreographerError("Choreographer: frame time went backward"),
          frame_time_(frame_time), now_(now) {}
    int64_t frame_time_;
    int64_t now_;
};

// Resource errors
class DisposedReceiverError : public ChoreographerError {
public:
    DisposedReceiverError() : ChoreographerError("Choreographer: DisplayEventReceiver is disposed") {}
};
```

### Interface Ownership

| Interface | Owner (consumer) | Implementer (producer) |
|---|---|---|
| VSync callback | Choreographer | DisplayEventReceiver |
| Message posting | Choreographer | Looper (existing) |
| Traverser function | Choreographer | ViewRootImpl |
| FD event reading | DisplayEventReceiver | NativeReceiver (libui or mock) |
| VSync scheduling | DisplayEventReceiver | NativeReceiver (libui or mock) |

---

## 4. Structural Design

```
core/cpp/
+-- include/android/view/
|   +-- DisplayEventReceiver.h          [NEW] VSync receiver public header
|   +-- Choreographer.h                 [NEW] Frame loop singleton header
|   +-- ViewRootImpl.h                  [MODIFIED] Add weak_ptr<Choreographer>, enable_shared_from_this
+-- src/android/view/
|   +-- DisplayEventReceiver.cpp        [NEW] VSync receiver implementation
|   +-- Choreographer.cpp               [NEW] Frame loop implementation
|   +-- ViewRootImpl.cpp                [MODIFIED] Add choreographer integration
+-- include/android_mock/ui/
|   +-- DisplayEventReceiver.h          [NEW] Mock native receiver for host builds
+-- tests/
|   +-- mock_display_event_receiver.h   [NEW] Pipe-based VSimulator
|   +-- display_event_receiver_test.cpp [NEW] DisplayEventReceiver unit tests
|   +-- choreographer_test.cpp          [NEW] Choreographer unit tests
|   +-- view_root_impl_choreographer_test.cpp [NEW] Integration tests
+-- CMakeLists.txt                      [MODIFIED] Add new source files
+-- tests/CMakeLists.txt                [MODIFIED] Add new test files
```

**Import direction rules:**

| Component | May import from | Must never import from |
|---|---|---|
| `DisplayEventReceiver.h` | `android/os/Looper.h`, `<memory>`, `<functional>`, `<cstdint>` | `Choreographer.h` (would create circular dependency) |
| `DisplayEventReceiver.cpp` | `DisplayEventReceiver.h`, `android_mock/ui/DisplayEventReceiver.h` (HOST_BUILD), `<ui/DisplayEventReceiver.h>` (non-HOST), `<poll.h>`, `<unistd.h>` | `Choreographer.cpp` |
| `Choreographer.h` | `DisplayEventReceiver.h`, `android/os/Looper.h`, `<array>`, `<memory>`, `<functional>`, `<cstdint>` | `ViewRootImpl.h` (would create circular dependency; choreographer has no knowledge of views) |
| `Choreographer.cpp` | `Choreographer.h`, `DisplayEventReceiver.h`, `<chrono>`, `<exception>`, `<iostream>` (for HOST_BUILD logging) | `ViewRootImpl.cpp` |
| `ViewRootImpl.h` (modified) | `Choreographer.h`, `<memory>` | `Choreographer.cpp` |
| `ViewRootImpl.cpp` (modified) | `ViewRootImpl.h`, `Choreographer.h`, existing includes | `DisplayEventReceiver.cpp` |
| `mock_display_event_receiver.h` | `<sys/socket.h>`, `<fcntl.h>`, `<unistd.h>`, `<cstring>` | Any production headers |
| `android_mock/ui/DisplayEventReceiver.h` | `<sys/socket.h>`, `<unistd.h>`, `<fcntl.h>`, `<cstdint>` | Any production `android::view` headers |

**Key structural constraint:** Choreographer and ViewRootImpl have a one-way dependency: ViewRootImpl knows about Choreographer (for traverser registration), but Choreographer does NOT know about ViewRootImpl. Choreographer only knows about `std::function<void()>` traverser. This avoids circular include dependencies and keeps Choreographer generic.

---

## 5. State & Behaviour Design

### Choreographer Frame Loop State Machine

```
         +--------------------------------------------------------------+
         |                                                              |
       IDLE ----[post_frame_callback]--> SCHEDULED ----[VSync arrives]-> DO_FRAME
         |                                  |                            |
         |                             [frame_pending=true]      [callbacks execute]
         |                                                              |
         |                                                         [schedule_frame_locked()]
         |                                  <---------------------[m_frame_pending_=false]
         |                                                              |
         |                                                         IDLE
         |                                                  (if no new callbacks posted)
         |
         +--[dispose]--> DISPOSED
```

**Transitions:**

| From | To | Guard | Side effects | Invariant |
|---|---|---|---|---|
| IDLE | SCHEDULED | `!m_frame_pending_` and frame callback posted | `m_frame_pending_ = true`, `schedule_vsync()` called | Exactly one VSync request pending |
| SCHEDULED | DO_FRAME | VSync pulse received via `on_vsync()` | `do_frame(frame_time)` posted to Looper message queue | Frame time is valid (nanos, monotonic) |
| DO_FRAME | SCHEDULED | Callbacks executed, `m_frame_pending_ = false` | `schedule_frame_locked()` called | Next VSync requested |
| DO_FRAME | IDLE | Callbacks executed, no new callbacks posted | `m_frame_pending_ = false`, `m_skipped_frames_ = 0` | System idle until new callback posted |
| IDLE/SCHEDULED | DISPOSED | `dispose()` called | `m_frame_pending_ = false`, VSync cancelled | No more VSync events delivered |

**Backward-time sub-behaviour (within DO_FRAME):**

```
do_frame(frame_time):
    start_nanos = steady_clock::now()
    if frame_time > start_nanos:
        // Frame time went backward -- skip
        schedule_frame_locked()
        return  // DO_FRAME -> IDLE (no callbacks executed)
```

### Behavioural Scenarios

#### Scenario: VSync-driven frame execution
```
Given: Choreographer created via get_instance() on a thread with a running Looper
       DisplayEventReceiver mock FD registered with Looper
       A frame callback cb1 posted via post_frame_callback(cb1)
When:  Mock writes VSync event with timestamp 1000000000 to the mock FD
       Looper::poll_once() is called (processes FD event -> on_vsync -> posts do_frame)
       Looper::poll_once() is called again (processes do_frame message)
Then:  cb1 is invoked with frameTimeNanos = 1000000000
       m_last_frame_time_nanos_ = 1000000000
       m_frame_pending_ = false
       Next VSync is scheduled (schedule_vsync() called)
```

#### Scenario: Staged callback execution order
```
Given: Choreographer created with mock VSync
       Callback cb_input posted to INPUT stage (via internal test helper)
       Callback cb_animation posted to ANIMATION stage
       Callback cb_traversal posted to TRAVERSAL stage
When:  VSync pulse arrives, do_frame executes
Then:  cb_input executes before cb_animation
       cb_animation executes before cb_traversal
       cb_traversal executes before m_traverser_ (if set)
```

#### Scenario: Traverser triggers ViewRootImpl
```
Given: ViewRootImpl created, set_choreographer(weak_ptr<Choreographer>) called
       set_view(mock_view) called (registers traverser)
When:  VSync pulse arrives, do_frame executes TRAVERSAL stage
Then:  m_traverser_() is called after all TRAVERSAL callbacks
       perform_traversals() is invoked on ViewRootImpl
       perform_measure(), perform_layout(), perform_draw() are called
```

#### Scenario: Skipped frame detection
```
Given: Choreographer created, last frame time was 1000000000
       Frame interval is 16666667ns (60Hz)
When:  do_frame is called with frame_time = 1000000000 + 4 * 16666667 (4 frames late)
       start_nanos = 1000000000 + 4 * 16666667
Then:  m_skipped_frames_ incremented (gap > 2 * frame_interval)
       Warning logged (if skipped_frames > kSkippedFrameWarningLimit)
       frame_time resynced to nearest past VSync
       Callbacks executed with resynced frame_time
```

#### Scenario: Backward frame time skips frame
```
Given: Choreographer created, last frame time was 1000000000
When:  do_frame is called with frame_time = 2000000000 (in the future relative to start_nanos)
Then:  No callbacks are executed
       No traverser is called
       schedule_frame_locked() is called (next VSync requested)
       m_last_frame_time_nanos_ is NOT updated
```

#### Scenario: Callback exception does not break frame loop
```
Given: Choreographer created with mock VSync
       Callback cb_throwing posted that throws std::runtime_error("fail")
       Callback cb_ok posted that sets a flag to true
When:  VSync pulse arrives, do_frame executes
Then:  cb_throwing is caught, error logged
       cb_ok is still executed, flag is set to true
       Frame continues normally (next VSync scheduled)
```

#### Scenario: Callback removal prevents execution
```
Given: Choreographer created with mock VSync
       Callback cb posted via post_frame_callback(cb)
When:  remove_frame_callback(cb) is called before VSync pulse
       VSync pulse arrives
Then:  cb is NOT invoked (removed from queue)
```

#### Scenario: Delayed callback waits for correct frame
```
Given: Choreographer created with mock VSync
When:  post_frame_callback_delayed(cb, 500) is called (500ms delay)
       do_frame is called with frame_time = now (before due time)
Then:  cb is NOT executed (due_time > frame_time)
       do_frame is called again with frame_time = now + 600ms (after due time)
Then:  cb IS executed (due_time <= frame_time)
```

#### Scenario: Weak_ptr expiry does not crash
```
Given: ViewRootImpl created
       Shared_ptr<Choreographer> choreo = get_instance()
       set_choreographer(choreo) called
       choreo goes out of scope (shared_ptr destroyed)
When:  set_view(mock_view) called
Then:  m_choreographer_.lock() returns nullptr
       No traverser is registered
       No crash
```

#### Scenario: No Looper on thread throws
```
Given: Thread has no Looper (Looper::prepare() not called)
When:  Choreographer::get_instance() is called
Then:  std::runtime_error is thrown with message "Choreographer: no Looper on this thread"
```

#### Scenario: DisplayEventReceiver creation failure throws
```
Given: Thread has a Looper
       DisplayEventReceiver constructor fails (mock returns invalid FD)
When:  Choreographer::get_instance() is called
Then:  std::runtime_error is thrown (no fallback to polling)
```

---

## 6. Dependency Design

| Component | Depends on | Reason | Direction rule |
|---|---|---|---|
| `DisplayEventReceiver` | `os::Looper` | FD registration via `add_fd()`/`remove_fd()` | receiver -> looper (infrastructure) |
| `DisplayEventReceiver` | `NativeReceiver` (libui or mock) | VSync event source | receiver -> native (abstraction) |
| `Choreographer` | `DisplayEventReceiver` | VSync input for frame loop | choreographer -> receiver (feature -> infra) |
| `Choreographer` | `os::Looper` (indirectly) | Message posting via `send_message()` | choreographer -> looper (via receiver) |
| `ViewRootImpl` | `Choreographer` | Traverser registration | viewroot -> choreographer (integration) |
| `ViewRootImpl` | `std::enable_shared_from_this` | `shared_ptr` capture in traverser callback | viewroot -> std::lib (language) |
| `MockDisplayEventReceiver` | (none) | Pure test utility | test -> system calls only |
| `android_mock/ui/DisplayEventReceiver` | (none) | Pure mock for host builds | mock -> system calls only |

**Redesigned dependencies:**
- None. The dependency graph is acyclic and respects layering: infrastructure (Looper, native receiver) -> feature (DisplayEventReceiver, Choreographer) -> integration (ViewRootImpl).
- ViewRootImpl depends on Choreographer (not vice versa), avoiding circular dependency.
- Choreographer depends on DisplayEventReceiver (not vice versa), maintaining unidirectional flow.

---

## 7. Design Pattern Application

### Thread-Local Singleton

```
Pattern: Thread-local singleton via inline thread_local
Application: Choreographer::s_thread_instance is inline thread_local shared_ptr.
  get_instance() checks nullptr, creates on first access.
  s_main_instance is a plain static shared_ptr set when the current thread
  is the main thread (os::Looper::get_main_looper() == looper).
  Mirrors Looper's pattern exactly:
    Looper: static thread_local std::shared_ptr<Looper> s_thread_local_looper
    Choreographer: static inline thread_local std::shared_ptr<Choreographer> s_thread_instance
  No std::call_once needed (C++17 inline thread_local is thread-safe for initialization).
  Test impact: Each test thread gets its own Choreographer instance. Tests that
  share a thread must call Choreographer::s_thread_instance.reset() between tests.
```

### RAII FD Management

```
Pattern: RAII via destructor calling dispose()
Application: DisplayEventReceiver destructor calls dispose() if not already disposed.
  dispose() unregisters from Looper, closes native receiver FD.
  Matches InputEventReceiver pattern exactly (destructor calls dispose()).
  Move constructor transfers ownership; source left in disposed state.
  Prevents FD leaks even if Choreographer is destroyed mid-frame.
```

### Sorted-Vector Callback Queue

```
Pattern: Sorted insertion with std::lower_bound + std::vector::insert
Application: Each callback stage has a std::vector<CallbackEntry> sorted by due_time.
  post_frame_callback: lower_bound finds insertion point, insert maintains order. O(n).
  do_frame: upper_bound finds first non-due entry, erase removes all due entries. O(n).
  remove_frame_callback: remove_if with std::function equality. O(n) per queue.
  Cache-friendly: contiguous memory vs. linked-list indirection.
  Constitution II (Zero-Cost): std::vector is the simplest container that provides
  sorted access. No custom allocator or free-list needed (std::function already heap-allocated).
```

### Weak-Ptr Integration

```
Pattern: std::weak_ptr for non-owning cross-component reference
Application: ViewRootImpl holds std::weak_ptr<Choreographer>.
  set_view() locks the weak_ptr. If null (Choreographer destroyed), no traverser registered.
  Traverser captures shared_ptr<ViewRootImpl> via shared_from_this() to keep ViewRootImpl alive.
  Traverser checks strong_self before calling perform_traversals().
  Prevents dangling references and use-after-free.
  Allows Choreographer to be destroyed independently of ViewRootImpl.
```

---

## 8. Design Trade-offs

### Decision: Callback queue -- sorted `std::vector` vs. free-list linked list

**Option A: Sorted `std::vector<CallbackEntry>`**
- Pro: Cache-friendly contiguous memory. O(n) insert is fast for small queues (typical: 1-5 callbacks per stage). `std::lower_bound` binary search is O(log n).
- Con: O(n) insert and erase require shifting elements. Not optimal with hundreds of callbacks.

**Option B: Free-list linked list (Java pattern)**
- Pro: O(1) insertion. No shifting. Java uses this because Java object allocation is expensive and the freelist amortizes allocation cost.
- Con: Pointer indirection on every access (cache misses). More complex code (next/prev pointers, freelist management). `std::function` is already heap-allocated at capture time, so per-frame allocation is unnecessary.

**Option C: `std::set` (RB-tree)**
- Pro: O(log n) insert, O(log n) erase. No shifting.
- Con: Node allocation on every insert. Cache-unfriendly. Overkill for typical queue sizes.

**Chosen: Option A (sorted `std::vector`)**
- Rationale: Constitution II requires zero-cost abstractions. For the typical case (1-5 callbacks per stage), `std::vector` with binary search is faster than linked-list due to cache locality. The clarifications document explicitly recommends this: "sorted vector is cache-friendly compared to a linked list. The freelist pattern from Java exists because Java objects are expensive to allocate. `std::function` allocation happens once at capture time, so per-frame allocation is unnecessary." If profiling later shows this is a bottleneck, switch to Option B.

### Decision: Exception handling in callback dispatch -- catch-all vs. no-catch

**Option A: `try/catch(...)` around each callback**
- Pro: A single callback exception cannot break the frame loop. This matches Java's behavior.
- Con: Hides programming errors (bugs in callbacks are silently swallowed).

**Option B: No catch, let exceptions propagate**
- Pro: Bugs are immediately visible. The frame loop crashes, which is easier to debug.
- Con: A single bad callback breaks the entire frame (no more frames until the bug is fixed).

**Chosen: Option A (catch-all)**
- Rationale: The frame loop is a real-time system. A single buggy callback should not starve the display of frames. Java Choreographer catches exceptions and logs them. The constitution's Error Handling principle (Safety dimension V) says exceptions are reserved for "truly exceptional, unrecoverable circumstances" -- a callback throwing is a recoverable error (log and continue).

### Decision: VSync-only mode -- no polling fallback

**Option A: VSync only (no fallback)**
- Pro: Halves code complexity. No non-VSync frame delay calculation, no separate `MSG_DO_FRAME` handling path, no `DEFAULT_FRAME_DELAY` constant.
- Con: Fails entirely if no display / SurfaceFlinger is unreachable.

**Option B: VSync with polling fallback**
- Pro: Works on headless / CI environments without a display.
- Con: Adds ~60 lines of complex polling logic. Java's non-VSync path has its own complete `doFrame` handling, frame delay calculation, and scheduling logic.

**Chosen: Option A (VSync only)**
- Rationale: The clarifications document explicitly states "VSYNC-only mode. No non-VSYNC fallback." The C++ MVP is not a Java compatibility layer; it is a native implementation targeting devices with real displays. CI testing uses mock DisplayEventReceiver (pipe-based VSimulator), so tests do not need a polling fallback. If a headless mode is later required, it can be added as a separate feature.

### Decision: Traverser integration -- `std::function` vs. virtual method

**Option A: `std::function<void()>` traverser stored in Choreographer**
- Pro: No virtual functions. No inheritance coupling. Choreographer does not know about ViewRootImpl. Any callable can be set as traverser.
- Con: `std::function` has small allocation overhead (one allocation per `set_traverser` call when capturing a lambda).

**Option B: Virtual `on_traversal()` method on a base class**
- Pro: Zero allocation. Static dispatch via vtable.
- Con: Requires Choreographer to hold a raw pointer to a base class. Creates inheritance coupling. ViewRootImpl must inherit from a Choreographer-aware base.

**Chosen: Option A (`std::function`)**
- Rationale: Constitution II (Zero-Cost) prefers static dispatch, but the `std::function` allocation happens once (at `set_traverser` time, not per-frame). The hot path (`m_traverser_()` in `do_frame`) is a single indirect call through `std::function::operator()`, which is comparable to a vtable call. More importantly, this design avoids inheritance coupling and keeps Choreographer independent of ViewRootImpl. The clarifications document confirms: "The traverser is a `std::function<void(int64_t)>` that captures the ViewRootImpl shared_ptr."

---

## 9. Extension Design

### Extension: Additional callback stages (future Java stages beyond COMMIT)

**Anticipated change:** Java Choreographer has no stages beyond COMMIT=4, but the enum could be extended for new stages (e.g., PREDRAW, POSTDRAW).

**Current design accommodation:**
- `CallbackType::COUNT = 5` defines the array size. Adding a new stage means adding a new enum value and incrementing COUNT.
- `m_callback_queues_` is `std::array<..., COUNT>`. If COUNT changes, the array size changes automatically.
- `do_frame` iterates `for (int i = 0; i < static_cast<int>(CallbackType::COUNT); ++i)`. No hardcoded stage list.
- Adding a stage is a one-line change (new enum value) plus a one-line change (increment COUNT).

**What would break it:**
- Hardcoded stage iteration (e.g., `for (auto type : {INPUT, ANIMATION, TRAVERSAL, COMMIT})`).
- Stage-specific logic in `do_frame` that does not go through the generic queue extraction.

### Extension: FrameTimeline / vsync_id / frame deadline tracking

**Anticipated change:** Java Choreographer tracks `VsyncEventData.vsync_id`, computes `getFrameDeadline()`, and provides `getExpectedPresentationTimeNanos()`. These are used by the renderer to schedule work within the frame deadline.

**Current design accommodation:**
- `VsyncEventData` struct already includes `count` and `vsync_id` fields. The DisplayEventReceiver parses and delivers them.
- Choreographer stores `m_frame_scheduled_` but could be extended to store `m_last_vsync_id_` and `m_frame_deadline_nanos_`.
- `get_frame_interval_nanos()` already delegates to DisplayEventReceiver. Adding `get_vsync_id()` and `get_frame_deadline_nanos()` would follow the same pattern.

**What would break it:**
- If `VsyncEventData` were defined inside `Choreographer` instead of `DisplayEventReceiver`, changing the struct would require changes in both components.
- If `do_frame` consumed `VsyncEventData` fields directly instead of through the callback interface.

### Extension: Non-VSync polling fallback

**Anticipated change:** Add a timer-based polling path for environments without a display (headless CI, some embedded targets).

**Current design accommodation:**
- `schedule_frame_locked()` calls `m_display_event_receiver_->schedule_vsync()`. This could be replaced with a timer-based scheduler.
- `on_vsync()` posts `do_frame` to the Looper. A timer callback could post the same message.
- The `do_frame()` method is VSync-agnostic: it receives `frame_time_nanos` and processes callbacks. It does not depend on how the frame time was determined.

**What would break it:**
- If `schedule_frame_locked()` directly called `m_native_->requestVsync()` (bypassing DisplayEventReceiver).
- If `on_vsync()` were tied to a specific VSync event structure.

### Extension: Multiple Choreographers per ViewRootImpl

**Anticipated change:** A single ViewRootImpl might need to coordinate with multiple Choreographers (e.g., different refresh rates for different displays).

**Current design accommodation:**
- `set_choreographer()` takes a `weak_ptr<Choreographer>`. Adding `set_choreographer_multi()` would accept a vector of weak_ptrs.
- The traverser registration in `set_view()` is a single `std::function<void()>`. Extending to multiple traversers is additive.

**What would break it:**
- If `m_choreographer_` were a `shared_ptr` instead of `weak_ptr` (ownership semantics would need redesign for multiple instances).

---

## Appendix: Constitution Compliance Summary

| Principle | Compliance |
|---|---|
| I. Safety-First Design | RAII for all resources (FD closed in destructor, smart pointers exclusively). `std::function` null checks. No pointer arithmetic. All members initialized. `std::expected` not needed (errors are exceptional, not recoverable). |
| II. Zero-Cost Abstractions | Sorted `std::vector` for callback queue (cache-friendly). No virtual functions in hot path (`do_frame` is direct call). `enum class` with direct array indexing. `std::function` overhead is one allocation at capture time, zero per dispatch. |
| III. TDD | Tests defined for every component: 8 DisplayEventReceiver tests, 14 Choreographer tests, 4 integration tests. Coverage target >80%. |
| IV. Plan as Source of Truth | Design aligns with plan.md sections 1.1-1.5. Tasks map directly to design components. |
| V. Tech Stack Deliberation | C++23, CMake, GoogleTest, smart pointers, `std::function`, `std::expected` (not used in MVP but available). No new dependencies beyond existing Looper/Handler and libui. |
