
# Animator - Reverse Engineering Documentation

## Executive Summary
`Animator` is the abstract base class for Android's property animation system. It defines the core API and lifecycle for all animators, including starting, ending, pausing, resuming, and listening for lifecycle events. Subclasses like `ValueAnimator` and `AnimatorSet` implement this contract to provide specific animation functionality.

## Architecture Overview
*   **Abstract Base Class**: `Animator` defines a common interface for different types of animators but does not contain any animation logic itself. It provides default or abstract implementations for its methods, which subclasses must override.
*   **Lifecycle and State**: It defines the core animation lifecycle:
    *   **Creation**: An animator is configured with properties like duration, start delay, and interpolator.
    *   **Running**: `start()` begins the animation. The animator is now in a "started" and then "running" state.
    *   **Events**: As it runs, it notifies registered `AnimatorListener`s of events like `onAnimationStart`, `onAnimationRepeat`, and `onAnimationEnd`.
    *   **Pausing**: A running animation can be `pause()`d and `resume()`d, with notifications sent to `AnimatorPauseListener`s.
    *   **Ending**: The animation can be explicitly `end()`ed (jump to the final value) or `cancel()`ed (stop in place). Both trigger `onAnimationEnd`.
*   **Listener Pattern**: It uses the listener pattern to allow external objects to observe the animation's lifecycle. It supports two types of listeners: `AnimatorListener` for start/end/repeat/cancel events and `AnimatorPauseListener` for pause/resume events.
*   **Cloning**: It implements `Cloneable`, allowing animators to be used as templates. Cloning an animator creates a new instance with the same configuration but without the runtime state.

## Detailed Functionality

### Core Abstract Methods
Subclasses must provide implementations for these methods:
*   `getStartDelay()` / `setStartDelay(long)`
*   `getDuration()` / `setDuration(long)`
*   `getInterpolator()` / `setInterpolator(TimeInterpolator)`
*   `isRunning()`

### Lifecycle Control Methods
*   **`start()`**: Begins the animation. The default implementation is empty; subclasses override this to start their timing and value calculation.
*   **`cancel()`**: Stops the animation immediately. The default implementation is empty. Subclasses must implement the logic to stop processing and notify listeners.
*   **`end()`**: Jumps the animation to its final value. The default implementation is empty. Subclasses must implement this.
*   **`pause()` / `resume()`**: Toggles the `mPaused` flag and notifies the `AnimatorPauseListener`s. The actual pausing of the animation timing is handled by the subclass (e.g., `ValueAnimator` stops listening to `AnimationHandler`).

### Listener Management
*   **`addListener(AnimatorListener)` / `removeListener(AnimatorListener)`**: Adds or removes a lifecycle listener. Listeners are stored in an `ArrayList`.
*   **`addPauseListener(AnimatorPauseListener)` / `removePauseListener(AnimatorPauseListener)`**: Adds or removes a pause/resume listener.
*   **`notifyListeners(...)`, `notifyPauseListeners(...)`**: Internal helper methods that iterate through the listener lists and invoke the appropriate callback method. They use a clever caching mechanism (`mCachedList`) to avoid allocating a new array on every notification and to prevent `ConcurrentModificationException` if a listener modifies the list from within a callback.

### Internal Animation Hooks
*   **`setupStartValues()` / `setupEndValues()`**: Methods intended for subclasses like `ObjectAnimator` to grab the initial and final values of a property from the target object.
*   **`pulseAnimationFrame(long frameTime)`**: An internal method called by a timing source (like `AnimatorSet`) to drive the animation frame by frame when it's not self-pulsing.
*   **`skipToEndValue(boolean inReverse)`**: A hook for subclasses to implement logic that immediately sets the animated property to its final value.

## Data Model
*   `mListeners`: An `ArrayList<AnimatorListener>` for lifecycle event callbacks.
*   `mPauseListeners`: An `ArrayList<AnimatorPauseListener>` for pause/resume callbacks.
*   `mPaused`: A `boolean` flag to track the paused state.
*   `mChangingConfigurations`: An `int` bitmask used by the resource caching system.
*   `mConstantState`: A reference used for resource caching.
*   `mStartListenersCalled`: A boolean flag to track whether `onAnimationStart` has been fired, to prevent duplicate notifications.

## Java-to-C++ Translation Guide
*   **Abstract Base Class**: This translates directly to a C++ abstract base class with pure virtual functions for the core methods (`getDuration`, `isRunning`, etc.) and virtual methods with empty default implementations for others (`start`, `end`, `cancel`).

    ```cpp
    class Animator {
    public:
        virtual ~Animator() = default;
        virtual void setDuration(long duration) = 0;
        virtual long getDuration() const = 0;
        virtual bool isRunning() const = 0;
        // ... other abstract methods

        virtual void start();
        virtual void end();
        virtual void cancel();
        // ... etc.

        void addListener(AnimatorListener* listener);
        // ... listener management
    };
    ```
*   **Listeners**: The listener interfaces (`AnimatorListener`, `AnimatorPauseListener`) would also become C++ abstract base classes. The `Animator` base class would manage lists of raw pointers or, more safely, `std::weak_ptr`s to listener objects to avoid ownership cycles.
*   **Listener Notification**: The notification helpers would be translated to C++. The logic of copying the listener list before iterating to handle re-entrancy is a critical pattern to preserve.
*   **Cloning**: The C++ class would need a virtual `clone()` method, following the Prototype design pattern, to replicate the Java `clone()` functionality.

## Implementation Risks
*   **Lifecycle Contract**: Subclasses in C++ must rigorously adhere to the lifecycle contract defined by `Animator`. For example, `cancel()` must always be followed by a call to `onAnimationEnd`, and `onAnimationStart` must only be called once per run. Any deviation will break client code that relies on these guarantees.
*   **Listener Management**: If not handled carefully (e.g., with weak pointers), storing lists of listeners can lead to memory leaks or dangling pointers if a listener is destroyed without being removed from the animator.

## Questions for C++ Team
*   What is the standard C++ pattern in our project for managing listeners/observers? Should we use raw pointers, `std::weak_ptr`, or a dedicated signal/slot library?
*   How will the C++ `Animator` base class handle the default `onAnimationStart/End(Animator, boolean)` methods that were added in later Java versions? Will we use default interface methods (C++20), provide two separate listener interfaces, or another pattern?
