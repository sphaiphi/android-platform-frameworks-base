
# TimeInterpolator - Reverse Engineering Documentation

## Executive Summary
`TimeInterpolator` is a fundamental interface in the animation system that defines how time is processed during an animation. Its purpose is to map the linear passage of time (represented as a fraction from 0.0 to 1.0) to a transformed, potentially non-linear fraction. This transformed fraction is then used to calculate the animated value, allowing for effects like acceleration, deceleration, bouncing, and overshooting.

## Architecture Overview
*   **Functional Interface**: This is a simple, single-method interface, making it a "functional interface" in Java 8+ terms. Its sole purpose is to define the signature for a function that transforms a float.
*   **Strategy Pattern**: `TimeInterpolator` is an implementation of the Strategy design pattern. The `Animator` class holds a reference to a `TimeInterpolator` object. The `Animator`'s timing logic delegates the "interpolation strategy" to this object, allowing the animation's pacing to be changed without altering the `Animator` itself.
*   **Implementations**: The Android framework provides many concrete implementations of this interface in the `android.view.animation` package, such as `LinearInterpolator`, `AccelerateDecelerateInterpolator`, `BounceInterpolator`, etc.

## Detailed Functionality

### `getInterpolation(float input)`
*   **Purpose**: This is the single method defined by the interface. It takes a linear time fraction and returns a modified, "interpolated" fraction.
*   **Input**: The `input` parameter is a `float` that represents the elapsed fraction of an animation's duration. It will always be a value that progresses linearly from 0.0 at the beginning to 1.0 at the end of the animation interval.
*   **Output**: The return value is the result of applying the interpolator's curve to the input.
    *   For a `LinearInterpolator`, the output is always equal to the input.
    *   For an `AccelerateInterpolator`, the output will be less than the input for most of the duration, creating a slow start and fast end.
    *   The output is not constrained to the [0.0, 1.0] range. Interpolators like `AnticipateOvershootInterpolator` can return values less than 0 or greater than 1, causing the animation to "undershoot" its start value or "overshoot" its end value before settling.

## Data Model
This is an interface and has no data members. Implementations are often, but not always, stateless.

## Java-to-C++ Translation Guide
*   **Abstract Base Class**: In C++, this would be defined as an abstract base class with a single pure virtual function.

    ```cpp
    class TimeInterpolator {
    public:
        virtual ~TimeInterpolator() = default;
        virtual float getInterpolation(float input) const = 0;
    };
    ```
    Marking the method `const` is a good practice if the interpolators are expected to be stateless.

*   **`std::function`**: Alternatively, because it is a single-method interface, it could be represented by a `std::function` type alias, which would allow lambdas and other callables to be used directly as interpolators without requiring them to inherit from a base class.

    ```cpp
    using TimeInterpolator = std::function<float(float)>;
    ```
    This approach is often more flexible and idiomatic in modern C++.

*   **Implementation**: The mathematical formulas from the various Android interpolator implementations (e.g., `(float)(Math.cos((input + 1) * Math.PI) / 2.0f) + 0.5f` for `AccelerateDecelerateInterpolator`) would need to be translated directly to their C++ equivalents using functions from `<cmath>`.

## Implementation Risks
*   There are no risks in the interface itself. The risks lie in the implementations. A poorly designed interpolation curve can result in animations that feel unnatural or have visual discontinuities (e.g., if the function is not continuous or its derivative is not continuous).

## Questions for C++ Team
*   For the C++ animation API, should we define `TimeInterpolator` as an abstract base class (mirroring Java) or as a `std::function` type alias (more modern C++)?
*   Which of the standard Android interpolators (`Linear`, `AccelerateDecelerate`, `Bounce`, etc.) are required to be ported to C++?
