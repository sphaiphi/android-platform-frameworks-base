
# IntArrayEvaluator - Reverse Engineering Documentation

## Executive Summary
`IntArrayEvaluator` is a class that implements the `TypeEvaluator` interface for `int[]` (integer arrays). It is used to calculate the intermediate values for an animation that operates on arrays of integers, by performing a linear interpolation on each element of the array independently.

## Architecture Overview
*   **Specialized `TypeEvaluator`**: It is a specific implementation of the `TypeEvaluator<int[]>` interface, designed to work with `ValueAnimator`s that animate properties represented by integer arrays.
*   **Optional Reusability**: Like `FloatArrayEvaluator`, it provides two constructors. One allocates a new `int[]` for the result on every animation frame, while the other allows the caller to provide a "reuse" array. This reusable array is modified and returned on every frame, which is more memory-efficient but requires the caller to be careful about how they use the returned value.

## Detailed Functionality

### Constructors
*   **`IntArrayEvaluator()`**: A default constructor. When this is used, the `evaluate` method will allocate a new result array on each call.
*   **`IntArrayEvaluator(int[] reuseArray)`**: A constructor that takes an `int[]` as an argument. This `reuseArray` will be used to store the result of all subsequent `evaluate()` calls, preventing memory allocations during the animation loop.

### `evaluate(float fraction, int[] startValue, int[] endValue)`
*   **Purpose**: To calculate the interpolated integer array between a start array and an end array for a given fraction.
*   **Algorithm**:
    1.  It determines which array to use for the result. If a `reuseArray` was provided (`mArray != null`), it uses that. Otherwise, it allocates a new `int[]` of the same length as the `startValue`.
    2.  It iterates through the arrays from `i = 0` to `array.length - 1`.
    3.  For each element, it performs a linear interpolation: `start + fraction * (end - start)`.
    4.  Crucially, the result of the floating-point calculation is cast to an `int`, effectively truncating any fractional part.
    5.  The resulting integer is stored in the result array at index `i`.
    6.  After the loop, it returns the populated result array.
*   **Preconditions**: This method assumes that `startValue` and `endValue` have the same length.

## Data Model
*   `mArray`: A private `int[]` field. It is `null` if the default constructor is used. If the other constructor is used, it holds a reference to the array that will be reused for storing and returning results.

## Java-to-C++ Translation Guide
*   **Class or Namespace**: This can be implemented as a C++ class that mirrors the Java design, or as a set of functions within a namespace.
*   **`std::vector<int>`**: The C++ equivalent of `int[]` is `std::vector<int>`.
*   **`evaluate` Function**: The `evaluate` method can be translated directly to a C++ function taking a `float` fraction and two `const std::vector<int>&` arguments. The core logic is identical.
*   **Integer Conversion**: The explicit cast `(int)` in Java should be replicated in C++ using `static_cast<int>()`. This truncation behavior is a key part of the algorithm.

    ```cpp
    #include <vector>

    class IntArrayEvaluator {
    public:
        IntArrayEvaluator() : mArray(nullptr) {}
        explicit IntArrayEvaluator(std::vector<int>* reuseArray) : mArray(reuseArray) {}

        std::vector<int> evaluate(float fraction,
                                  const std::vector<int>& startValue,
                                  const std::vector<int>& endValue) {
            std::vector<int>* array = mArray;
            std::vector<int> newArray; // Used only if mArray is null
            if (array == nullptr) {
                newArray.resize(startValue.size());
                array = &newArray;
            }

            for (size_t i = 0; i < array->size(); ++i) {
                int start = startValue[i];
                int end = endValue[i];
                (*array)[i] = static_cast<int>(start + fraction * (static_cast<float>(end - start)));
            }
            return *array;
        }

    private:
        std::vector<int>* mArray;
    };
    ```

## Implementation Risks
*   **Array Length Mismatch**: A C++ implementation should include an `assert` to ensure the start and end vectors are of the same size to prevent out-of-bounds access.
*   **Integer Truncation**: The conversion from the intermediate `float` result back to `int` is a truncating cast. This is the intended behavior and must be preserved. Using a different rounding method (like `round()`) would produce different animation results.
*   **Misuse of Reused Array**: As with `FloatArrayEvaluator`, if the C++ version implements the reuse pattern, callers must be aware that the returned vector's contents are volatile.

## Questions for C++ Team
*   Given that C++ `std::vector` copy/move semantics are generally efficient, is the optional "reuse array" optimization pattern necessary or desirable for the C++ implementation?
