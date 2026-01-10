
# TypeConverter - Reverse Engineering Documentation

## Executive Summary
`TypeConverter` is an abstract base class that provides a mechanism for converting values from one type to another. It is used by the property animation system when the type of value being animated (e.g., a `PointF` for path animations) is different from the type accepted by the property's setter method (e.g., a custom `MyPoint` object).

## Architecture Overview
*   **Abstract Base Class**: This class is `abstract` and defines the contract for a one-way type conversion.
*   **Generic Types**: It is a generic class, `TypeConverter<T, V>`, where `T` is the source type (the type of the animated values) and `V` is the target type (the type expected by the property's setter).
*   **Strategy Pattern**: It acts as a "strategy" object. A `PropertyValuesHolder` can be given a `TypeConverter` instance. On each animation frame, after the animated value (of type `T`) is calculated, the `PropertyValuesHolder` uses the converter to transform the value into type `V` before passing it to the target object's setter method.

## Detailed Functionality

### Constructor (`TypeConverter(Class<T> fromClass, Class<V> toClass)`)
*   **Purpose**: To initialize the converter with the source and target types.
*   **Behavior**: It stores the `Class` objects representing the "from" and "to" types. This type information is used internally by the animation framework, for example, to help find the correct setter method via reflection.

### `convert(T value)`
*   **Purpose**: This is the core abstract method that subclasses must implement. It contains the logic to perform the conversion.
*   **Input**: A value of the source type `T`.
*   **Output**: The corresponding value of the target type `V`.

### `getSourceType()` and `getTargetType()`
*   **Purpose**: These methods simply return the `Class` objects that were passed into the constructor, allowing the animation system to query the types involved in the conversion.

## Data Model
*   `mFromClass`: A `Class<T>` object representing the source type.
*   `mToClass`: A `Class<V>` object representing the target type.

## Java-to-C++ Translation Guide
*   **Abstract Templated Class**: This class translates directly to a C++ abstract base class using templates.

    ```cpp
    template<typename T, typename V>
    class TypeConverter {
    public:
        virtual ~TypeConverter() = default;

        // The core conversion method.
        virtual V convert(T value) = 0;

        // In C++, runtime type information is often handled differently.
        // The getSourceType()/getTargetType() methods might not be needed
        // if the system can rely on template metaprogramming or typeid.
        const std::type_info& getSourceType() const { return typeid(T); }
        const std::type_info& getTargetType() const { return typeid(V); }
    };
    ```
*   **Runtime Type Information**: The Java version stores `Class` objects to provide runtime type information. The C++ version can achieve this using `typeid`, as shown above, although in many template-based C++ designs, this explicit runtime query is unnecessary as the types are resolved at compile time.

## Implementation Risks
*   **Incorrect Conversion Logic**: The primary risk lies in the implementation of the `convert` method in a concrete subclass. If the conversion logic is flawed, it will result in incorrect values being applied to the animated property.
*   **Performance**: If the conversion is a computationally expensive operation, it will be performed on every frame of the animation. This could become a performance bottleneck. Converters should be designed to be as lightweight as possible.
*   **Bidirectional Need**: This class only supports one-way conversion. If an animation needs to read the starting value from a property, and that property's type needs conversion, a `BidirectionalTypeConverter` must be used instead. Using a one-way `TypeConverter` in such a scenario will lead to a runtime error.

## Questions for C++ Team
*   In the C++ animation framework, will runtime type information (equivalent to `getSourceType`/`getTargetType`) be required, or will the design rely solely on compile-time template types?
*   What is the C++ strategy for handling a failed conversion within the `convert` method? Should it throw an exception or return a default/error value?
