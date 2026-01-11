
# IntEvaluator - Reverse Engineering Documentation

## Executive Summary
`IntEvaluator` is a simple, stateless class that implements the `TypeEvaluator` interface for `int` values. It provides the standard linear interpolation logic required to animate between a starting and ending integer value. It is the default evaluator used by `ValueAnimator` when animating integer values.

## Architecture Overview
*   **Stateless `TypeEvaluator`**: This class is a straightforward implementation of `TypeEvaluator<Integer>`. It contains no fields and its `evaluate` method is a pure function.
*   **No Singleton**: Unlike `ArgbEvaluator`, it does not have a public `getInstance()` method. Since it is stateless, a single instance can be reused, but the framework typically creates a new one for each animator that needs it.

## Detailed Functionality

### `evaluate(float fraction, Integer startValue, Integer endValue)`
*   **Purpose**: To calculate the interpolated integer value between a start and end value.
*   **Algorithm**:
    1.  It receives the `startValue` and `endValue` as `Integer` objects due to Java's generics.
    2.  It relies on auto-unboxing to convert the `Integer` objects to `int` primitives (`int startInt = startValue;`).
    3.  It performs the linear interpolation using floating-point math: `startInt + fraction * (endValue - startInt)`.
    4.  The final floating-point result is cast to an `int`, which truncates (removes) the decimal part.
    5.  The resulting `int` is auto-boxed into an `Integer` object to be returned, matching the generic `TypeEvaluator<Integer>` signature.

## Data Model
This class is stateless and has no data members.

## Java-to-C++ Translation Guide
*   **Free Function**: As a stateless utility, this is best implemented in C++ as a free function inside a namespace, rather than a class.

    ```cpp
    namespace int_evaluator {

    int evaluate(float fraction, int startValue, int endValue) {
        return static_cast<int>(startValue + fraction * (static_cast<float>(endValue - startValue)));
    }

    } // namespace int_evaluator
    ```
*   **Type Safety and Casting**: The C++ function can operate directly on `int` primitives, making it more direct than the Java version which deals with `Integer` objects. The calculation involves a multiplication with a `float`, so the integer difference (`endValue - startValue`) should be cast to a `float` before the multiplication to avoid integer overflow and ensure a floating-point result. The final result must then be explicitly cast back to an `int` using `static_cast<int>()` to replicate the truncation behavior.

## Implementation Risks
*   **Integer Truncation vs. Rounding**: The Java implementation implicitly truncates the result due to the `(int)` cast. A C++ implementation must use `static_cast<int>()` and not a rounding function like `std::round()` to produce the identical behavior. Using a rounding function would cause the animation to jump to the next integer value at the halfway point (0.5), whereas truncation makes the jump happen only at the very end (1.0). This difference can be visually noticeable.

## Questions for C++ Team
*   Is the truncation behavior of the integer cast the desired behavior for all integer animations, or should rounding be considered for the C++ implementation? (To be compatible, truncation is required).
*   Will this be implemented as part of a generic `TypeEvaluator` template system or as a standalone utility function?
