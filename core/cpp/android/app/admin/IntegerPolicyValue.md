# IntegerPolicyValue - Reverse Engineering Documentation

## 1. Executive Summary
`IntegerPolicyValue` is a final class that extends `PolicyValue<Integer>`. It serves as a `Parcelable` wrapper for a primitive `int` value, enabling integer-based policies to be handled consistently within the Android device policy framework. This allows integer policy states to be serialized for IPC and persisted.

## 2. Architecture Overview
This class is a concrete implementation of the generic `PolicyValue<T>` class, specialized for `Integer`. It is a simple, immutable value object, analogous to `BooleanPolicyValue` and `StringPolicyValue`.

### Inheritance
- **`android.app.admin.PolicyValue<Integer>`**: Base class that holds the wrapped `Integer` value.
- **`android.os.Parcelable`**: Interface enabling the object to be passed across processes.

### Design Patterns
- **Value Object**: Represents a single, immutable integer value.
- **Wrapper**: Encapsulates a primitive `int` in a `Parcelable` object.
- **Factory Method**: The `CREATOR` field implements the standard Android pattern for deserializing from a `Parcel`.

## 3. Detailed Functionality

### `IntegerPolicyValue(int value)`
- **Purpose**: Constructs a new `IntegerPolicyValue`.
- **Algorithm**: Calls the `super` constructor to store the provided `int` value. Java's autoboxing converts the `int` to an `Integer` object for the generic superclass.
- **C++ Implementation Guidance**: A C++ constructor should take an `int` (or a specific-width integer like `int32_t`) and store it as a private member.

### `equals(@Nullable Object o)`
- **Purpose**: Compares this `IntegerPolicyValue` to another object for equality.
- **Algorithm**: After standard reference and type checks, it compares the wrapped integer values.
- **C++ Implementation Guidance**: Implement `operator==` to compare the underlying integer members.

### `hashCode()`
- **Purpose**: Returns a hash code for the object.
- **Algorithm**: Delegates to `Objects.hash()` on the wrapped `Integer` value.
- **C++ Implementation Guidance**: Provide a `std::hash` specialization that simply hashes the underlying integer member.

### `writeToParcel(@NonNull Parcel dest, int flags)`
- **Purpose**: Serializes the object to a `Parcel`.
- **Algorithm**: Writes the wrapped integer value to the parcel using `dest.writeInt()`.
- **C++ Implementation Guidance**: In a C++ serialization framework, this would correspond to writing a 32-bit integer to the byte stream.

## 4. Data Model
The class wraps a single primitive `int` value, which is stored as an `Integer` object in the `mValue` field of its superclass, `PolicyValue<Integer>`.

- **`mValue`**: `private Integer` (in superclass)
  - **Type**: `java.lang.Integer`
  - **Description**: The integer state of the policy.

## 5. API Reference
- **`public IntegerPolicyValue(int value)`**: Constructor.
- **`public boolean equals(@Nullable Object o)`**: Equality check.
- **`public int hashCode()`**: Hash code generation.
- **`public String toString()`**: String representation.
- **`public void writeToParcel(@NonNull Parcel dest, int flags)`**: Parcelable serialization.

## 6. Java-to-C++ Translation Guide
- **`final class`**: The C++ class can be marked `final`.
- **`extends PolicyValue<Integer>`**: The C++ class should inherit from `PolicyValue<int32_t>` or a similar template specialization.
- **`int` vs. `int32_t`**: Java's `int` is a 32-bit signed integer. For cross-language compatibility, the C++ implementation should use a fixed-width type like `int32_t` from `<cstdint>`.
- **`Parcelable`**: A custom C++ serialization mechanism is required for IPC.

## 7. Implementation Risks
- None. This is a very simple and straightforward value class with no external dependencies or complex logic.

## 8. Questions for C++ Team
- Is there a standard C++ equivalent for `Parcelable` that should be used, or will a custom solution be required?
- Should fixed-width integer types (`int32_t`, `int64_t`, etc.) be used in the C++ equivalent for all integer-based policies to ensure no ambiguity in size?
