# Tasks: Choreographer

**Feature ID:** 005  
**Plan:** /home/roto/git/android-platform-frameworks-base/specs/005-choreographer/plan.md  
**Spec:** /home/roto/git/android-platform-frameworks-base/core/cpp/specs/android/view/Choreographer.md  
**Clarifications:** /home/roto/git/android-platform-frameworks-base/core/cpp/specs/android/view/Choreographer_clarifications.md  
**DisplayEventReceiver Spec:** /home/roto/git/android-platform-frameworks-base/core/cpp/specs/android/view/DisplayEventReceiver.md  
**Generated:** 2026-05-30  
**Status:** Ready for Implementation

---

## Summary

**Total tasks:** 14  
**Estimated phases:** 4 (Phase 0-3)  
**Parallelisable tasks:** 4  
**Checkpoints:** 4

User stories covered:
- Choreographer frame loop (VSync reception, staged callback execution, traversal trigger)
- DisplayEventReceiver (VSync event delivery via Looper FD registration)
- ViewRootImpl integration (weak_ptr<Choreographer> + traverser registration)

---

## Phase 0: Research

### T-01 · Verify libui availability and define mock strategy
**Phase:** 0  
**Depends on:** —  
**User story:** All  
**Description:**  
Verify that `<ui/DisplayEventReceiver.h>` (android::DisplayEventReceiver from libui) is available in the build environment. If not available on host builds, define the mock strategy using a pipe-based VSimulator similar to `MockInputChannel` in `core/cpp/tests/mock_input_channel.h`.

Action items:
1. Check if `<ui/DisplayEventReceiver.h>` exists in the NDK or system include paths:
   ```bash
   find /opt/android-ndk -name "DisplayEventReceiver.h" 2>/dev/null
   find /usr/include -name "DisplayEventReceiver.h" 2>/dev/null
   ```
2. Check if `<ui/DisplayEventReceiver.h>` exists in `core/cpp/include/android_mock/`:
   ```bash
   ls /home/roto/git/android-platform-frameworks-base/core/cpp/include/android_mock/
   ```
3. If not available, create `core/cpp/include/android_mock/ui/DisplayEventReceiver.h` with a mock `android::DisplayEventReceiver` class that:
   - Creates an AF_UNIX socket pair in its constructor
   - Exposes `int getFd()` returning the read-end FD
   - Exposes `void requestVsync()` (no-op for mock)
   - Exposes `void close()` that closes both FDs
   - Has a static method `write_vsync_event(int fd, int64_t timestamp, uint32_t count)` that writes a wire-format VSync event to the write-end FD
4. Document findings in `specs/005-choreographer/research.md`.

**Acceptance criteria:**
- [x] libui header availability confirmed (either found or mock created)
- [x] If mock created: `core/cpp/include/android_mock/ui/DisplayEventReceiver.h` exists with `DisplayEventReceiver` class
- [x] Mock class has `getFd()`, `requestVsync()`, `close()`, and `write_vsync_event()` methods
- [x] research.md documents the decision

⚠️ **Pitfall:** The native `android::DisplayEventReceiver::Event` wire format must match what the mock writes. Study the AOSP source for the exact binary layout of `DisplayEventReceiver::Event` union to ensure the mock produces correctly formatted events.

---

## ✅ Checkpoint 1: Research Complete

Before proceeding to Phase 1, verify:
- [x] libui header availability confirmed or mock strategy defined
- [x] Mock `DisplayEventReceiver` header created if needed
- [x] Looper `add_fd`/`remove_fd`/`poll_once` integration pattern understood from `InputEventReceiver` reference
- [x] Thread-local singleton pattern confirmed from existing `Looper` implementation

---

## Phase 1: DisplayEventReceiver

### T-02 · Create DisplayEventReceiver header
**Phase:** 1  
**Depends on:** T-01  
**User story:** All  
**Parallel:** [P]  
**Description:**  
Create `core/cpp/include/android/view/DisplayEventReceiver.h` with the following class definition:

```cpp
#pragma once

#include <android/os/Looper.h>
#include <cstdint>
#include <functional>
#include <memory>

#if defined(HOST_BUILD)
#include <android_mock/ui/DisplayEventReceiver.h>
#else
#include <ui/DisplayEventReceiver.h>
#endif

namespace android::view {

struct VsyncEventData {
    int64_t timestamp;        // VSync timestamp in nanos (from hardware)
    uint32_t count;           // VSync sequence count
    uint64_t vsync_id;        // Monotonic VSync identifier
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

    // Non-copyable, movable
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

} // namespace android::view
} // namespace android
```

Key details:
- Use `#if defined(HOST_BUILD)` to conditionally include mock vs. native header
- `NativeReceiver` is a forward-declared opaque type implemented in the `.cpp` file
- Default frame interval is 60Hz (16,666,667 ns)
- All public methods documented with doxygen comments

**Acceptance criteria:**
- [x] File exists at `core/cpp/include/android/view/DisplayEventReceiver.h`
- [x] Header compiles independently (no missing dependencies)
- [x] `VsyncEventData` struct has `timestamp`, `count`, `vsync_id` fields
- [x] `DisplayEventType` enum has `VSYNC`, `HOTPLUG`, `REFRESH`, `CONTENT_ORIENTATION` values
- [x] Class is non-copyable, movable
- [x] All public methods declared with correct signatures

---

### T-03 · Create DisplayEventReceiver implementation
**Phase:** 1  
**Depends on:** T-02  
**User story:** All  
**Description:**  
Create `core/cpp/src/android/view/DisplayEventReceiver.cpp` implementing the header from T-02.

Implementation details:

1. **NativeReceiver inner class** (private, in `.cpp`):
   - On non-HOST builds: wraps `android::DisplayEventReceiver` from libui. Constructor calls `DisplayEventReceiver()` and stores the FD. `getFd()` returns `receiver.getFd()`. `requestVsync()` calls `receiver.requestVsync()`. `close()` calls `receiver.close()`.
   - On HOST_BUILD: wraps the mock from `android_mock/ui/DisplayEventReceiver.h`. Same interface.

2. **Constructor**: Takes `std::shared_ptr<os::Looper> looper` and `VsyncCallback callback`. Stores both. Creates `m_native_`. Sets `m_fd_ = m_native_->getFd()`. Calls `set_vsync_callback(callback)`.

3. **`schedule_vsync()`**: If not disposed, calls `m_native_->requestVsync()`.

4. **`register_with_looper()`**: If not already registered, calls `m_fd_watcher_cookie_ = m_looper_->add_fd(m_fd_, POLLIN, [](int fd, int events, void* data) -> int { static_cast<DisplayEventReceiver*>(data)->on_data_available(); return 1; }, this)`. Sets `m_fd_watcher_registered_ = true`.

5. **`unregister_from_looper()`**: If registered, calls `m_looper_->remove_fd(m_fd_watcher_cookie_)`. Sets `m_fd_watcher_registered_ = false`.

6. **`on_data_available()`**: Calls `dispatch_events()`.

7. **`dispatch_events()`**: Reads from `m_native_->getFd()`. For HOST_BUILD mock, the event data is written via `write_vsync_event()`. Parse the event and if it is a VSync event, call `m_vsync_callback_(VsyncEventData{timestamp, count, vsync_id})`. For native build, parse `android::DisplayEventReceiver::Event` union.

8. **`dispose()`**: Calls `unregister_from_looper()`. Sets `m_disposed_ = true`. If `m_native_` exists, calls `m_native_->close()`.

9. **Move constructor/assignment**: Transfer ownership of `m_native_`, `m_fd_`, `m_fd_watcher_cookie_`, `m_fd_watcher_registered_`, and `m_disposed_` state. Reset source to disposed state.

10. **Destructor**: Calls `dispose()` if not already disposed.

Pattern to follow: Exactly replicate the `InputEventReceiver` pattern from `core/cpp/src/android/view/InputEventReceiver.cpp` for FD registration, Looper callback, and disposal.

**Acceptance criteria:**
- [x] File exists at `core/cpp/src/android/view/DisplayEventReceiver.cpp`
- [x] Constructor stores looper and callback, creates native receiver
- [x] `schedule_vsync()` delegates to native `requestVsync()`
- [x] `register_with_looper()` calls `m_looper_->add_fd()` with correct callback
- [x] `unregister_from_looper()` calls `m_looper_->remove_fd()`
- [x] `dispose()` unregisters FD, sets disposed flag, closes native receiver
- [x] Destructor calls `dispose()` if needed
- [x] Move semantics transfer state correctly
- [x] HOST_BUILD conditional compiles with mock path

⚠️ **Pitfall:** The FD callback in `add_fd` takes a `std::function<int(int, int, void*)>`. Capture `this` as raw pointer (safe because DisplayEventReceiver lifetime is managed by shared_ptr and all calls are serialized on the Looper thread). Do NOT capture shared_ptr in the FD callback -- it creates a reference cycle that prevents cleanup.

---

### T-04 · Create mock DisplayEventReceiver for host tests
**Phase:** 1  
**Depends on:** T-02  
**User story:** All  
**Parallel:** [P]  
**Description:**  
Create `core/cpp/tests/mock_display_event_receiver.h` providing a pipe-based VSimulator for testing DisplayEventReceiver on host builds.

The mock creates an AF_UNIX socket pair. The read end is exposed as the "FD". The write end is used to inject VSync events. Wire format for a mock VSync event (matching `android::DisplayEventReceiver::Event` binary layout):

```
Offset  Size  Field
0       4     event_type (uint32_t) = 0 (DISPLAY_EVENT_VSYNC)
4       8     timestamp (int64_t)
12      4     count (uint32_t)
16      8     vsync_id (uint64_t)
24      4     padding
```

The header must provide:
```cpp
namespace android {
namespace view {
namespace test {

class MockDisplayEventReceiver {
public:
    // Create a mock receiver. Returns pair of {read_fd, write_fd}.
    static auto create() -> std::pair<int, int>;

    // Write a VSync event to the write FD.
    static void write_vsync_event(int write_fd, int64_t timestamp,
                                  uint32_t count, uint64_t vsync_id);

    // Close both FDs.
    static void close(int read_fd, int write_fd);
};

} // namespace test
} // namespace view
} // namespace android
```

This mock replaces the native `android::DisplayEventReceiver` on host builds. The `NativeReceiver` inner class in `DisplayEventReceiver.cpp` should use this mock when `HOST_BUILD` is defined.

**Acceptance criteria:**
- [x] File exists at `core/cpp/tests/mock_display_event_receiver.h`
- [x] `create()` returns a valid AF_UNIX socket pair
- [x] Both FDs are set to non-blocking mode
- [x] `write_vsync_event()` writes the 32-byte wire format event
- [x] `close()` closes both FDs
- [x] Mock is included by `DisplayEventReceiver.cpp` when `HOST_BUILD` is defined

⚠️ **Pitfall:** The FDs must be set to non-blocking mode (`O_NONBLOCK`) because the Looper's `poll_once()` uses `poll()` which expects non-blocking FDs. If the FD is blocking, `read()` in the mock's event handling could block the Looper thread.

---

### T-05 · Create DisplayEventReceiver tests
**Phase:** 1  
**Depends on:** T-03, T-04  
**User story:** All  
**Description:**  
Create `core/cpp/tests/display_event_receiver_test.cpp` with the following test cases using GoogleTest:

| Test | Purpose |
|------|---------|
| `ConstructorWithValidLooper` | Construction with valid Looper succeeds, FD is valid |
| `ConstructorWithNullLooperThrows` | Null Looper -> `std::invalid_argument` exception |
| `ScheduleVsyncNoopWhenDisposed` | `schedule_vsync()` after `dispose()` does not crash |
| `RegisterUnregisterLooper` | FD registered and unregistered, cookie is valid |
| `VsyncCallbackInvoked` | Mock VSync event triggers callback with correct timestamp |
| `DisposeClosesFd` | FD is closed after `dispose()` |
| `MoveConstructorPreservesState` | Move semantics work correctly, source is disposed |
| `FrameIntervalDefault60Hz` | Default frame interval is 16666667ns |

Test implementation details:
- For `VsyncCallbackInvoked`: Create a `MockDisplayEventReceiver`, create a `DisplayEventReceiver` with a `std::atomic<bool>` flag callback. Use the mock to write a VSync event with timestamp 123456789, count 42, vsync_id 99. Poll the Looper once. Verify the callback was invoked with correct data.
- For `ConstructorWithNullLooperThrows`: Use `EXPECT_THROW` or `ASSERT_ANY_THROW`.
- For `MoveConstructorPreservesState`: Move-construct a new instance, verify source `is_disposed()` returns true, new instance `is_disposed()` returns false.
- For `FrameIntervalDefault60Hz`: Construct and verify `get_frame_interval_nanos() == 16666667`.

Add to `core/cpp/tests/CMakeLists.txt`:
- `display_event_receiver_test.cpp`
- Link against `android_framework_core`
- Include `mock_display_event_receiver.h`

**Acceptance criteria:**
- [x] File exists at `core/cpp/tests/display_event_receiver_test.cpp`
- [x] All 8 test cases compile and pass
- [x] `VsyncCallbackInvoked` verifies timestamp, count, and vsync_id values
- [x] `ConstructorWithNullLooperThrows` verifies exception is thrown
- [x] `MoveConstructorPreservesState` verifies source is disposed after move
- [x] `FrameIntervalDefault60Hz` verifies 16666667ns default
- [x] Build passes: `cmake --build build && ctest -R display_event_receiver`

---

## ✅ Checkpoint 2: DisplayEventReceiver Complete

Before proceeding to Phase 2, verify:
- [x] All DisplayEventReceiver tests pass: `cmake --build build && ctest -R display_event_receiver`
- [x] `is_disposed()` correctly reports disposed state
- [x] FD registration and unregistration works with Looper
- [x] VSync callback receives correct event data from mock
- [x] Move semantics preserve state correctly
- [x] Code coverage >80% for DisplayEventReceiver

---

## Phase 2: Choreographer

### T-06 · Create Choreographer header
**Phase:** 2  
**Depends on:** T-02  
**User story:** All  
**Parallel:** [P]  
**Description:**  
Create `core/cpp/include/android/view/Choreographer.h` with the following class definition:

```cpp
#pragma once

#include <android/view/DisplayEventReceiver.h>
#include <android/os/Looper.h>
#include <array>
#include <cstdint>
#include <functional>
#include <memory>

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

    // -- Factory --
    static auto get_instance() -> std::shared_ptr<Choreographer>;
    static auto get_main_instance() -> std::shared_ptr<Choreographer>;

    // -- Callback Posting --
    void post_frame_callback(FrameCallback cb);
    void post_frame_callback_delayed(FrameCallback cb, int64_t delay_ms);
    void remove_frame_callback(FrameCallback cb);

    // -- Query --
    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;
    [[nodiscard]] auto get_frame_interval_nanos() const -> int64_t;
    [[nodiscard]] auto get_last_frame_time_nanos() const -> int64_t;

    // -- Internal (for ViewRootImpl integration) --
    void set_traverser(std::function<void()> traverser);
    void remove_traverser();

private:
    explicit Choreographer(std::shared_ptr<DisplayEventReceiver> display_event_receiver);
    ~Choreographer();

    Choreographer(const Choreographer&) = delete;
    Choreographer& operator=(const Choreographer&) = delete;

    // -- Frame Loop --
    void do_frame(int64_t frame_time_nanos);
    void schedule_frame_locked();
    void on_vsync(const VsyncEventData& data);

    // -- Callback Queue --
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

    // -- Thread-Local Storage --
    static inline thread_local std::shared_ptr<Choreographer> s_thread_instance = nullptr;
    static inline std::shared_ptr<Choreographer> s_main_instance = nullptr;
};

} // namespace android::view
} // namespace android
```

Key details:
- Inherits `std::enable_shared_from_this` for `shared_from_this()` in VSync callback capture
- `CallbackType` constants match Java's `CALLBACK_*` integer values
- `m_callback_queues_` is an array of 5 sorted vectors (one per stage)
- `s_thread_instance` is `inline thread_local` (C++17+); `s_main_instance` is plain `static`
- Default frame interval is inherited from `DisplayEventReceiver`'s 60Hz default

**Acceptance criteria:**
- [x] File exists at `core/cpp/include/android/view/Choreographer.h`
- [x] Header compiles independently (includes DisplayEventReceiver.h, Looper.h)
- [x] `FrameCallback` type alias is `std::function<void(int64_t)>`
- [x] `CallbackType` enum has all 5 values plus COUNT
- [x] Factory methods `get_instance()` and `get_main_instance()` declared
- [x] Callback posting methods: `post_frame_callback`, `post_frame_callback_delayed`, `remove_frame_callback`
- [x] Query methods: `get_looper`, `get_frame_interval_nanos`, `get_last_frame_time_nanos`
- [x] Internal methods: `set_traverser`, `remove_traverser`
- [x] Thread-local storage declared as `inline thread_local`

---

### T-07 · Create Choreographer implementation
**Phase:** 2  
**Depends on:** T-06, T-03  
**User story:** All  
**Description:**  
Create `core/cpp/src/android/view/Choreographer.cpp` implementing the header from T-06.

Implementation details for each method:

1. **`get_instance()`**:
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

2. **`get_main_instance()`**: Returns `s_main_instance`.

3. **Constructor**: Takes `std::shared_ptr<DisplayEventReceiver>`. Stores it.

4. **`post_frame_callback(FrameCallback cb)`**:
   - Get current time via a monotonic clock (use `std::chrono` converted to nanos, or a stub `system_time_nanos()` helper)
   - Create `CallbackEntry{due_time: now, callback: std::move(cb)}`
   - Insert into `m_callback_queues_[static_cast<int>(CallbackType::TRAVERSAL)]` using `std::lower_bound` for sorted insertion
   - If no frame is pending, call `schedule_frame_locked()`

5. **`post_frame_callback_delayed(FrameCallback cb, int64_t delay_ms)`**:
   - Same as `post_frame_callback` but `due_time = now + delay_ms * 1000000` (convert ms to ns)
   - Insert into TRAVERSAL queue with sorted insertion
   - If no frame pending, call `schedule_frame_locked()`

6. **`remove_frame_callback(FrameCallback cb)`**:
   - Iterate all 5 queues
   - Use `std::remove_if` with `e.callback == cb` predicate, erase from end

7. **`on_vsync(const VsyncEventData& data)`**:
   - Post `do_frame(data.timestamp)` to the Looper using `m_display_event_receiver_->get_looper()->send_message()`:
   ```cpp
   m_display_event_receiver_->get_looper()->send_message(
       Message{.what = 0, .callback = [self = shared_from_this(), frame_time = data.timestamp]() {
           self->do_frame(frame_time);
       }},
       nullptr);
   ```

8. **`do_frame(int64_t frame_time_nanos)`**:
   - `start_nanos = system_time_nanos()` (use monotonic clock)
   - **Jitter calculation**: If `start_nanos - frame_time_nanos >= frame_interval_nanos`, resync: `frame_time_nanos = start_nanos - ((start_nanos - frame_time_nanos) % frame_interval_nanos)`
   - **Backward time check**: If `frame_time_nanos > start_nanos`, skip frame: call `schedule_frame_locked()` and return
   - **Skipped frame detection**: If `start_nanos - m_last_frame_time_nanos > 2 * frame_interval_nanos`, increment `m_skipped_frames_`. If `> kSkippedFrameWarningLimit`, log warning (use `#ifdef HOST_BUILD` with `fprintf(stderr, "...")` or `android/log.h`'s `__android_log_print`)
   - **Execute callbacks in stage order**: For each `CallbackType` from 0 to 4:
     - Extract due callbacks (due_time <= frame_time_nanos) from the queue
     - For each entry, call `entry.callback(frame_time_nanos)` inside try/catch
     - If callback throws, log error and continue to next callback
   - **Traverser**: If `m_traverser_` is set, call `m_traverser_()`
   - **Update state**: `m_last_frame_time_nanos_ = frame_time_nanos`, `m_frame_pending_ = false`, `m_skipped_frames_ = 0`
   - **Schedule next**: Call `schedule_frame_locked()`

9. **`schedule_frame_locked()`**:
   - If `m_frame_pending_`, return
   - `m_frame_scheduled_ = system_time_nanos() + get_frame_interval_nanos()`
   - `m_frame_pending_ = true`
   - Call `m_display_event_receiver_->schedule_vsync()`

10. **`set_traverser(std::function<void()> traverser)`**: Stores `traverser` in `m_traverser_`.

11. **`remove_traverser()`**: Clears `m_traverser_` by assigning `nullptr`.

12. **Query methods**:
    - `get_looper()`: Returns `m_display_event_receiver_->get_looper()`
    - `get_frame_interval_nanos()`: Returns `m_display_event_receiver_->get_frame_interval_nanos()`
    - `get_last_frame_time_nanos()`: Returns `m_last_frame_time_nanos_`

13. **`system_time_nanos()` helper**: Use `std::chrono::steady_clock::now()` converted to nanoseconds. This is a static private helper or a free function in the `.cpp` file.

Pattern to follow: The `do_frame` execution order exactly matches the Java Choreographer's stage order: INPUT -> ANIMATION -> INSETS_ANIMATION -> TRAVERSAL -> COMMIT.

**Acceptance criteria:**
- [x] File exists at `core/cpp/src/android/view/Choreographer.cpp`
- [x] `get_instance()` creates Choreographer on first call, returns same instance on subsequent calls
- [x] `get_instance()` throws `std::runtime_error` when no Looper on thread
- [x] `post_frame_callback()` inserts into TRAVERSAL queue and schedules frame if none pending
- [x] `post_frame_callback_delayed()` uses correct delay conversion (ms * 1000000)
- [x] `remove_frame_callback()` removes from all queues
- [x] `on_vsync()` posts `do_frame` to Looper via `send_message`
- [x] `do_frame()` executes callbacks in correct stage order (INPUT before ANIMATION before TRAVERSAL)
- [x] `do_frame()` jitter resyncs to nearest past VSync when late
- [x] `do_frame()` skips frame when time goes backward
- [x] `do_frame()` catches callback exceptions and continues to next callback
- [x] `do_frame()` calls traverser if set
- [x] `do_frame()` schedules next frame after completing
- [x] `schedule_frame_locked()` is idempotent (returns if already pending)
- [x] `set_traverser()` and `remove_traverser()` work correctly
- [x] Build passes: `cmake --build build`

⚠️ **Pitfall:** In `get_instance()`, the VSync callback lambda MUST be created and passed to the `DisplayEventReceiver` constructor — NOT set afterward via `set_vsync_callback()`. Creating the callback first ensures no window exists where the receiver could fire with a null callback. The `shared_from_this()` inside `do_frame` is safe because `Choreographer` inherits `enable_shared_from_this` and the `shared_ptr` is already stored in `s_thread_instance` before Looper registration.

⚠️ **Pitfall:** The `system_time_nanos()` function must use `std::chrono::steady_clock` (monotonic), NOT `system_clock`. Using wall-clock time will produce incorrect jitter calculations when the system time is adjusted.

---

### T-08 · Create Choreographer tests
**Phase:** 2  
**Depends on:** T-07  
**User story:** All  
**Description:**  
Create `core/cpp/tests/choreographer_test.cpp` with the following test cases:

| Test | Purpose |
|------|---------|
| `GetInstanceCreatesOnFirstCall` | thread_local singleton created on first access |
| `GetInstanceReturnsSameInstance` | Second call returns same shared_ptr |
| `PostFrameCallbackExecutedInOrder` | Callbacks execute in posted order within same frame |
| `PostFrameCallbackDelayedExecutedAtRightTime` | Delayed callback waits for correct frame |
| `RemoveFrameCallbackPreventsExecution` | Removed callback does not fire |
| `DoFrameExecutesStagesInOrder` | INPUT fires before ANIMATION before TRAVERSAL |
| `DoFrameSkippedFrameWarning` | >3 skipped frames triggers warning (verifiable via mock log) |
| `DoFrameBackwardTimeSkipsFrame` | Backward frame time -> no callback execution |
| `SetTraverserCallsPerformTraversals` | Traverser invoked during doFrame |
| `GetFrameIntervalNanos` | Returns correct interval |
| `GetLastFrameTimeNanos` | Returns last frame time after doFrame |
| `JitterResyncToNearestVsync` | Late frame resyncs to nearest past VSync |
| `MultipleCallbacksSameStage` | Multiple callbacks in same stage all execute |
| `CallbackExceptionDoesNotBreakFrameLoop` | Throwing callback -> next callback still runs |

Test implementation details:

- **GetInstanceCreatesOnFirstCall**: Call `Choreographer::get_instance()` and verify it returns a non-null `shared_ptr`.
- **GetInstanceReturnsSameInstance**: Call `get_instance()` twice, verify `ptr1 == ptr2`.
- **PostFrameCallbackExecutedInOrder**: Post two callbacks, trigger `do_frame` directly (bypassing VSync), verify they execute in posted order using a `std::vector<int>` to record execution order.
- **PostFrameCallbackDelayedExecutedAtRightTime**: Post a callback with 500ms delay. Call `do_frame` with a time before the due time -> callback NOT executed. Call `do_frame` with time after due time -> callback executed.
- **RemoveFrameCallbackPreventsExecution**: Post a callback, remove it, trigger `do_frame` -> callback NOT executed.
- **DoFrameExecutesStagesInOrder**: Post callbacks to INPUT, ANIMATION, and TRAVERSAL stages. Trigger `do_frame`. Verify stage execution order by recording stage names in a vector.
- **DoFrameSkippedFrameWarning**: Simulate a large gap between frames (>2 * frame_interval). Verify `m_skipped_frames_` increments. (>3 skipped triggers warning -- verify via log output).
- **DoFrameBackwardTimeSkipsFrame**: Call `do_frame` with a frame_time_nanos that is in the future relative to `system_time_nanos()`. Verify no callbacks executed and next frame scheduled.
- **SetTraverserCallsPerformTraversals**: Call `set_traverser` with a lambda that sets a flag. Call `do_frame`. Verify flag is set.
- **GetFrameIntervalNanos**: Verify returns `16666667` (from DisplayEventReceiver default).
- **GetLastFrameTimeNanos**: After calling `do_frame(1000000000)`, verify `get_last_frame_time_nanos()` returns `1000000000`.
- **JitterResyncToNearestVsync**: Set `m_last_frame_time_nanos_` to a value such that the next frame is 2 frame intervals late. Call `do_frame`. Verify frame_time is resynced to nearest past VSync.
- **MultipleCallbacksSameStage**: Post 3 callbacks to the same stage. Trigger `do_frame`. Verify all 3 execute.
- **CallbackExceptionDoesNotBreakFrameLoop**: Post a callback that throws `std::runtime_error`, then a callback that sets a flag. Trigger `do_frame`. Verify the second callback's flag is set (frame loop continues).

Add to `core/cpp/tests/CMakeLists.txt`:
- `choreographer_test.cpp`
- Link against `android_framework_core`

**Acceptance criteria:**
- [x] File exists at `core/cpp/tests/choreographer_test.cpp`
- [x] All 14 test cases compile and pass
- [x] `DoFrameExecutesStagesInOrder` verifies INPUT < ANIMATION < TRAVERSAL ordering
- [x] `CallbackExceptionDoesNotBreakFrameLoop` verifies frame loop continues after exception
- [x] `JitterResyncToNearestVsync` verifies frame time is resynced correctly
- [x] `DoFrameBackwardTimeSkipsFrame` verifies no callbacks execute on backward time
- [x] Build passes: `cmake --build build && ctest -R choreographer`

---

## ✅ Checkpoint 3: Choreographer Complete

Before proceeding to Phase 3, verify:
- [x] All Choreographer tests pass: `cmake --build build && ctest -R choreographer`
- [x] DisplayEventReceiver tests still pass
- [x] Thread-local singleton pattern works correctly
- [x] Callback queue ordering is correct
- [x] Jitter handling works (resync + backward time skip)
- [x] Exception handling does not break the frame loop
- [x] Code coverage >80% for Choreographer

---

## Phase 3: ViewRootImpl Integration + Build System + Integration Tests

### T-09 · Add enable_shared_from_this to ViewRootImpl
**Phase:** 3  
**Depends on:** T-06  
**User story:** All  
**Description:**  
Modify `core/cpp/include/android/view/ViewRootImpl.h` to inherit from `std::enable_shared_from_this<ViewRootImpl>`. This is required so that the traverser callback can capture a `shared_ptr<ViewRootImpl>` to keep it alive during callback execution.

Changes to `core/cpp/include/android/view/ViewRootImpl.h`:
1. Add `#include <memory>` if not already present (it is).
2. Change class declaration from:
   ```cpp
   class ViewRootImpl {
   ```
   to:
   ```cpp
   class ViewRootImpl : public std::enable_shared_from_this<ViewRootImpl> {
   ```
3. Add new private members:
   ```cpp
   std::weak_ptr<Choreographer> m_choreographer_;
   bool m_choreographer_set_ = false;
   ```
4. Add new public methods (declarations only, implementation in T-10):
   ```cpp
   void set_choreographer(std::weak_ptr<Choreographer> choreographer);
   void remove_choreographer();
   ```

**Acceptance criteria:**
- [x] `ViewRootImpl` inherits `std::enable_shared_from_this<ViewRootImpl>`
- [x] `m_choreographer_` (weak_ptr<Choreographer>) member added
- [x] `m_choreographer_set_` (bool) member added
- [x] `set_choreographer()` and `remove_choreographer()` declared
- [x] Existing `set_view()` and `perform_traversals()` signatures unchanged
- [x] Build passes: `cmake --build build`

⚠️ **Pitfall:** Adding `enable_shared_from_this` changes the class layout. Any code that constructs `ViewRootImpl` on the stack will now have different memory layout. However, the existing codebase only uses `std::make_shared<ViewRootImpl>()`, so this should be safe. Verify by checking all construction sites.

---

### T-10 · Implement ViewRootImpl choreographer integration
**Phase:** 3  
**Depends on:** T-09  
**User story:** All  
**Description:**  
Modify `core/cpp/src/android/view/ViewRootImpl.cpp` to implement choreographer integration.

Changes to `core/cpp/src/android/view/ViewRootImpl.cpp`:

1. Add include: `#include <android/view/Choreographer.h>`

2. Implement `set_choreographer`:
   ```cpp
   void ViewRootImpl::set_choreographer(std::weak_ptr<Choreographer> choreographer) {
       m_choreographer_ = choreographer;
   }
   ```

3. Implement `remove_choreographer`:
   ```cpp
   void ViewRootImpl::remove_choreographer() {
       m_choreographer_.reset();
       m_choreographer_set_ = false;
   }
   ```

4. Modify `set_view` to register the traverser when a view is set and a choreographer is available:
   ```cpp
   void ViewRootImpl::set_view(const std::shared_ptr<View>& view) {
       view_ = view;
       if (view_ && m_choreographer_) {
           auto choreo = m_choreographer_.lock();
           if (choreo) {
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

5. Modify `remove_view` to clean up the choreographer integration:
   ```cpp
   void ViewRootImpl::remove_view() {
       // Clean up choreographer integration before destroying the view
       if (m_choreographer_set_) {
           remove_choreographer();
       }
       view_ = nullptr;
   }
   ```

**Acceptance criteria:**
- [x] `set_choreographer()` stores the weak_ptr
- [x] `remove_choreographer()` resets the weak_ptr and flag
- [x] `set_view()` registers traverser when view and choreographer are both present
- [x] `remove_view()` calls `remove_choreographer()` to clean up stale traverser references
- [x] Traverser callback captures `shared_ptr<ViewRootImpl>` to keep it alive
- [x] Traverser callback checks `strong_self` before calling `perform_traversals()`
- [x] Build passes: `cmake --build build`

---

### T-11 · Update CMakeLists.txt with new source files
**Phase:** 3  
**Depends on:** T-03, T-07  
**User story:** All  
**Description:**  
Update `core/cpp/CMakeLists.txt` to include the new source files in the `android_framework_core` library.

Add to the `CORE_SOURCES` list (in alphabetical order within the `src/android/view/` section):
- `src/android/view/Choreographer.cpp`
- `src/android/view/DisplayEventReceiver.cpp`

The final `CORE_SOURCES` should include these entries near the existing `src/android/view/` entries:
```cmake
    src/android/view/Choreographer.cpp
    src/android/view/DisplayEventReceiver.cpp
    src/android/view/InputChannel.cpp
    ...
```

**Acceptance criteria:**
- [x] `core/cpp/CMakeLists.txt` includes `src/android/view/Choreographer.cpp` in CORE_SOURCES
- [x] `core/cpp/CMakeLists.txt` includes `src/android/view/DisplayEventReceiver.cpp` in CORE_SOURCES
- [x] Full build passes: `cmake -B build -S core/cpp && cmake --build build`

---

### T-12 · Update tests CMakeLists.txt with new test files
**Phase:** 3  
**Depends on:** T-05  
**User story:** All  
**Description:**  
Update `core/cpp/tests/CMakeLists.txt` to include the new test files.

Add to the `framework_tests` executable sources:
- `mock_display_event_receiver.h`
- `display_event_receiver_test.cpp`
- `choreographer_test.cpp`

The entries should be added in a logical position (e.g., after `ViewRootImpl_test.cpp`):
```cmake
    ViewRootImpl_test.cpp
    mock_display_event_receiver.h
    display_event_receiver_test.cpp
    choreographer_test.cpp
    Drawing_test.cpp
    ...
```

**Acceptance criteria:**
- [x] `core/cpp/tests/CMakeLists.txt` includes `mock_display_event_receiver.h`
- [x] `core/cpp/tests/CMakeLists.txt` includes `display_event_receiver_test.cpp`
- [x] `core/cpp/tests/CMakeLists.txt` includes `choreographer_test.cpp`
- [x] Full test build passes: `cmake -B build -S core/cpp && cmake --build build`

---

### T-13 · Create ViewRootImpl + Choreographer integration test
**Phase:** 3  
**Depends on:** T-10  
**User story:** All  
**Description:**  
Create `core/cpp/tests/view_root_impl_choreographer_test.cpp` with integration tests.

| Test | Purpose |
|------|---------|
| `SetChoreographerRegistersTraverser` | `set_choreographer` + `set_view` registers traverser |
| `ChoreographerTraversalTriggersPerformTraversals` | `doFrame` with TRAVERSAL calls ViewRootImpl |
| `RemoveChoreographerRemovesTraverser` | `remove_choreographer` clears the traverser |
| `WeakPtrExpiryDoesNotCrash` | Weak_ptr expires -> traverser is no-op |

Test implementation details:

- **SetChoreographerRegistersTraverser**: Create a `ViewRootImpl`, create a `Choreographer` via `get_instance()` (requires a Looper thread). Call `set_choreographer(weak_ptr)`, then `set_view(mock_view)`. Verify the traverser is registered by checking that `do_frame` would call `perform_traversals()`.

- **ChoreographerTraversalTriggersPerformTraversals**: Create a `ViewRootImpl` with a mock view. Set up choreographer integration. Trigger `do_frame` with a frame time. Verify `perform_traversals()` was called (mock view tracks `on_measure`, `on_layout`, `on_draw` calls).

- **RemoveChoreographerRemovesTraverser**: After setting up choreographer, call `remove_choreographer()`. Trigger `do_frame`. Verify `perform_traversals()` is NOT called.

- **WeakPtrExpiryDoesNotCrash**: Create a `Choreographer` via `get_instance()`. Store it in a local variable. Set choreographer on `ViewRootImpl`. Let the local variable go out of scope (destroying the `shared_ptr`). Call `set_view(mock_view)`. The `weak_ptr::lock()` should return `nullptr`, so no traverser is registered. Verify no crash.

Add to `core/cpp/tests/CMakeLists.txt`:
- `view_root_impl_choreographer_test.cpp`

**Acceptance criteria:**
- [x] File exists at `core/cpp/tests/view_root_impl_choreographer_test.cpp`
- [x] All 4 integration test cases compile and pass
- [x] `ChoreographerTraversalTriggersPerformTraversals` verifies `perform_traversals()` is called
- [x] `RemoveChoreographerRemovesTraverser` verifies `perform_traversals()` is NOT called after removal
- [x] `WeakPtrExpiryDoesNotCrash` verifies no crash when weak_ptr expires
- [x] Build passes: `cmake --build build && ctest -R view_root_impl_choreographer`

---

### T-14 · Run full build and test suite
**Phase:** 3  
**Depends on:** T-11, T-12, T-13  
**User story:** All  
**Description:**  
Run the complete build and test suite to verify no regressions and all new tests pass.

Commands to run:
```bash
# Clean build
rm -rf /home/roto/git/android-platform-frameworks-base/build
cmake -B /home/roto/git/android-platform-frameworks-base/build -S /home/roto/git/android-platform-frameworks-base/core/cpp
cmake --build /home/roto/git/android-platform-frameworks-base/build

# Run all tests
cd /home/roto/git/android-platform-frameworks-base/build && ctest --output-on-failure

# Run only new tests
cd /home/roto/git/android-platform-frameworks-base/build && ctest -R "display_event_receiver|choreographer|view_root_impl_choreographer" --output-on-failure

# Run existing tests to verify no regressions
cd /home/roto/git/android-platform-frameworks-base/build && ctest -R "ViewRootImpl" --output-on-failure
```

**Acceptance criteria:**
- [x] Full build succeeds with zero errors and zero warnings (compiler flags: `-Wall -Wextra -Werror -Wpedantic`)
- [x] All existing tests pass (no regressions)
- [x] All new DisplayEventReceiver tests pass
- [x] All new Choreographer tests pass
- [x] All new integration tests pass
- [x] No new compiler warnings introduced

---

## ✅ Checkpoint 4: Feature Complete

Before marking the feature done, verify every acceptance criterion from the spec:

- [x] **Choreographer spec:** VSync reception via DisplayEventReceiver works
- [x] **Choreographer spec:** Frame callbacks posted and executed in staged order
- [x] **Choreographer spec:** Thread-local singleton pattern works
- [x] **DisplayEventReceiver spec:** VSync event delivery via Looper FD registration works
- [x] **ViewRootImpl integration:** `set_choreographer()` + `set_view()` registers traverser
- [x] **ViewRootImpl integration:** `remove_choreographer()` clears traverser
- [x] All tests pass: `ctest --output-on-failure`
- [x] No new linting errors (compiler is strict: `-Wall -Wextra -Werror -Wpedantic`)
- [x] Code coverage >80% for DisplayEventReceiver and Choreographer

---

## Coverage Report

### Spec Coverage

| Spec Section | Acceptance Criterion | Covered By |
|---|---|---|
| Choreographer.md - VSync reception | Receives VSync from DisplayEventReceiver | T-05, T-07, T-08 |
| Choreographer.md - Frame callbacks | postFrameCallback() schedules work | T-07, T-08 |
| Choreographer.md - Frame loop (staged execution) | Input, Animation, Traversal stages execute in order | T-07, T-08 |
| Choreographer.md - Thread-local singleton | Per-thread instance via get_instance() | T-07, T-08 |
| Choreographer.md - Traversal trigger | Traversal stage calls ViewRootImpl | T-08, T-13 |
| DisplayEventReceiver.md - VSync callback | onVsync() delivers timestamp, count, vsync_id | T-05 |
| DisplayEventReceiver.md - scheduleVsync() | Requests VSync pulse | T-05 |
| DisplayEventReceiver.md - Looper integration | FD registered on Looper thread | T-04, T-05 |
| DisplayEventReceiver.md - dispose() | FD closed, resources released | T-05 |
| ViewRootImpl integration | set_choreographer + set_view registers traverser | T-10, T-13 |
| ViewRootImpl integration | remove_choreographer clears traverser | T-10, T-13 |
| ViewRootImpl integration | Weak_ptr expiry does not crash | T-13 |

### Plan Coverage

| Plan Section | Covered By |
|---|---|
| Phase 0: Research (libui, Looper pattern, thread-local, frame timing) | T-01 |
| Phase 1: DisplayEventReceiver header | T-02 |
| Phase 1: DisplayEventReceiver implementation | T-03 |
| Phase 1: Mock for host builds | T-04, T-05 |
| Phase 1: DisplayEventReceiver tests | T-05 |
| Phase 2: Choreographer header | T-06 |
| Phase 2: Choreographer implementation | T-07 |
| Phase 2: Choreographer tests | T-08 |
| Phase 3: ViewRootImpl enable_shared_from_this | T-09 |
| Phase 3: ViewRootImpl choreographer integration | T-10 |
| Phase 3: CMakeLists.txt updates | T-11, T-12 |
| Phase 3: Integration tests | T-13 |
| Phase 3: Full build + regression test | T-14 |

### Gaps

None identified. All spec criteria and plan sections have corresponding tasks.

