# Data Model: Input System Integration

## Entities

### InputEventWrapper

Type-safe container for any input event type. Wraps `std::variant<MotionEvent, KeyEvent>`.

**Fields**:
- `event`: `std::variant<MotionEvent, KeyEvent>` — the typed event payload
- `sequence_number`: `uint32_t` — monotonic sequence number for event tracking (used by `finishInputEvent` to match events)

**Validation**:
- `sequence_number` is assigned monotonically by `InputEventReceiver` on event reception
- `std::variant` is always in the "value" state (never "empty") after construction by `consumeEvents()`

**State transitions**:
- Created (unconsumed) → Dispatched (after `onInputEvent` callback) → Finished (after `finishInputEvent`)

---

### InputEventReceiver

Core receiver managing the input channel, looper, and event lifecycle.

**Fields**:
- `mChannel`: `std::shared_ptr<InputChannel>` — the input channel (socket pair) for event reception
- `mLooper`: `std::shared_ptr<os::Looper>` — the Looper thread for callback delivery
- `mCurrentEvent`: `std::optional<InputEventWrapper>` — the currently in-progress event (guarded by sequential processing invariant)
- `mSequenceCounter`: `uint32_t` — monotonic counter for assigning sequence numbers
- `mDisposed`: `bool` — disposal state (once true, no further operations allowed)
- `mFdWatcherRegistered`: `bool` — whether the FD watcher is registered with the Looper

**Validation**:
- `mChannel` must be valid (`is_valid() == true`) at construction
- `mLooper` must be non-null at construction
- `mCurrentEvent.has_value()` must be `false` before processing a new event (sequential invariant)
- `mDisposed` must be `false` for all public methods except `dispose()`

**State transitions**:
- Constructed → Active (after Looper registration) → Disposed (after `dispose()`)
- Active: `mCurrentEvent` alternates between empty (waiting for event) and occupied (event in progress)

**Relationships**:
- Owns `InputChannel` (shared ownership)
- References `Looper` (shared ownership)
- Produces `InputEventWrapper` instances (owned by caller via callback)

---

### MotionEvent

Represents a touch/motion event. Extends the existing minimal implementation.

**Fields**:
- `action`: `MotionEvent::Action` (enum class) — event action type
- `x`: `float` — primary X coordinate
- `y`: `float` — primary Y coordinate
- `device_id`: `int32_t` — source device identifier
- `source`: `uint32_t` — event source flags (e.g., `SOURCE_TOUCHSCREEN`)
- `history_size`: `uint32_t` — number of history items in the batch
- `history`: `std::vector<MotionEvent>` — prior motion samples in a batch
- `event_time`: `int64_t` — event timestamp (nanoseconds)
- `pointer_count`: `int32_t` — number of pointers (for multi-touch)
- `pointer_ids`: `std::vector<int32_t>` — pointer identifiers
- `pointer_coords`: `std::vector<std::pair<float, float>>` — per-pointer coordinates

**Validation**:
- `action` must be one of: `ACTION_DOWN`, `ACTION_UP`, `ACTION_MOVE`, `ACTION_CANCEL`, `ACTION_HOVER_MOVE`, `ACTION_HOVER_ENTER`, `ACTION_HOVER_EXIT`
- `x`, `y` are valid within the view bounds (validation happens at dispatch time, not construction)
- `history` size must match `history_size`

**State transitions**:
- Created (from wire parsing) → Dispatched (after `dispatchTouchEvent`) → Recycled (after `finishInputEvent`)

**Relationships**:
- Held by `InputEventWrapper` (as `std::variant` alternative 1)
- Dispatched to `View` via `dispatch_touch_event(const MotionEvent&)`

---

### KeyEvent

Represents a keyboard event. Extends the existing minimal implementation.

**Fields**:
- `action`: `KeyEvent::Action` (enum class) — `ACTION_DOWN` or `ACTION_UP`
- `key_code`: `int32_t` — Android key code (e.g., `KEYCODE_BACK`)
- `device_id`: `int32_t` — source device identifier
- `source`: `uint32_t` — event source flags
- `event_time`: `int64_t` — event timestamp (nanoseconds)
- `repeat_count`: `int32_t` — repeat count for held keys
- `meta_state`: `uint32_t` — meta key state (shift, ctrl, alt, etc.)

**Validation**:
- `action` must be `ACTION_DOWN` or `ACTION_UP`
- `key_code` must be a valid Android key code (>= 0)

**State transitions**:
- Created (from wire parsing) → Dispatched → Recycled

**Relationships**:
- Held by `InputEventWrapper` (as `std::variant` alternative 2)

---

### ViewGroupDispatchState

Internal state for an in-progress touch dispatch sequence (not a persistent entity).

**Fields**:
- `target`: `std::shared_ptr<View>` — the view currently receiving the event
- `intercepted`: `bool` — whether a parent `ViewGroup` intercepted the event
- `local_coords`: `std::pair<float, float>` — event coordinates in target's local space

**Validation**:
- `target` is valid (non-null) when `intercepted` is `false`
- `local_coords` is computed from global coordinates minus target's top-left offset

**State transitions**:
- Init → HitTest → (Recursion) → Dispatched → Finished
