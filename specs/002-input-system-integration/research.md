# Research: Input System Integration

## Wire Protocol Parsing

**Decision**: Parse Android `InputEvent` wire format directly in `InputEventReceiver::consumeEvents()` using a standalone parser function.

**Rationale**: The Java `InputEventReceiver.nativeConsumeBatchedInputEvents()` reads raw bytes from the socket and unflattens `InputEvent` objects directly. A separate parser class would add indirection and virtual calls, violating the zero-cost abstraction principle. The wire format is a fixed binary layout defined by the platform: 8-byte event header (sequence number, event type, action, device ID, source, history size) followed by a type-specific payload.

**Alternatives considered**:
- Separate `InputEventParser` utility class — rejected: adds indirection, virtual dispatch overhead
- AIDL-generated deserialization — rejected: AIDL bindings are for IPC across processes, not in-process socket reads
- `std::variant` with manual `std::visit` — chosen: zero-cost, compile-time dispatch

## Looper FD Registration Pattern

**Decision**: Use `ALooper_registerFd()` style registration via a wrapper around the platform's `Looper` class. The `InputEventReceiver` registers its `InputChannel` read FD with the `Looper` using a callback-based poll mechanism.

**Rationale**: The existing project `Looper` class uses `std::shared_ptr<Looper>` with thread-local storage. The `InputChannel` provides the native FD. Registration must be thread-safe (FD registration from constructor, callback on Looper thread). Since the design is lock-free single-threaded, registration happens once during construction on the calling thread, and the callback executes on the Looper thread.

**Alternatives considered**:
- `epoll`-based custom loop — rejected: duplicates Looper functionality
- `poll()`-based — rejected: less efficient than epoll, no integration with existing Looper

## std::variant vs Virtual Dispatch for InputEvent

**Decision**: `std::variant<MotionEvent, KeyEvent>` with `std::visit` for dispatch.

**Rationale**: The clarification session selected this option. `std::variant` provides compile-time type safety with zero runtime overhead (no vtable lookup). `std::visit` is inline-friendly and the compiler can optimize the two-type case to a simple type tag comparison. This matches the constitution's zero-cost abstraction principle (Principle II) and the project's preference for static polymorphism over virtual functions.

**Alternatives considered**:
- Virtual base class `InputEvent` with derived `MotionEvent`/`KeyEvent` — rejected: vtable lookup overhead, heap allocation per event
- Tagged union with manual type checking — rejected: error-prone, `std::variant` provides the same with compile-time safety

## Event Bounding Strategy

**Decision**: `consumeEvents()` reads all available data from the socket in one call and dispatches events sequentially until the buffer is empty. No artificial per-frame event cap.

**Rationale**: The Android input system batches motion samples for performance. Artificial caps would drop valid events and break smooth gesture recognition. The socket buffer (typically 64KB on Android) provides a natural upper bound. The Looper thread processes events sequentially, so a burst of 100 motion samples will block the thread for the duration of their dispatch — but this is the expected behavior (the app is responsible for fast event processing).

**Alternatives considered**:
- Hard cap of 32 events per call — rejected: would silently drop valid motion samples
- One event per call — rejected: defeats the purpose of batching, increases dispatch overhead

## Scope Boundary: InputStage vs ViewDispatch

**Decision**: `InputEventReceiver` and `ViewGroup`/`View` dispatch are in scope. `InputStage` pipeline and `ViewRootImpl` are out of scope — provided as a minimal stub that forwards events to `ViewGroup.dispatchPointerEvent()`.

**Rationale**: `ViewRootImpl` in the Java framework is a 3000+ line class with 20+ inner classes. The `InputStage` chain (async, post-IME, pre-focus, view, final) adds significant complexity. The core input path (receiver -> socket -> callback -> ViewGroup dispatch -> View) is independently valuable and testable. The `ViewRootImpl` stub provides a forwarding path for integration testing without the full complexity.

**Alternatives considered**:
- Full InputStage implementation — rejected: scope creep, 3000+ lines of Java to reverse-engineer
- Receiver-only (no dispatch) — rejected: incomplete input path, User Story 3 would be unimplementable

## FD Lifetime Management

**Decision**: `InputChannel` owns the FD via RAII. `InputEventReceiver` holds a `std::shared_ptr<InputChannel>` (or the existing `InputChannel` by value with a native handle). FD registration happens in the constructor; unregistration happens in `dispose()`.

**Rationale**: The existing `InputChannel` class stores a `void* native_handle_`. For FD management, this should be replaced with a typed handle or `std::unique_ptr`-style RAII wrapper. Since the existing header uses `void*`, the C++ implementation will cast it to an `int` FD for `read()`/`poll()` operations. The `dispose()` method must unregister from the Looper before closing the channel.

**Alternatives considered**:
- `std::unique_ptr<int>` for FD — rejected: existing `InputChannel` uses `void*`, would require header change
- Raw FD int — accepted: pragmatic, matches existing `InputChannel` design, RAII managed at the `InputEventReceiver` level via `dispose()`
