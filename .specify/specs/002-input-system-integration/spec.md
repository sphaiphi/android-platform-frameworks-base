# Feature Specification: Input System Integration (InputEventReceiver)

**Feature Branch**: `002-input-system-integration`
**Created**: 2026-05-23
**Status**: Draft
**Input**: User description: "Input System Integration (InputEventReceiver)"

## Clarifications

### Session 2026-05-23

- Q: Should InputEventReceiver parse raw binary wire format directly or delegate to a parser utility? → A: Parse raw binary wire format directly in consumeEvents()
- FR-002 updated: `consumeEvents()` parses the Android `InputEvent` wire protocol binary layout (event header + typed payload) directly.
- FR-015 added: Lock-free, single-threaded design — all calls on Looper thread only, no internal synchronization.
- FR-016 added: consumeEvents() reads all available socket data per call, no artificial per-frame event cap.
- FR-017 added: InputStage/ViewRootImpl out of scope; minimal stub interface forwards to ViewGroup.dispatchPointerEvent().
- InputEvent changed from polymorphic hierarchy to `std::variant<MotionEvent, KeyEvent>` (zero-cost, no virtual dispatch).

## User Scenarios & Testing

### User Story 1 - Receive and Dispatch Touch Events (Priority: P1)

A native application (via NDK or framework component) needs to receive raw touch/motion events from the Android input system and dispatch them through the view hierarchy. Events arrive via a socket pair (`InputChannel`) watched by a `Looper`. The `InputEventReceiver` reads events from the socket, triggers a callback (`onInputEvent`), and after the application processes the event, signals completion via `finishInputEvent`.

**Why this priority**: This is the core input path. Without it, no touch, key, or motion input can reach the view system. Everything else depends on this foundation.

**Independent Test**: Can be fully tested by creating an `InputEventReceiver` bound to a mock `InputChannel`, injecting a synthetic event through the socket, and verifying that `onInputEvent` is called with the correct event data, then `finishInputEvent` is called with the handled flag.

**Acceptance Scenarios**:

1. **Given** an `InputEventReceiver` is constructed with a valid `InputChannel` and `Looper`, **When** a `MotionEvent` arrives on the input channel socket, **Then** the `onInputEvent()` callback is invoked on the Looper thread with a properly constructed `MotionEvent`
2. **Given** an `onInputEvent()` callback has received an event, **When** `finishInputEvent(event, true)` is called, **Then** the handled status is sent back through the `InputChannel` to the system InputDispatcher
3. **Given** an `onInputEvent()` callback has received an event, **When** `finishInputEvent(event, false)` is called, **Then** the unhandled status is sent back, allowing the system to determine if other windows should receive the event
4. **Given** `onInputEvent()` is invoked, **When** the application does NOT call `finishInputEvent()`, **Then** the input pipeline for the window is blocked (ANR condition)

---

### User Story 2 - Event Reception via Looper Polling (Priority: P1)

The `InputEventReceiver` must integrate with the Android `Looper` message loop to efficiently wait for input events. It registers a file descriptor watcher on the `InputChannel`'s socket. When data arrives (VSync-aligned), the Looper wakes the receiver, which then consumes events from the socket buffer.

**Why this priority**: Without Looper integration, the receiver cannot asynchronously receive events. This is the mechanism that makes the input system responsive without busy-waiting.

**Independent Test**: Can be tested by creating a receiver, registering it with a Looper, writing data to the write-end of the `InputChannel` socket pair from another thread, and verifying the Looper callback fires.

**Acceptance Scenarios**:

1. **Given** an `InputEventReceiver` is registered with a `Looper`, **When** no data is available on the input channel, **Then** the Looper blocks efficiently (polls the socket FD)
2. **Given** data arrives on the input channel socket from another thread, **When** the Looper polls, **Then** the `InputEventReceiver` callback is triggered
3. **Given** multiple events are batched in the socket buffer, **When** `consumeEvents()` is called, **Then** all available events are read and dispatched sequentially
4. **Given** the receiver is disposed, **When** the Looper polls, **Then** the file descriptor watcher is removed and no further callbacks occur

---

### User Story 3 - Event Dispatch Through View Hierarchy (Priority: P2)

After `onInputEvent()` is called in `ViewRootImpl`, events flow through the `InputStage` pipeline and into the view hierarchy. The root `DecorView` (a `ViewGroup`) dispatches events through hit-testing: checking intercept, iterating children in Z-order, transforming coordinates, and recursing down to the target view.

**Why this priority**: This completes the end-to-end input path from system to leaf view. Without it, events arrive at ViewRootImpl but never reach the actual UI components.

**Independent Test**: Can be tested by constructing a `View`/`ViewGroup` hierarchy, feeding a `MotionEvent` through `ViewRootImpl`'s dispatch path, and verifying the correct view receives the event with transformed coordinates.

**Acceptance Scenarios**:

1. **Given** a `ViewGroup` with multiple children, **When** a touch event arrives within a child's bounds, **Then** the event is dispatched to that child with coordinates transformed to its local space
2. **Given** a `ViewGroup` that intercepts a touch event via `onInterceptTouchEvent()`, **When** a `MotionEvent.ACTION_DOWN` arrives, **Then** the event is consumed by the group and not forwarded to children
3. **Given** a nested `ViewGroup` hierarchy, **When** a touch event arrives, **Then** coordinate transformation is applied at each level (recursive `offset_location`)
4. **Given** a leaf `View` handles an event (returns `true` from `dispatchTouchEvent`), **When** the event bubbles up, **Then** `finishInputEvent` is called with `handled=true`

---

### User Story 4 - Special Event Handling (Focus, Touch Mode, Pointer Capture) (Priority: P3)

The `InputEventReceiver` must support non-motion events: focus changes, touch mode transitions, pointer capture events, and drag events. These are delivered through dedicated callback methods.

**Why this priority**: These are important for completeness but are not on the critical path for basic touch input. They can be implemented after the core input path.

**Independent Test**: Can be tested by invoking each callback method directly and verifying the correct internal state is updated.

**Acceptance Scenarios**:

1. **Given** a window gains focus, **When** `onFocusEvent(true)` is called, **Then** the focus state is propagated to the associated view
2. **Given** a display enters touch mode, **When** `onTouchModeChanged(true)` is called, **Then** touch mode state is updated
3. **Given** pointer capture is requested, **When** `onPointerCaptureEvent(true)` is called, **Then** pointer capture state is set

---

## Edge Cases

- **Double `finishInputEvent`**: What happens when `finishInputEvent` is called twice for the same event? The Java implementation logs a warning and skips the second call (sequence number not in map).
- **`finishInputEvent` after dispose**: What happens when `finishInputEvent` is called after the receiver is disposed? The Java implementation logs a warning and no-ops.
- **Null event to `finishInputEvent`**: The Java implementation throws `IllegalArgumentException`.
- **Event not finished (ANR)**: If `onInputEvent` returns without calling `finishInputEvent`, the input dispatcher blocks, leading to an ANR timeout.
- **Concurrent event consumption**: Events arrive sequentially (one at a time). The receiver must not process a new event before the previous one is finished.
- **Socket closed unexpectedly**: If the input channel socket is closed by the system (e.g., window destroyed), the receiver must handle the read error gracefully.
- **Batched events**: Some input events may be batched for performance (e.g., motion samples). The receiver must support `consumeBatchedInputEvents`.

## Requirements

### Functional Requirements

- **FR-001**: System MUST provide an `InputEventReceiver` class that wraps an `InputChannel` socket pair and delivers events via a `Looper`-thread callback
- **FR-002**: System MUST read raw `MotionEvent`/`KeyEvent` data from the input channel socket using `consumeEvents()`
- **FR-003**: System MUST invoke `onInputEvent(std::variant<MotionEvent, KeyEvent>)` callback on the Looper thread for each received event (no virtual dispatch)
- **FR-004**: System MUST support `finishInputEvent(event, handled)` to send completion status back through the `InputChannel` to the InputDispatcher
- **FR-005**: System MUST support `dispatchInputEvent()` to construct typed events (MotionEvent/KeyEvent) from raw socket data and trigger the callback
- **FR-006**: System MUST support `onFocusEvent(bool)`, `onTouchModeChanged(bool)`, and `onPointerCaptureEvent(bool)` callbacks
- **FR-007**: System MUST provide `dispose()` / `nativeDispose()` to clean up the receiver and close the input channel
- **FR-008**: System MUST prevent processing a new event before the previous one is finished (sequential event processing)
- **FR-015**: System MUST be lock-free and single-threaded — all public methods MUST be called exclusively from the Looper thread; no internal mutexes or synchronization primitives
- **FR-009**: System MUST support `consumeBatchedInputEvents(long frameTimeNanos)` for batched motion event delivery
- **FR-016**: `consumeEvents()` reads all available data from the socket in a single call and dispatches events sequentially; batching is bounded purely by socket buffer availability with no artificial per-frame event cap
- **FR-010**: System MUST support `probablyHasInput()` to check event availability (may return false negatives)
- **FR-011**: System MUST support `reportTimeline()` for input latency reporting
- **FR-012**: System MUST support `onInterceptTouchEvent()` in `ViewGroup` for event interception in the dispatch chain
- **FR-017**: `InputStage` pipeline and `ViewRootImpl` are out of scope for this feature; a minimal stub interface forwards events from `ViewRootImpl` to `ViewGroup.dispatchPointerEvent()`
- **FR-013**: System MUST transform event coordinates via `offset_location()` when dispatching to child views
- **FR-014**: System MUST iterate children in reverse Z-order during hit-testing in `ViewGroup`

### Key Entities

- **InputEventReceiver**: Core receiver class that bridges the input channel socket to application callbacks. Owns the channel, looper, and current event state.
- **InputChannel**: Socket pair handle providing the IPC endpoint for input events. Contains a native file descriptor.
- **InputEvent**: Type-safe union (`std::variant<MotionEvent, KeyEvent>`) — no virtual dispatch; sequence numbers tracked in the variant-holding wrapper
- **MotionEvent**: Represents a touch/motion event with action type, coordinates, device ID, source flags, and history buffer.
- **KeyEvent**: Represents a keyboard event with action type (down/up) and key code.
- **ViewGroup**: Container view that performs hit-testing, event interception, and coordinate transformation during dispatch.
- **View**: Leaf UI component that receives dispatched touch events via `dispatchTouchEvent()`.

## Success Criteria

### Measurable Outcomes

- **SC-001**: An `InputEventReceiver` can receive and dispatch a `MotionEvent` from socket write to `onInputEvent` callback in under 1ms on a typical device
- **SC-002**: All public methods of `InputEventReceiver`, `InputChannel`, `MotionEvent`, `KeyEvent`, and `ViewGroup` dispatch are covered by unit tests (>80% coverage)
- **SC-003**: The complete input dispatch path (receiver -> InputStage -> ViewGroup -> View) works end-to-end in a host-built test
- **SC-004**: Failing to call `finishInputEvent` within the ANR timeout (5 seconds) is detectable via test assertion

## Assumptions

- The `InputChannel` socket pair is already established by the window manager (out of scope for this feature)
- The `Looper` and `MessageQueue` infrastructure is available (already implemented)
- Raw event binary format on the socket matches the Android `InputEvent` wire protocol; `consumeEvents()` parses the binary layout (event header + typed payload) directly
- `MotionEvent` and `KeyEvent` basic types are available (partially implemented)
- The `View` and `ViewGroup` base classes exist or are being developed in parallel (see track 001: Window Manager)
- Host build uses mock binder headers; on-device build uses real AIDL bindings
- C++23 standard with `std::expected` for error handling, smart pointers for lifetime safety
