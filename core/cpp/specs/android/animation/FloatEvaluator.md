
# FloatEvaluator - Reverse Engineering Documentation

## Executive Summary
`FloatEvaluator` is a simple, stateless class that implements the `TypeEvaluator` interface for `float` values. It provides the standard linear interpolation logic required to animate between a starting and ending float value. It is the default evaluator used by `ValueAnimator` when animating float values.

## Architecture Overview
*   **Stateless `TypeEvaluator`**: This class is a straightforward implementation of `TypeEvaluator<Number>`. It has no fields and its `evaluate` method is a pure function, meaning its output depends only on its inputs.
*   **No Singleton**: Unlike `ArgbEvaluator`, this class does not provide a `getInstance()` singleton pattern. However, since it is stateless, a single instance could be created and reused across multiple animators without issue. The animation framework typically creates a new instance as needed.

## Detailed Functionality

### `evaluate(float fraction, Number startValue, Number endValue)`
*   **Purpose**: To calculate the interpolated float value between a start and end value.
*   **Algorithm**:
    1.  It takes the generic `Number` arguments and converts them to their primitive `float` values using `startValue.floatValue()` and `endValue.floatValue()`.
    2.  It applies the standard linear interpolation (lerp) formula: `result = start + fraction * (end - start)`.
    3.  It returns the resulting `float`, which is auto-boxed into a `Float` object to match the `TypeEvaluator<Number>` return type.
*   **Type Handling**: The use of `Number` as the generic type parameter allows this evaluator to be used with both `Float` and `Integer` values, as both are subclasses of `Number`. The `floatValue()` method handles the conversion.

## Data Model
This class is stateless and has no data members.

## Java-to-C++ Translation Guide
*   **Free Function**: Since the class is stateless and has only one significant method, this functionality is best implemented as a simple, free function in C++, likely within a namespace. There is no need for a C++ class.

    ```cpp
    namespace float_evaluator {

    float evaluate(float fraction, float startValue, float endValue) {
        return startValue + fraction * (endValue - startValue);
    }

    } // namespace float_evaluator
    ```
*   **Type Safety**: The Java version uses `Number` and `floatValue()`. The C++ version can be made more direct and type-safe by operating directly on `float` primitives. If it needed to be part of a generic C++ `TypeEvaluator` interface, it might be a template specialization.

    ```cpp
    // Example of a generic C++ TypeEvaluator
    template<typename T>
    struct TypeEvaluator {
        virtual T evaluate(float fraction, T startValue, T endValue) = 0;
    };

    // Specialization for float
    struct FloatEvaluator : public TypeEvaluator<float> {
        float evaluate(float fraction, float startValue, float endValue) override {
            return startValue + fraction * (endValue - startValue);
        }
    };
    ```
    However, given its simplicity, the free function approach is generally preferable in C++.

## Implementation Risks
*   There are no implementation risks. The logic is a single, simple mathematical formula.

## Questions for C++ Team
*   Will the C++ `TypeEvaluator` system be based on a templated abstract base class, or will we use a different pattern?
*   Given its simplicity, should this just be a free utility function (`lerp`) rather than a formal `Evaluator` class?
