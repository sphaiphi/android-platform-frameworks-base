# API Contract: InputEventReceiver

## Interface: `android::view::InputEventReceiver`

### Constructor

```cpp
InputEventReceiver(std::shared_ptr<InputChannel> channel, std::shared_ptr<os::Looper> looper);
```

**Preconditions**:
- `channel->is_valid() == true`
- `looper != nullptr`

**Postconditions**:
- Receiver is constructed but not yet registered with the Looper
- `mCurrentEvent` is empty, `mDisposed` is false

**Throws**: `std::invalid_argument` if preconditions violated

---

### `onInputEvent` (Pure Virtual Callback)

```cpp
virtual void onInputEvent(std::variant<MotionEvent, KeyEvent> event) = 0;
```

**Preconditions**:
- Called exclusively on the Looper thread
- `mCurrentEvent.has_value() == false` (no in-progress event)
- `!mDisposed`

**Postconditions**:
- Implementation MUST call `finishInputEvent()` before returning
- `mCurrentEvent` is set to the dispatched event during callback execution

**Called by**: `InputEventReceiver` internal dispatch logic, on the Looper thread

---

### `finishInputEvent`

```cpp
void finishInputEvent(std::variant<MotionEvent, KeyEvent> event, bool handled);
```

**Preconditions**:
- Called exclusively on the Looper thread
- `mCurrentEvent.has_value() == true` (event in progress)
- `!mDisposed`
- `event` matches the type held in `mCurrentEvent`

**Postconditions**:
- `handled` status is written to the `InputChannel` socket
- `mCurrentEvent.reset()` — event is cleared, receiver is ready for next event
- If `handled == false`, the system InputDispatcher may deliver the event to other windows

**Errors**:
- Returns `std::unexpected(InputError::NO_EVENT_IN_PROGRESS)` if `mCurrentEvent` is empty
- Returns `std::unexpected(InputError::DISPOSED)` if `mDisposed` is true
- Returns `std::unexpected(InputError::TYPE_MISMATCH)` if event type doesn't match `mCurrentEvent`

**Returns**: `std::expected<void, InputError>`

---

### `dispose`

```cpp
void dispose();
```

**Preconditions**:
- Called exclusively on the Looper thread

**Postconditions**:
- FD watcher unregistered from Looper
- `InputChannel` closed
- `mDisposed = true`
- All subsequent public method calls (except `dispose()` again) return `InputError::DISPOSED`

**Called by**: Application when input reception should stop (e.g., window destroyed)

---

### `consumeEvents` (Internal)

```cpp
std::vector<std::variant<MotionEvent, KeyEvent>> consumeEvents();
```

**Preconditions**:
- Called exclusively on the Looper thread (from FD watcher callback)
- `!mDisposed`

**Postconditions**:
- All available events read from the socket and parsed
- Returns a vector of parsed events (may be empty if no data available)

**Returns**: `std::vector<std::variant<MotionEvent, KeyEvent>>` — zero or more parsed events

**Errors**:
- Returns empty vector on EAGAIN/EINTR (no data available)
- Throws `std::runtime_error` on fatal read errors (socket closed, corrupted data)

---

### `consumeBatchedInputEvents`

```cpp
bool consumeBatchedInputEvents(int64_t frameTimeNanos);
```

**Preconditions**:
- Called exclusively on the Looper thread
- `!mDisposed`

**Postconditions**:
- Forces delivery of all batched pending events
- Returns whether a batch was consumed

**Returns**: `bool` — true if a batch was consumed, false otherwise

---

### `probablyHasInput`

```cpp
bool probablyHasInput() const;
```

**Preconditions**: None

**Postconditions**: May return false negatives (event arrived but not yet detected)

**Returns**: `bool` — true if events are likely available

---

### `onFocusEvent`

```cpp
void onFocusEvent(bool hasFocus);
```

**Preconditions**: Called on the Looper thread

**Postconditions**: Focus state propagated to associated view (if available)

---

### `onTouchModeChanged`

```cpp
void onTouchModeChanged(bool inTouchMode);
```

**Preconditions**: Called on the Looper thread

**Postconditions**: Touch mode state updated

---

## Interface: `ViewGroup` Extensions

### `dispatch_pointer_event`

```cpp
bool dispatch_pointer_event(const MotionEvent& event);
```

**Preconditions**:
- `event` is a valid motion event (action, coordinates set)
- `children_` contains zero or more child views

**Postconditions**:
- If `on_intercept_touch_event(event)` returns true: event dispatched to this group's `on_touch_event()`
- Otherwise: event dispatched to the first child whose bounds contain the event coordinates (reverse Z-order)
- Coordinates transformed to child's local space via `offset_location()` before forwarding
- Returns true if the event was handled by any descendant

**Called by**: `ViewRootImpl` stub, or external input dispatcher

---

### `on_intercept_touch_event` (Virtual)

```cpp
virtual bool on_intercept_touch_event(const MotionEvent& event);
```

**Default**: Returns `false` (do not intercept)

**Postconditions**: If returns true, this `ViewGroup` captures the remainder of the touch sequence

---

## Error Types

```cpp
enum class InputError {
    NO_EVENT_IN_PROGRESS,
    DISPOSED,
    TYPE_MISMATCH,
    SOCKET_READ_ERROR,
    SOCKET_WRITE_ERROR,
    INVALID_CHANNEL,
    WIRE_FORMAT_ERROR,
};
```
