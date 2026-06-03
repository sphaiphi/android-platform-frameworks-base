# Choreographer Clarifications

## Summary

The Choreographer spec is a high-level overview (~40 lines) that describes the role and architecture but lacks implementation-level detail. The Java reference is 1654 lines with extensive edge-case handling. The C++ MVP must capture the core frame loop (VSync reception, callback queue, staged execution, traversal trigger) while deferring advanced features. DisplayEventReceiver does not exist in C++ yet and is a hard dependency. The existing C++ Looper/Message infrastructure is sufficient to replace Java's Handler pattern.

Blocking questions: 3
Important questions: 4
Nice-to-know questions: 3

---

## Blocking

### Q1: DisplayEventReceiver is not yet implemented in C++. Should it be a prerequisite feature?

**Context:** Choreographer.md states "Use `android::DisplayEventReceiver` to receive native VSync signals." DisplayEventReceiver.md describes its role, but no C++ source files exist for it. The Java Choreographer creates `FrameDisplayEventReceiver` in its constructor and calls `scheduleVsync()` during `doFrame`.

**Answer:** Yes. DisplayEventReceiver MUST be implemented before Choreographer. It is the sole source of VSync timing data. Choreographer's constructor takes a `DisplayEventReceiver` (or creates one internally).

**Why it blocks:** Without DisplayEventReceiver, Choreographer has no VSync input. The entire frame loop is driven by VSync pulses. A planner cannot architect Choreographer without knowing how VSync data arrives.

**Decision:** Implement DisplayEventReceiver as a separate feature in `core/cpp/specs/android/view/DisplayEventReceiver.md` with its own plan. Choreographer plan must list it as a prerequisite. The C++ DisplayEventReceiver wraps the native `android::DisplayEventReceiver` (from libui), registers its pipe FD on the Looper via `add_fd()`, and delivers `onVsync()` callbacks when the FD is ready.

---

### Q2: How should the C++ Choreographer integrate with ViewRootImpl's traversal?

**Context:** ViewRootImpl.h already exists with `perform_traversals()`. The Java Choreographer's CALLBACK_TRAVERSAL stage calls `ViewRootImpl.invalidate()` which triggers `performTraversals()`. The C++ ViewRootImpl has no `Choreographer` member and no `invalidate()` method.

**Answer:** ViewRootImpl shall hold a `weak_ptr<Choreographer>` and register a CALLBACK_TRAVERSAL callback during `set_view()`. The callback invokes `perform_traversals()`. On `removeView()`, the callback is removed. This avoids a hard circular dependency.

**Why it blocks:** Without this integration, Choreographer is just a timer with no output. The entire purpose of Choreographer is to drive the frame loop, and the frame loop's final stage is traversal (measure/layout/draw).

**Decision:** Add `set_choreographer(weak_ptr<Choreographer>)` and `remove_choreographer()` to ViewRootImpl. The traversal callback is a `std::function<void(int64_t)>` that captures the ViewRootImpl shared_ptr to keep it alive during the callback.

---

### Q3: What is the exact public API surface for the MVP?

**Context:** The Java class has 30+ public/protected methods. The spec mentions only `postFrameCallback()` and `postVsyncCallback()`. Many methods are `@hide` or `@UnsupportedAppUsage`.

**Answer:** The MVP public API is:

```cpp
class Choreographer : public std::enable_shared_from_this<Choreographer> {
public:
    // Factory
    static auto get_instance() -> std::shared_ptr<Choreographer>;

    // Callback posting
    void post_frame_callback(FrameCallback cb);
    void post_frame_callback_delayed(FrameCallback cb, int64_t delay_ms);
    void remove_frame_callback(FrameCallback cb);

    // Frame callback type
    using FrameCallback = std::function<void(int64_t frameTimeNanos)>;

    // Query
    auto get_looper() const -> std::shared_ptr<Looper>;
    auto get_frame_interval_nanos() const -> int64_t;
    auto get_last_frame_time_nanos() const -> int64_t;

    // Internal (for ViewRootImpl integration)
    void set_traverser(std::function<void()> traverser);

private:
    explicit Choreographer(std::shared_ptr<Looper> looper);
    ~Choreographer();
    // ... internal methods
};
```

No `postCallback(int, Runnable, Object)` overloads. No `setFPSDivisor()`. No `getVsyncId()`. No `getFrameDeadline()`. No `getExpectedPresentationTimeNanos()`. No `releaseInstance()` (RAII destruction suffices).

**Why it blocks:** A planner needs to know exactly which methods to implement. Spec-only coverage of `postFrameCallback` leaves too many decisions open (e.g., should `removeFrameCallback` exist? Should `getFrameIntervalNanos` be public?).

---

## Important

### Q4: CallbackQueue implementation -- sorted vector with no object pooling

**Context:** Java uses `CallbackRecord` linked-list nodes with a `mCallbackPool` for reuse. C++ has `std::function` which is already heap-allocated when capturing lambdas. Object pooling `CallbackRecord` structs adds complexity with minimal benefit.

**Answer:** Use a sorted `std::vector<CallbackEntry>` per callback type, where `CallbackEntry` holds `{ int64_t dueTime, FrameCallback cb }`. Insertion is O(n) binary search + insert. Extraction scans from the beginning and moves executed entries to a temporary list. On callback completion, the temporary list is cleared (no pooling needed).

For zero-cost: the sorted vector is cache-friendly compared to a linked list. The freelist pattern from Java exists because Java objects are expensive to allocate. `std::function` allocation happens once at capture time, so per-frame allocation is unnecessary.

**Default assumption if unanswered:** Use `std::vector` with sorted insertion. If performance profiling shows this is a bottleneck, switch to a free-list linked list.

---

### Q5: Callback type selection -- use all 5 types, but INSETS_ANIMATION callbacks are optional

**Context:** Java defines CALLBACK_INPUT=0 through CALLBACK_COMMIT=4. The spec mentions all 5 stages. INSETS_ANIMATION (2) exists for window inset animation controllers which are not in scope for MVP.

**Answer:** Implement all 5 callback type constants. INPUT, ANIMATION, TRAVERSAL, and COMMIT are required for MVP. INSETS_ANIMATION queue exists but will have no registered callbacks initially. This maintains API compatibility with the Java API surface (same integer values) while allowing INSETS_ANIMATION functionality to be added later without breaking changes.

**Default assumption if unanswered:** All 5 types defined as `enum class CallbackType : int { INPUT=0, ANIMATION=1, INSETS_ANIMATION=2, TRAVERSAL=3, COMMIT=4 }`. The queue array is always allocated with size 5.

---

### Q6: VSYNC-only mode. No non-VSYNC fallback.

**Context:** Java has `USE_VSYNC = SystemProperties.getBoolean("debug.choreographer.vsync", true)` and a parallel non-VSync code path that uses `DEFAULT_FRAME_DELAY = 10ms` polling.

**Answer:** The C++ MVP always uses VSYNC. The non-VSync path is a debugging/compatibility fallback that is not needed in the native implementation. If DisplayEventReceiver cannot be created (e.g., no display), Choreographer construction fails with an error rather than falling back to timer-based scheduling.

**Why it matters:** This halves the code complexity. The non-VSync path has its own `MSG_DO_FRAME` handling, frame delay calculations, and scheduling logic.

**Default assumption if unanswered:** VSYNC only. If a no-VSync path is later required, it can be added as a separate feature.

---

### Q7: Jitter calculation -- simplified version only

**Context:** Java's `doFrame()` jitter math (lines 1018-1079) handles: missed vsync detection, skipped frame counting, frame time resync, backward frame time detection, and FPSDivisor gating. This is ~60 lines of complex integer arithmetic.

**Answer:** Implement the core jitter handling:
- If `startNanos - frameTimeNanos >= frameIntervalNanos`, set `frameTimeNanos = startNanos - (jitterNanos % frameIntervalNanos)` (resync to nearest past vsync).
- Log a warning if more than 2 frames are skipped (matching Java's `SKIPPED_FRAME_WARNING_LIMIT = 30` but with a lower threshold for C++ MVP).
- If frame time goes backward, skip the frame and request next VSync (same as Java).

Do NOT implement: FPSDivisor gating, the commit-phase frame time adjustment (lines 1151-1168), or the complex resync trace infrastructure.

**Default assumption if unanswered:** Simplified jitter with frame resync + skip logging. The commit-phase adjustment is a corner-case fix for heavy layouts that can be added later.

---

## Nice-to-Know

### Q8: Thread-local storage implementation detail

**Context:** Java uses `ThreadLocal<Choreographer>` with `initialValue()` override. C++ Looper uses `thread_local static std::shared_ptr<Looper>`.

**Answer:** Use `inline thread_local std::shared_ptr<Choreographer> s_thread_instance` with a `get_instance()` factory that creates the Choreographer on first access. The main thread instance is additionally stored in a static `s_main_instance` variable, accessible via `get_main_instance()`. This mirrors the Java pattern exactly and is the standard C++ idiom for thread-local singletons.

**Note:** Do NOT use `std::call_once` for thread-local initialization -- `thread_local` with inline variable (C++17+) is already thread-safe for initialization.

---

### Q9: FrameData / FrameTimeline -- omitted from MVP

**Context:** Java's `FrameData` holds `mFrameTimeNanos`, `mFrameTimelines[]`, and `mPreferredFrameTimelineIndex`. `FrameTimeline` holds `mVsyncId`, `mExpectedPresentationTimeNanos`, `mDeadlineNanos`. These are populated from `DisplayEventReceiver.VsyncEventData`.

**Answer:** Omit FrameData and FrameTimeline from MVP. `getFrameTimeNanos()` returns `mLastFrameTimeNanos` directly. `getVsyncId()`, `getFrameDeadline()`, and `getExpectedPresentationTimeNanos()` are not implemented. These can be added once DisplayEventReceiver's `VsyncEventData` structure is finalized.

---

### Q10: Buffer stuffing recovery and animation clock -- omitted from MVP

**Context:** Java's `BufferStuffingState` is a 35-line struct with `RecoveryAction` enum, `isStuffed`, `isRecovering`, `numberWaitsForNextVsync`. The `updateBufferStuffingState()` method is 50 lines. `AnimationUtils.lockAnimationClock()` / `unlockAnimationClock()` is a global synchronization primitive.

**Answer:** Both are omitted from MVP. Buffer stuffing is a SurfaceFlinger-side optimization that is not relevant to the native framework's MVP. The animation clock is a Java-level synchronization mechanism for `ValueAnimator` timing and is not needed in the C++ MVP.

---

### Q11: Token-based callback identity -- omit tokens for MVP

**Context:** Java's `CallbackRecord` has `action` (Runnable/FrameCallback) and `token` (Object). `removeCallbacks(action, token)` uses both for identity. `FRAME_CALLBACK_TOKEN` and `VSYNC_CALLBACK_TOKEN` are sentinel objects.

**Answer:** For MVP, `remove_frame_callback(FrameCallback)` takes only the callback function. Callback identity is determined by `std::function` equality (which compares the underlying callable). If the underlying callable does not support equality comparison (e.g., stateful lambdas), use a `std::shared_ptr` wrapper with pointer comparison.

Tokens are omitted. `postCallback(int, Runnable, Object)` is not in the MVP API.

