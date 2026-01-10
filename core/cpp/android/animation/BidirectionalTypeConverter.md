
# BidirectionalTypeConverter - Reverse Engineering Documentation

## Executive Summary
`BidirectionalTypeConverter` is an abstract class that extends `TypeConverter`. It adds the capability to convert not only from a source type `T` to a target type `V`, but also back from `V` to `T`. This is essential for animations where the starting value of a property needs to be read from the target object before the animation begins.

## Architecture Overview
*   **Extension of `TypeConverter`**: It inherits the basic one-way `convert(T value)` method and the source/target type information from its parent, `TypeConverter`.
*   **Abstract Bidirectional Method**: It adds a new abstract method, `convertBack(V value)`, which concrete subclasses must implement to provide the reverse conversion.
*   **Inversion Factory**: It includes a public `invert()` method that acts as a factory. It creates and returns a new `BidirectionalTypeConverter` that is the exact inverse of the current one, swapping the source and target types and delegating the conversion calls appropriately. This avoids the need for developers to manually write an inverse converter.

## Detailed Functionality

### `convertBack(V value)`
*   **Purpose**: This is the core abstract method of the class. A subclass must implement this to define the logic for converting from the "animated" type `V` back to the property's original type `T`.
*   **Usage**: This is used by `ObjectAnimator` at the beginning of an animation if only an end value is supplied. To calculate the start value, the animator must:
    1.  Read the current value of the property from the target object (this value has type `T`).
    2.  This is not correct. It reads the current value (type `V`) and needs to convert it back to `T` to be used as a start value if the keyframes are of type `T`.
    *Correction*: `ObjectAnimator` uses this when the property's type (`V`) is different from the animation's value type (`T`). For example, animating a `Path` (type `T`) but applying it to a custom view property that takes a different object (`V`). If the start value is not provided, `ObjectAnimator` reads the current property value (type `V`), uses `convertBack` to turn it into the animation's value type (`T`), and sets that as the starting keyframe.

### `invert()`
*   **Purpose**: To provide a convenient way to get a converter that performs the reverse operation without writing a new class.
*   **Algorithm**:
    1.  It lazily creates and caches an instance of a private inner class, `InvertedConverter`.
    2.  The `InvertedConverter`'s constructor takes the original converter (`this`) as a reference.
    3.  The `InvertedConverter`'s `convert(V value)` method simply calls `mConverter.convertBack(value)`.
    4.  The `InvertedConverter`'s `convertBack(T value)` method simply calls `mConverter.convert(value)`.
*   This is a clean implementation of the wrapper/delegation pattern.

## Data Model
*   `mInvertedConverter`: A private field that caches the lazily-created inverse converter to avoid object churn.
*   The class inherits `mFromClass` and `mToClass` from `TypeConverter`.

## Java-to-C++ Translation Guide
*   **Abstract Base Classes**: This would be translated into a hierarchy of C++ abstract base classes.

    ```cpp
    // Base TypeConverter
    template<typename T, typename V>
    class TypeConverter {
    public:
        virtual ~TypeConverter() = default;
        virtual V convert(T value) = 0;
        // ... other methods to get source/target types
    };

    // Bidirectional TypeConverter
    template<typename T, typename V>
    class BidirectionalTypeConverter : public TypeConverter<T, V> {
    public:
        virtual T convertBack(V value) = 0;

        // The invert() method would be more complex to implement with C++ templates
        // but could be done with a similar private inner class.
        std::unique_ptr<BidirectionalTypeConverter<V, T>> invert();
    };
    ```
*   **Generics vs. Templates**: Java's generics (`<T, V>`) map directly to C++ templates (`template<typename T, typename V>`).
*   **Inversion**: The `InvertedConverter` inner class can be replicated in C++ as a private templated inner class that holds a pointer or reference to its parent converter and delegates the calls in reverse. Managing the lifetime of the inverted converter (e.g., with `std::unique_ptr`) would be important.

## Implementation Risks
*   **Logical Inconsistency**: The main risk lies with the implementer of a concrete subclass. If `convert(convertBack(v))` does not result in a value equal to `v` (within a reasonable tolerance for floating-point types), then animations that read their start value may behave unexpectedly or "jump" at the beginning. The forward and backward conversions must be logically consistent inverses of each other.
*   **Ownership and Lifetime (C++)**: In a C++ implementation, the ownership of the `InvertedConverter` must be handled correctly. Returning a `std::unique_ptr` would be a safe way to transfer ownership to the caller. Caching the inverted converter would require careful management to avoid memory leaks or dangling pointers.

## Questions for C++ Team
*   What is the C++ strategy for representing types at runtime, equivalent to Java's `Class<T>` objects, which are used in the constructor? (e.g., `typeid`, or will this not be needed in the C++ version?)
*   How will ownership of the inverted converter returned by `invert()` be managed?
