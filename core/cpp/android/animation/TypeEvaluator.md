
# TypeEvaluator - Reverse Engineering Documentation

## Executive Summary
`TypeEvaluator` is a core interface in the Android animation framework that makes the system extensible. It defines the contract for a class that knows how to interpolate between two values of an arbitrary type. By implementing this interface for a custom object type, developers can animate properties of that type, even if the system has no built-in knowledge of it.

## Architecture Overview
*   **Strategy Pattern**: `TypeEvaluator` is a key component of the Strategy design pattern used by `ValueAnimator`. `ValueAnimator` holds a reference to a `TypeEvaluator`. On every animation frame, the `ValueAnimator` calculates the elapsed fraction and then delegates the task of calculating the actual animated value to the `TypeEvaluator`.
*   **Functional Interface**: It is a generic, single-method interface, `TypeEvaluator<T>`, where `T` is the type of the value to be interpolated.
*   **Default Implementations**: The framework provides default implementations for common types, such as `IntEvaluator`, `FloatEvaluator`, and `ArgbEvaluator`. If an animator is created for a type that the system doesn't recognize, the developer must provide a custom `TypeEvaluator` instance via `ValueAnimator.setEvaluator()`.

## Detailed Functionality

### `evaluate(float fraction, T startValue, T endValue)`
*   **Purpose**: This is the single method in the interface. Its job is to calculate and return the interpolated value that lies `fraction` of the way between `startValue` and `endValue`.
*   **Parameters**:
    *   `fraction`: A `float` from 0.0 to 1.0 representing the elapsed, interpolated time.
    *   `startValue`: The starting value of the animation interval (type `T`).
    *   `endValue`: The ending value of the animation interval (type `T`).
*   **Return Value**: The calculated intermediate value of type `T`.
*   **Default Logic**: The interface documentation suggests that a typical implementation will perform simple linear interpolation: `result = startValue + fraction * (endValue - startValue)`. However, this is only a recommendation; an implementation is free to use any logic it wants, including non-linear interpolation, as long as it returns a value of type `T`.

## Data Model
This is an interface and has no data members. Implementations are often, but not always, stateless (e.g., `IntEvaluator`). Some, like `RectEvaluator`, can be stateful if they support a "reuse" object to avoid memory allocations.

## Java-to-C++ Translation Guide
*   **Abstract Templated Class**: The most direct translation to C++ is a templated abstract base class.

    ```cpp
    template<typename T>
    class TypeEvaluator {
    public:
        virtual ~TypeEvaluator() = default;
        virtual T evaluate(float fraction, T startValue, T endValue) = 0;
    };
    ```
    This allows for creating concrete evaluators for any type, just like in Java. For example, a C++ `ArgbEvaluator` would inherit from `TypeEvaluator<uint32_t>`.

*   **`std::function`**: As a functional interface, it could also be represented by a `std::function` type alias, though the abstract base class approach is a more direct parallel to the Java design and makes the "evaluator" concept more explicit in the type system.

## Implementation Risks
*   **Correctness of Logic**: The primary risk lies in the implementation of the `evaluate` method. The logic must be correct for the custom type. For a struct with multiple fields (like `Rect`), this means correctly interpolating each field. For more complex objects, the logic can be non-trivial.
*   **Performance**: The `evaluate` method is called on every animation frame. Any expensive operations, such as memory allocations, within this method can cause performance issues and animation jank. Implementations should be as lightweight as possible. This is why many of the built-in Android evaluators have a "reuse" object constructor to avoid allocations.

## Questions for C++ Team
*   Will the C++ animation framework use a templated abstract class for `TypeEvaluator`?
*   What are the guidelines for implementing custom evaluators in C++ regarding performance and memory allocation? Should they also support an optional "reuse" object pattern?
