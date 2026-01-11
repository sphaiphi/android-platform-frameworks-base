
# TimeAnimator - Reverse Engineering Documentation

## Executive Summary
`TimeAnimator` is a specialized subclass of `ValueAnimator` that provides a simple, continuous "ticker." Unlike a standard `ValueAnimator`, it does not have a duration, does not interpolate between values, and does not end on its own. Instead, its sole purpose is to call a `TimeListener` on every animation frame, providing the total elapsed time since the animator was started and the delta time since the previous frame. It is a utility for creating custom animations or simulations that need a consistent timing pulse.

## Architecture Overview
*   **Subclass of `ValueAnimator`**: It inherits the basic timing and lifecycle infrastructure from `ValueAnimator`, including `start()`, `cancel()`, and integration with `AnimationHandler`.
*   **Callback-focused**: Its primary feature is the `TimeListener` interface. The animator's main job is to invoke the `onTimeUpdate` method of this listener on every frame.
*   **No "Animation" Logic**: It overrides key methods from `ValueAnimator` to disable the standard animation logic. `animateValue()` and `initAnimation()` are no-ops because `TimeAnimator` does not manage or interpolate any values itself.

## Detailed Functionality

### `TimeListener` (Nested Interface)
*   **Purpose**: Defines the callback for receiving timing events.
*   **`onTimeUpdate(TimeAnimator animation, long totalTime, long deltaTime)`**: This is the single method.
    *   `totalTime`: The time in milliseconds that has passed since `start()` was called.
    *   `deltaTime`: The time in milliseconds that has passed since the last frame's `onTimeUpdate` call. This will be `0` on the very first frame.

### `animateBasedOnTime(long currentTime)`
*   **Purpose**: This is the core logic method, overridden from `ValueAnimator`. It's called on every animation frame by the `AnimationHandler`.
*   **Algorithm**:
    1.  It checks if a `TimeListener` has been set.
    2.  It calculates `totalTime` by subtracting the animation's `mStartTime` from the `currentTime`.
    3.  It calculates `deltaTime` by subtracting the `mPreviousTime` from the `currentTime`. It handles the first frame case where `mPreviousTime` is -1 by setting `deltaTime` to 0.
    4.  It updates `mPreviousTime` to the `currentTime` for use in the next frame.
    5.  It calls `mListener.onTimeUpdate(...)` with the calculated times.
    6.  It always returns `false`, indicating that the animation is never "done." It will run forever until `cancel()` or `end()` is called.

### Overridden `ValueAnimator` Methods
*   **`start()`**: Calls the superclass `start()` and also resets `mPreviousTime` to -1 to ensure `deltaTime` is calculated correctly on the first frame of the new run.
*   **`setCurrentPlayTime(long playTime)`**: This is overridden to provide seek-like functionality. It works by reverse-calculating what the `mStartTime` *should have been* for the animation to have reached the given `playTime` at this moment. It then immediately calls `animateBasedOnTime` to fire a one-time update with the new time.
*   **`animateValue(float fraction)`**: Overridden to do nothing.
*   **`initAnimation()`**: Overridden to do nothing.

## Data Model
*   `mListener`: A reference to the user-provided `TimeListener` instance.
*   `mPreviousTime`: A `long` that stores the timestamp of the last animation frame. This is essential for calculating `deltaTime`.

## Java-to-C++ Translation Guide
*   **Subclass of `ValueAnimator`**: A C++ `TimeAnimator` would inherit from the C++ `ValueAnimator` base class.
*   **`TimeListener` Interface**: This would become a C++ abstract base class with a pure virtual `onTimeUpdate` method. The C++ `TimeAnimator` would hold a pointer to an object of this type.
*   **`animateBasedOnTime` Logic**: The logic for calculating `totalTime` and `deltaTime` can be translated directly to a C++ `animateBasedOnTime` override. The C++ method would also always return `false`.
*   **Empty Overrides**: The C++ `TimeAnimator` would also provide empty overrides for `animateValue` and `initAnimation`.

## Implementation Risks
*   **Infinite Loop**: The core design is that this animator runs forever. Client code that uses `TimeAnimator` is responsible for calling `cancel()` or `end()` to stop it. Forgetting to do so will result in the animation running indefinitely, consuming battery, even if its effects are no longer visible. (Note: The `AnimationHandler`'s background pausing logic helps mitigate this, but it's still a risk).
*   **Time Calculation**: The time calculations rely on the `mStartTime` being set correctly by the `ValueAnimator` superclass and the `mPreviousTime` being managed correctly within `TimeAnimator` itself. Any errors in this state management would lead to incorrect `totalTime` or `deltaTime` values.

## Questions for C++ Team
*   What is the standard C++ pattern for listeners in our project? Should `setTimeListener` take a raw pointer, a `std::shared_ptr`, or use a signal/slot mechanism?
*   How will the C++ `TimeAnimator` handle the case where it is used without a `TimeListener` being set? (The Java version simply does nothing in its `animateBasedOnTime` method, which is the correct behavior).
