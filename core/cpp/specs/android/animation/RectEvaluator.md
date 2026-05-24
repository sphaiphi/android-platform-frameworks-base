
# RectEvaluator - Reverse Engineering Documentation

## Executive Summary
`RectEvaluator` is a class that implements the `TypeEvaluator` interface for `android.graphics.Rect` objects. It is used to calculate the intermediate `Rect` values for an animation, by performing a linear interpolation on each of the four integer components (`left`, `top`, `right`, `bottom`) of the rectangle independently.

## Architecture Overview
*   **Specialized `TypeEvaluator`**: It is a specific implementation of `TypeEvaluator<Rect>`, designed to work with `ValueAnimator`s that animate `Rect` properties, such as a view's clipping bounds.
*   **Optional Reusability**: Following the same pattern as `PointFEvaluator` and others, it provides two constructors. One allocates a new `Rect` on every frame, while the other takes a "reuse" `Rect` object that is modified and returned on each frame to reduce memory allocations.

## Detailed Functionality

### Constructors
*   **`RectEvaluator()`**: The default constructor. When this is used, the `evaluate` method will allocate a new `Rect` result object on each call.
*   **`RectEvaluator(Rect reuseRect)`**: This constructor takes a `Rect` object. This `reuseRect` will be used to store the result of all subsequent `evaluate()` calls.

### `evaluate(float fraction, Rect startValue, Rect endValue)`
*   **Purpose**: This is the core method. Given a start rectangle, an end rectangle, and a fraction, it calculates the interpolated rectangle.
*   **Algorithm**:
    1.  It performs a separate linear interpolation on each of the four integer components:
        *   `left = startValue.left + (int) ((endValue.left - startValue.left) * fraction)`
        *   `top = startValue.top + (int) ((endValue.top - startValue.top) * fraction)`
        *   `right = startValue.right + (int) ((endValue.right - startValue.right) * fraction)`
        *   `bottom = startValue.bottom + (int) ((endValue.bottom - startValue.bottom) * fraction)`
    2.  The result of the floating-point multiplication is explicitly cast to an `int`, which truncates any fractional part.
    3.  It checks if a reuse object (`mRect`) is available.
    4.  If `mRect` is not null, it calls `mRect.set(left, top, right, bottom)` to modify the existing object and then returns `mRect`.
    5.  If `mRect` is null, it allocates a new `Rect` object (`new Rect(left, top, right, bottom)`) and returns it.

## Data Model
*   `mRect`: A private `Rect` field. It is `null` if the default constructor is used. If the reuse constructor is used, it holds a reference to the `Rect` object that will be modified and returned.

## Java-to-C++ Translation Guide
*   **Class or Namespace**: This can be implemented as a C++ class mirroring the Java design, or as a simple function in a namespace if the object reuse pattern is omitted.
*   **Rect Equivalent**: A C++ `struct` or `class` for `Rect` would be needed, holding the four integer coordinates.

    ```cpp
    struct Rect {
        int left;
        int top;
        int right;
        int bottom;
    };
    ```
*   **`evaluate` Function**: The `evaluate` method can be translated directly to a C++ function.

    ```cpp
    #include "Rect.h" // Assuming Rect struct exists

    class RectEvaluator {
    public:
        RectEvaluator() : mRect(nullptr) {}
        explicit RectEvaluator(Rect* reuse) : mRect(reuse) {}

        Rect evaluate(float fraction, const Rect& startValue, const Rect& endValue) {
            int left = static_cast<int>(startValue.left +
                fraction * static_cast<float>(endValue.left - startValue.left));
            int top = static_cast<int>(startValue.top +
                fraction * static_cast<float>(endValue.top - startValue.top));
            int right = static_cast<int>(startValue.right +
                fraction * static_cast<float>(endValue.right - startValue.right));
            int bottom = static_cast<int>(startValue.bottom +
                fraction * static_cast<float>(endValue.bottom - startValue.bottom));

            if (mRect != nullptr) {
                mRect->left = left;
                mRect->top = top;
                mRect->right = right;
                mRect->bottom = bottom;
                return *mRect;
            } else {
                return {left, top, right, bottom};
            }
        }
    private:
        Rect* mRect;
    };
    ```
*   **Integer Truncation**: As with `IntEvaluator`, the explicit cast to `(int)` is a truncating operation that must be preserved in the C++ version using `static_cast<int>()` to ensure identical behavior.

## Implementation Risks
*   **Misuse of Reused Object**: In a C++ implementation that supports the reuse pattern, callers must be aware that the returned `Rect` is volatile and its contents will change on the next animation frame.
*   **Integer Overflow**: The subtractions (`endValue.left - startValue.left`) could theoretically overflow if one coordinate is `INT_MAX` and the other is `INT_MIN`. Casting to a wider type like `float` or `long long` before the multiplication, as shown in the example C++ translation, is a robust way to prevent this.

## Questions for C++ Team
*   What is the standard C++ representation for a `Rect` in our project?
*   Should the C++ implementation support the "reuse object" pattern, or should it always return a new `Rect` by value, relying on compiler optimizations (RVO)?
