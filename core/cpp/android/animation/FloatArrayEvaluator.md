
# FloatArrayEvaluator - Reverse Engineering Documentation

## Executive Summary
`FloatArrayEvaluator` is a class that implements the `TypeEvaluator` interface for `float[]` (float arrays). It is used to calculate the intermediate values for an animation that operates on arrays of floats, by performing a linear interpolation on each element of the array independently.

## Architecture Overview
*   **Specialized `TypeEvaluator`**: It is a specific implementation of the `TypeEvaluator<float[]>` interface, designed to work with `ValueAnimator`s that animate properties represented by float arrays (e.g., vertices of a shape, multiple transformation matrix values).
*   **Optional Reusability**: It has two constructors. One creates a new `float[]` for the result on every animation frame, which is safe but less memory-efficient. The other allows the caller to provide a "reuse" array, which is then modified and returned on every frame. This is much more memory-efficient but requires the caller to be careful not to hold onto or misuse the returned array, as its contents will change on the next frame.

## Detailed Functionality

### Constructors
*   **`FloatArrayEvaluator()`**: A default constructor that sets up the evaluator to allocate a new result array on each evaluation.
*   **`FloatArrayEvaluator(float[] reuseArray)`**: A constructor that takes a `float[]` as an argument. This `reuseArray` will be used to store the result of all subsequent `evaluate()` calls, avoiding memory allocation during the animation.

### `evaluate(float fraction, float[] startValue, float[] endValue)`
*   **Purpose**: This is the core method of the class. Given a start array, an end array, and a fraction, it calculates the interpolated array.
*   **Algorithm**:
    1.  It first determines which array to use for the result. If a `reuseArray` was provided in the constructor (`mArray != null`), it uses that. Otherwise, it allocates a new `float[]` with the same length as the `startValue`.
    2.  It then iterates through the arrays from `i = 0` to `array.length - 1`.
    3.  In each iteration, it performs a simple linear interpolation for that element: `array[i] = startValue[i] + fraction * (endValue[i] - startValue[i])`.
    4.  After the loop, it returns the populated result array.
*   **Preconditions**: This method assumes that `startValue` and `endValue` have the same length. The behavior is undefined if they do not. The `ValueAnimator` framework ensures this.

## Data Model
*   `mArray`: A private `float[]` field. It is `null` if the default constructor is used. If the other constructor is used, it holds a reference to the array that will be reused for storing and returning results.

## Java-to-C++ Translation Guide
*   **Class or Namespace**: This can be implemented as a C++ class that mirrors the Java design, or as a set of functions within a namespace. The class approach is slightly cleaner if you need to support the optional "reuse" array pattern.
*   **`std::vector<float>`**: The C++ equivalent of `float[]` is `std::vector<float>`.
*   **`evaluate` Function**: The `evaluate` method can be translated directly to a C++ function. It would take a `float` fraction and two `const std::vector<float>&` arguments.
*   **Reusability Pattern**: The two-constructor design can be replicated in C++.

    ```cpp
    #include <vector>

    class FloatArrayEvaluator {
    public:
        // Default constructor, allocates new vector on each call.
        FloatArrayEvaluator() : mArray(nullptr) {}

        // Constructor that reuses the provided vector.
        explicit FloatArrayEvaluator(std::vector<float>* reuseArray) : mArray(reuseArray) {}

        std::vector<float> evaluate(float fraction,
                                    const std::vector<float>& startValue,
                                    const std::vector<float>& endValue) {
            std::vector<float>* array = mArray;
            if (array == nullptr) {
                // In C++, it's more idiomatic to just create the result on the stack
                // and rely on RVO (Return Value Optimization).
                std::vector<float> newArray(startValue.size());
                array = &newArray;
            }

            for (size_t i = 0; i < array->size(); ++i) {
                float start = startValue[i];
                float end = endValue[i];
                (*array)[i] = start + fraction * (end - start);
            }
            return *array;
        }

    private:
        std::vector<float>* mArray; // A raw pointer to the reused array.
    };
    ```
    *Note*: The C++ version is slightly different. Returning a `std::vector` by value is often efficient due to RVO and move semantics, potentially making the "reuse" pattern less critical than in older Java versions where object allocation was more expensive. However, to perfectly mirror the Java design, passing in a pointer to the array to be modified is the direct equivalent.

## Implementation Risks
*   **Array Length Mismatch**: If the start and end arrays have different lengths, the loop could read out of bounds. While the animation framework should prevent this, a robust C++ implementation might add an assertion or check (`assert(startValue.size() == endValue.size())`).
*   **Misuse of Reused Array**: If the C++ version implements the reuse pattern, callers must be aware that the contents of the returned vector (or the vector they passed in) are volatile and will be overwritten on the next animation frame. This is a common source of bugs if not handled carefully.

## Questions for C++ Team
*   Is the performance gain from reusing the result vector considered significant enough in our C++ environment to warrant the complexity and potential for misuse, or should we prefer the simpler, safer version that always returns a new vector?
