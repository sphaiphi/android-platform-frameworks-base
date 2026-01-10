
# Keyframe - Reverse Engineering Documentation

## Executive Summary
`Keyframe` is an abstract class that represents a single point in time and value in an animation. A sequence of keyframes is used to define the path of an animation. Each keyframe holds a "fraction" (representing a point in time as a fraction of the total duration, from 0.0 to 1.0), a value, and an optional `TimeInterpolator` which governs the rate of change for the interval *preceding* this keyframe.

## Architecture Overview
*   **Abstract Base Class**: `Keyframe` itself is abstract. The public API provides static factory methods (`ofInt`, `ofFloat`, `ofObject`) that return instances of hidden, type-specific concrete subclasses (`IntKeyframe`, `FloatKeyframe`, `ObjectKeyframe`).
*   **Factory Pattern**: This use of factory methods hides the implementation details of the type-specific subclasses, providing a clean public API while allowing for internal performance optimizations (e.g., avoiding object boxing for primitive types).
*   **Value Holder**: A `Keyframe` object primarily holds three pieces of information:
    1.  `mFraction`: The point in time.
    2.  `mValue`: The value of the animated property at that time.
    3.  `mInterpolator`: The interpolation function to use for the time interval leading up to this keyframe.

## Detailed Functionality

### Factory Methods (`ofInt`, `ofFloat`, `ofObject`)
*   **Purpose**: These are the public entry points for creating `Keyframe` objects.
*   **Behavior**: They instantiate and return the appropriate internal subclass (`IntKeyframe`, `FloatKeyframe`, or `ObjectKeyframe`).
*   **Overloads**: Each factory method has two overloads:
    *   One takes a `fraction` and a `value`. This creates a fully defined keyframe.
    *   One takes only a `fraction`. This creates a placeholder keyframe where the value is `null`. This is a special feature used by `ObjectAnimator`. When the animation starts, `ObjectAnimator` finds all keyframes with null values and populates them with the property's current value from the target object. This allows for creating animations that animate *from* or *to* the current state without needing to know the value beforehand.

### Core Properties and Methods
*   **`getFraction()` / `setFraction(float)`**: Get or set the time point for this keyframe (0.0 to 1.0).
*   **`getInterpolator()` / `setInterpolator(TimeInterpolator)`**: Get or set the interpolator. If `null`, a linear interpolation is used.
*   **`getValue()` / `setValue(Object)`**: Abstract methods for getting and setting the value. The concrete subclasses provide type-specific implementations.
*   **`getType()`**: Returns the `Class` of the value (e.g., `int.class`, `float.class`).
*   **`clone()`**: An abstract method requiring subclasses to implement deep cloning.

### Internal Subclasses (`IntKeyframe`, `FloatKeyframe`, `ObjectKeyframe`)
*   **Purpose**: To provide type-safe, optimized storage and access for the most common animated types.
*   **`IntKeyframe` and `FloatKeyframe`**: These subclasses store the value as a primitive `int` or `float` (`mValue`), avoiding the need for `Integer` or `Float` wrapper objects. They provide specialized getter methods (`getIntValue()`, `getFloatValue()`).
*   **`ObjectKeyframe`**: This is the generic fallback for all other types. It stores the value as an `Object`.

## Data Model
*   `mFraction`: A `float` from 0.0 to 1.0.
*   `mValueType`: A `Class` object representing the type of the value.
*   `mHasValue`: A `boolean` flag indicating whether a value has been assigned. This is `false` for placeholder keyframes created with `ofInt(fraction)`.
*   `mValueWasSetOnStart`: A `boolean` flag used by `ObjectAnimator` to know if it can/should overwrite a placeholder value at the start of the animation.
*   `mInterpolator`: A `TimeInterpolator` reference.

## Java-to-C++ Translation Guide
*   **Abstract Base Class and Subclasses**: This hierarchy translates well to C++ polymorphism.
    *   A C++ `Keyframe` abstract base class would define the common interface (`getFraction`, `getInterpolator`, `clone`, etc.).
    *   `getValue` and `setValue` would likely be templated or return a generic type like `std::any`.
    *   Concrete subclasses like `IntKeyframe` and `FloatKeyframe` would inherit from `Keyframe` and provide efficient, type-specific storage and access.

    ```cpp
    class Keyframe {
    public:
        virtual ~Keyframe() = default;
        // ... common interface ...
        virtual std::unique_ptr<Keyframe> clone() const = 0;
        virtual std::any getValue() const = 0;
    };

    class IntKeyframe : public Keyframe {
    private:
        int mValue;
    public:
        int getIntValue() const { return mValue; }
        std::any getValue() const override { return mValue; }
        // ...
    };
    ```
*   **Factory Functions**: The static `of...` methods would be translated to C++ free functions that return a `std::unique_ptr<Keyframe>` or a `std::shared_ptr<Keyframe>`, hiding the specific subclass being instantiated.
*   **`TimeInterpolator`**: The `TimeInterpolator` interface would also need a C++ equivalent abstract base class.
*   **Type Information**: Java's `Class` object (`mValueType`) for runtime type identification could be replaced in C++ with `typeid` or, more robustly, by embedding a type enum in the base class that is set by the subclasses.

## Implementation Risks
*   **Polymorphism Overhead**: A polymorphic C++ implementation with virtual function calls will have some performance overhead compared to a non-polymorphic one. However, this is necessary to replicate the design, and the type-specific subclasses (`IntKeyframe`, `FloatKeyframe`) are themselves an optimization to mitigate this for the most common cases.
*   **Cloning**: The `clone()` implementation must be correct in all subclasses to ensure that the animation caching system works properly and that animators can be safely reused.

## Questions for C++ Team
*   What is the C++ strategy for representing a generic value, equivalent to Java's `Object`? Will we use `std::any`, `std::variant`, or a custom solution?
*   How will the C++ `Keyframe` factory functions manage memory? Should they return `std::unique_ptr`, `std::shared_ptr`, or raw pointers?
