# BooleanPolicyValue - Reverse Engineering Documentation

## Executive Summary
`BooleanPolicyValue` is a final class that extends `PolicyValue<Boolean>`. Its primary purpose is to act as a `Parcelable` wrapper for a primitive `boolean` value, allowing boolean-based policies to be consistently handled within the device policy framework. This class enables boolean policy states to be serialized for IPC and persisted.

## Architecture Overview
`BooleanPolicyValue` is a concrete implementation of the generic `PolicyValue<T>` class, specialized for `Boolean`. It is a simple, immutable value object.

### Inheritance
- **`android.app.admin.PolicyValue<Boolean>`**: Base class that holds the wrapped value.
- **`android.os.Parcelable`**: Interface for marshaling and unmarshaling the object.

### Design Patterns
- **Value Object**: Represents a single, immutable boolean value.
- **Wrapper**: Wraps a primitive `boolean` in an object, providing it with object-oriented features like being parcelable.
- **Factory Method**: The `CREATOR` field is the standard Android pattern for deserializing the object from a `Parcel`.

## Detailed Functionality

### `BooleanPolicyValue(boolean value)`
**Purpose**: Constructs a new `BooleanPolicyValue` instance.
**Algorithm**: Calls the `super` constructor to store the provided `boolean` value.
**C++ Implementation Guidance**: A C++ constructor should take a `bool` and store it in a private member variable.

### `equals(@Nullable Object o)`
**Purpose**: Compares this `BooleanPolicyValue` to the specified object for equality.
**Algorithm**:
1. Checks for reference equality (`this == o`).
2. Checks if the other object is `null` or has a different class.
3. If the classes are the same, it compares the wrapped `boolean` values for equality.
**C++ Implementation Guidance**: Implement `operator==` to compare the wrapped boolean values of two `BooleanPolicyValue` objects.

### `hashCode()`
**Purpose**: Returns a hash code for the object.
**Algorithm**: Computes a hash code based on the wrapped `boolean` value using `Objects.hash()`.
**C++ Implementation Guidance**: Provide a `std::hash` specialization for `BooleanPolicyValue` that hashes the underlying `bool` value.

### `toString()`
**Purpose**: Returns a string representation of the object.
**Algorithm**: Returns a formatted string that includes the class name and the wrapped boolean value.
**C++ Implementation Guidance**: Overload `operator<<` for `std::ostream` to provide a human-readable representation of the object.

### `writeToParcel(@NonNull Parcel dest, int flags)`
**Purpose**: Flattens this object into a `Parcel`.
**Algorithm**: Writes the wrapped `boolean` value to the parcel using `dest.writeBoolean()`.
**Java-Specific Notes**: The `boolean` is written efficiently to the parcel.
**C++ Implementation Guidance**: If a `Parcel`-like system is used in C++, this would translate to writing a single byte or integer (`0` or `1`) to the serialization stream.

## Data Model
The class wraps a single primitive `boolean` value, which is stored in the `mValue` field of its superclass, `PolicyValue<Boolean>`.

- **`mValue`**: `private Boolean` (in the superclass)
  - **Type**: `java.lang.Boolean` (effectively a `boolean` due to autoboxing)
  - **Invariants**: None.
  - **Description**: The boolean state of the policy.

## API Reference
- **`public BooleanPolicyValue(boolean value)`**: Constructor.
- **`public boolean equals(@Nullable Object o)`**: Standard equality check.
- **`public int hashCode()`**: Standard hash code generation.
- **`public String toString()`**: String representation.
- **`public void writeToParcel(@NonNull Parcel dest, int flags)`**: Parcelable serialization.

## Java-to-C++ Translation Guide
- **`final class`**: In C++, mark the class as `final` to prevent further inheritance.
- **`extends PolicyValue<Boolean>`**: The C++ version should inherit from a template-specialized `PolicyValue<bool>`.
- **`boolean` vs. `bool`**: Java's `boolean` is equivalent to C++'s `bool`.
- **`Parcelable`**: A custom serialization mechanism will be needed in C++ if the object must be passed between processes.
- **`Objects.hash`**: Use a suitable C++ hashing function for the underlying `bool` value.

## Implementation Risks
- None. The class is simple and has no complex logic or dependencies.

## Questions for C++ Team
- Is there a standard C++ equivalent for `Parcelable` that should be used, or will a custom solution be required?
