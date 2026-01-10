# ResolutionMechanism - Reverse Engineering Documentation

## 1. Executive Summary
`ResolutionMechanism` is an abstract, generic class that serves as the base for identifying different strategies used to resolve conflicts when a device policy is set by multiple administrators. Its primary purpose is to describe *how* the final, enforced policy value (`V`) is determined from potentially conflicting inputs. Concrete subclasses (e.g., `MostRestrictive`, `FlagUnion`, `MostRecent`) implement specific resolution rules. This class is an essential part of the modern device policy engine, providing transparency into conflict resolution.

## 2. Architecture Overview
`ResolutionMechanism` is the root of an inheritance hierarchy for policy conflict resolution strategies. Because it's generic (`<V>`), it can describe mechanisms for various types of policy values. It is also `Parcelable`, allowing its subclasses to be efficiently transferred via IPC.

### Inheritance
- **`java.lang.Object`**: The root of the class hierarchy.
- **`android.os.Parcelable`**: All concrete subclasses must implement the `Parcelable` interface for serialization. The `ResolutionMechanism` class itself is marked with `@SuppressLint({"ParcelNotFinal", "ParcelCreator"})` because it's abstract and doesn't directly implement all `Parcelable` methods or have a `CREATOR`.

### Design Patterns
- **Abstract Base Class**: Defines a common interface and a basic mechanism for representing policy resolution strategies. It cannot be instantiated directly.
- **Generic Programming**: Uses Java generics (`<V>`) to enable type-safe handling of different types of policy values.
- **Strategy (as a Descriptor)**: The class and its subclasses act as descriptive markers for resolution strategies; the actual logic for applying the strategy resides within the policy engine that consumes these objects.

## 3. Detailed Functionality

### `ResolutionMechanism()`
- **Purpose**: A package-private default constructor.
- **Algorithm**: Empty, as it's an abstract class.

### `Parcelable` Implementation (Abstract)
- `ResolutionMechanism` declares that it implements `Parcelable`, meaning all concrete subclasses must provide implementations for `describeContents()` and `writeToParcel()`, as well as a `CREATOR` field.

## 4. Data Model
`ResolutionMechanism` is an abstract class and has no direct instance-specific data members. Its state and behavior are defined by its concrete subclasses.

## 5. Java-to-C++ Translation Guide
- **Generics (`<V>`)**: Translates directly to a C++ template class (`template<typename V>`).
  ```cpp
  template<typename V>
  class ResolutionMechanism {
  public:
      // Pure virtual methods for Parcelable equivalent
      virtual int describeContents() const = 0;
      virtual void writeToParcel(Parcel& dest, int flags) const = 0;
      // Virtual destructor
      virtual ~ResolutionMechanism() = default;

  protected:
      ResolutionMechanism() = default;
  };
  ```
- **Abstract Base Class**: Translates to a C++ abstract base class with a pure virtual destructor (to ensure proper cleanup of derived classes) and pure virtual methods for the `Parcelable` equivalent.
- **`Parcelable` equivalent**: C++ does not have a direct equivalent. A custom serialization/deserialization interface would need to be defined, with a virtual factory method (or external factory) for `createFromParcel` that reads a type token and instantiates the correct subclass.

## 6. Implementation Risks & Key Considerations
- **Polymorphic Serialization**: The biggest challenge is ensuring that `ResolutionMechanism` subclasses can be correctly serialized and deserialized polymorphically. This requires a mechanism (e.g., type tokens) during serialization/deserialization to identify the concrete subclass.
- **Generic Type `V`**: How `V` is handled in C++ (e.g., raw types, `std::variant`, `std::any`) will influence the design of both `ResolutionMechanism` and its subclasses.

## 7. Questions for C++ Team
1.  What is the standard approach in this C++ project for defining an abstract base class that has polymorphic derived types, and how are these derived types serialized/deserialized for IPC?
2.  How will the generic type `V` be managed across the `ResolutionMechanism` hierarchy in C++?
3.  Is there an existing framework for IPC serialization of polymorphic objects, or will a custom solution need to be developed?
