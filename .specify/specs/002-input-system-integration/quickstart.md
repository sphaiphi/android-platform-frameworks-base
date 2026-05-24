# Quickstart: Input System Integration

## Overview

This guide shows how to use the `InputEventReceiver` to receive and dispatch input events in the Android framework C++ core.

## Building

```bash
# Host build (CMake + GoogleTest)
cmake -B build -S core/cpp
cmake --build build
cd build && ctest --output-on-failure
```

## Basic Usage: Receiving Touch Events

### 1. Create a Custom InputEventReceiver

Subclass `InputEventReceiver` and implement `onInputEvent()`:

```cpp
#include <android/view/InputEventReceiver.h>
#include <android/view/MotionEvent.h>
#include <android/os/Looper.h>
#include <memory>
#include <variant>

class MyInputReceiver : public android::view::InputEventReceiver {
public:
    MyInputReceiver(std::shared_ptr<android::view::InputChannel> channel,
                    std::shared_ptr<android::os::Looper> looper)
        : InputEventReceiver(std::move(channel), std::move(looper)) {}

protected:
    void onInputEvent(std::variant<android::view::MotionEvent, android::view::KeyEvent> event) override {
        // Process the event
        std::visit([](auto& evt) {
            using T = std::decay_t<decltype(evt)>;
            if constexpr (std::is_same_v<T, android::view::MotionEvent>) {
                // Handle motion event
                auto action = evt.get_action();
                float x = evt.get_x();
                float y = evt.get_y();
                // ... process touch coordinates ...
            }
            // KeyEvent handling similarly
        }, event);

        // IMPORTANT: Must call finishInputEvent before returning
        finishInputEvent(std::move(event), true);
    }
};
```

### 2. Create and Register the Receiver

```cpp
// Assuming you have an InputChannel from the window manager
auto channel = std::make_shared<android::view::InputChannel>("MyWindow", native_handle);
auto looper = android::os::Looper::my_looper();

auto receiver = std::make_shared<MyInputReceiver>(channel, looper);
// The receiver is automatically registered with the Looper's FD watcher
```

### 3. Handle Events

Events arrive on the Looper thread via `onInputEvent()`. The callback is invoked when data is available on the input channel socket.

```cpp
// Inside onInputEvent():
std::visit([](auto& evt) {
    if constexpr (std::is_same_v<std::decay_t<decltype(evt)>, android::view::MotionEvent>) {
        switch (evt.get_action()) {
            case android::view::MotionEvent::ACTION_DOWN:
                // Finger touched screen
                break;
            case android::view::MotionEvent::ACTION_MOVE:
                // Finger moved
                break;
            case android::view::MotionEvent::ACTION_UP:
                // Finger lifted
                break;
            case android::view::MotionEvent::ACTION_CANCEL:
                // Gesture cancelled
                break;
        }
    }
}, event);

// Always finish the event
finishInputEvent(std::move(event), handled);
```

### 4. Dispose When Done

```cpp
receiver->dispose();
// Unregisters from Looper, closes the input channel
```

## ViewGroup Touch Dispatch

### Dispatching Events Through the Hierarchy

```cpp
// Create a view hierarchy
auto root = std::make_shared<android::view::ViewGroup>();
auto child = std::make_shared<android::view::View>();
root->add_view(child);

// Set layout bounds (required for hit-testing)
child->layout(100, 100, 200, 200);  // left, top, right, bottom

// Dispatch a touch event
MotionEvent down(MotionEvent::ACTION_DOWN, 150.0f, 150.0f);
bool handled = root->dispatch_pointer_event(down);
// handled == true if the child received and handled the event
// Coordinates are automatically transformed to child's local space (50, 50)
```

### Intercepting Events in a ViewGroup

```cpp
class InterceptingGroup : public android::view::ViewGroup {
protected:
    bool on_intercept_touch_event(const MotionEvent& event) override {
        // Return true to intercept and consume the event
        if (event.get_action() == MotionEvent::ACTION_DOWN) {
            return true;  // Capture the rest of the touch sequence
        }
        return false;  // Let children handle it
    }
};
```

## Testing

### Unit Test Example

```cpp
#include <gtest/gtest.h>
#include <android/view/InputEventReceiver.h>

TEST(InputEventReceiverTest, BasicDispatch) {
    // Create mock channel and looper
    auto channel = std::make_shared<MockInputChannel>();
    auto looper = std::make_shared<MockLooper>();

    bool callback_called = false;
    auto receiver = std::make_shared<TestReceiver>(channel, looper);

    // Inject a synthetic event through the mock channel
    // ... (mock setup)

    // Verify callback was invoked
    EXPECT_TRUE(callback_called);
}
```

### Running Tests

```bash
cd build && ctest -R InputEventReceiver --output-on-failure
cd build && ctest -R ViewGroupDispatch --output-on-failure
```

## Key Constraints

1. **Single-threaded**: All `InputEventReceiver` methods must be called on the Looper thread
2. **Sequential events**: Must call `finishInputEvent()` before the next event is delivered
3. **Zero-cost dispatch**: Events use `std::variant<MotionEvent, KeyEvent>` — no virtual dispatch
4. **RAII**: Always call `dispose()` when done to release the input channel FD
5. **Batching**: `consumeEvents()` reads all available socket data — no artificial per-frame limit
