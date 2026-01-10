
# KeyframeSet - Reverse Engineering Documentation

## Executive Summary
`KeyframeSet` is the primary, general-purpose implementation of the `Keyframes` interface. It holds a list of `Keyframe` objects and provides the logic to calculate an interpolated value for any given fraction of an animation's duration. It is an internal (`@hide`) class that forms the backbone of `ValueAnimator`.

## Architecture Overview
*   **Implementation of `Keyframes`**: This class provides the concrete logic for the `Keyframes` interface.
*   **Collection of Keyframes**: Its main purpose is to manage a `List<Keyframe>` objects.
*   **Optimized Evaluation**: The `getValue(float fraction)` method is optimized for the common cases. It has fast paths for fractions at the very beginning (`<= 0f`) and end (`>= 1f`) of the animation. For the main part of the animation, it does a linear scan to find the correct keyframe interval.
*   **Factory Methods**: It provides static factory methods (`ofInt`, `ofFloat`, `ofObject`, `ofKeyframe`) that simplify its creation and can return more optimized, type-specific subclasses (`IntKeyframeSet`, `FloatKeyframeSet`) when possible.

## Detailed Functionality

### Factory Methods (`ofInt`, `ofFloat`, etc.)
*   **Purpose**: These methods provide a convenient way to create a `KeyframeSet` from a simple array of values.
*   **`ofInt(int... values)` / `ofFloat(float... values)`**: These take an array of primitive values and automatically create the necessary `Keyframe` objects, distributing them evenly in time (fractions from 0.0 to 1.0). For example, `ofInt(10, 20, 30)` creates three keyframes at fractions 0.0, 0.5, and 1.0 with those values. They then return an instance of the optimized `IntKeyframeSet` or `FloatKeyframeSet`.
*   **`ofKeyframe(Keyframe... keyframes)`**: This is a smart factory. It inspects the provided keyframes. If they are all of a single primitive type (`IntKeyframe` or `FloatKeyframe`), it creates and returns the corresponding optimized subclass (`IntKeyframeSet` or `FloatKeyframeSet`). If the types are mixed or are generic `ObjectKeyframe`s, it returns a standard `KeyframeSet`.
*   **`ofPath(Path path)`**: This is a factory for a different implementation (`PathKeyframes`) which is also hidden behind the `Keyframes` interface.

### `getValue(float fraction)`
*   **Purpose**: This is the core evaluation logic for generic (`Object`) keyframes.
*   **Algorithm**:
    1.  **Special Case (2 keyframes)**: If there are only two keyframes, it's a simple start/end animation. It applies the interpolator and calls the `TypeEvaluator` once. This is a significant optimization for the most common type of animation.
    2.  **Edge Case (`fraction <= 0`)**: It calculates the value based on the first two keyframes.
    3.  **Edge Case (`fraction >= 1`)**: It calculates the value based on the last two keyframes.
    4.  **Main Case (`0 < fraction < 1`)**: It iterates through the keyframe list to find the first keyframe whose fraction is greater than the input `fraction`. This identifies the interval `(i-1, i)` that contains the current time.
    5.  It then calculates the `intervalFraction`—how far along the animation is within just that interval.
    6.  It applies the `TimeInterpolator` (if any) from the *ending* keyframe of the interval (`nextKeyframe`) to the `intervalFraction`.
    7.  Finally, it calls the `TypeEvaluator` with the `intervalFraction` and the start and end values from the surrounding keyframes (`prevKeyframe`, `nextKeyframe`) to get the final interpolated value.

### `setEvaluator(TypeEvaluator evaluator)`
*   Stores the `TypeEvaluator` to be used for interpolation. This is mandatory for `KeyframeSet`s that hold non-primitive types.

### `clone()`
*   Creates a deep copy of the `KeyframeSet` by cloning each individual `Keyframe` in its list.

## Data Model
*   `mNumKeyframes`: An `int` caching the number of keyframes.
*   `mKeyframes`: A `List<Keyframe>` holding the keyframe objects.
*   `mFirstKeyframe`, `mLastKeyframe`: Cached references to the first and last keyframes for quick access.
*   `mInterpolator`: A cached reference to the interpolator of the *last* keyframe, used only in the fast-path case with two keyframes.
*   `mEvaluator`: The `TypeEvaluator` used to interpolate between object values.

## Java-to-C++ Translation Guide
*   **Template Class**: This class is a prime candidate for a C++ template: `template <typename T> class KeyframeSet : public Keyframes`. This allows the C++ implementation to be type-safe and avoid the `Object` casting seen in the generic Java `KeyframeSet`.
*   **Evaluation Logic**: The algorithm within `getValue` can be translated directly to a C++ `getValue(float fraction)` method. The logic for the special cases and the linear scan would remain the same.
*   **Storage**: The `mKeyframes` list would become a `std::vector<Keyframe<T>>`.
*   **Factory Functions**: The `of...` static factory methods would become C++ free functions, possibly templated as well, that return a `std::unique_ptr<Keyframes>`. The `ofKeyframe` function's logic to detect the type and return a specialized version would be implemented using C++ type-checking mechanisms.

## Implementation Risks
*   **Performance**: The linear scan through keyframes in `getValue` has a performance cost that scales with the number of keyframes. While acceptable for most UI animations (which typically have few keyframes), it could become a bottleneck for very complex animations. The Java implementation mitigates this with type-specific subclasses; a C++ version should do the same via template specialization.
*   **Algorithm Fidelity**: The exact details of the `getValue` algorithm, including how `intervalFraction` is calculated and when the interpolator is applied, must be replicated precisely to ensure the C++ animations have the same timing and feel as the Java originals.

## Questions for C++ Team
*   Will the C++ implementation use a templated `KeyframeSet<T>`, or will it use a non-template base class with `std::any` for values to more closely match the Java `Object`-based version?
*   For the linear scan in `getValue`, is a `std::vector` lookup considered performant enough, or should a different data structure (like a map or a structure that permits binary search) be considered for animations with a very high number of keyframes?
