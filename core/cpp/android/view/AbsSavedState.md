# AbsSavedState - Reverse Engineering Documentation

## Executive Summary
`AbsSavedState` is a base class for `Parcelable` objects that are used to save and restore the state of a `View` or other components in a view hierarchy. It ensures that the state of all classes along the inheritance chain is preserved by maintaining a reference to the superclass state.

## Architecture Overview
*   **Role**: Base class for hierarchical state preservation.
*   **Inheritance**: Implements `Parcelable`.
*   **Chain of Responsibility**: Each subclass saves its own state and delegates the saving of its parent's state to `AbsSavedState`.

## Detailed Functionality

### State Management
*   **`mSuperState`**: A `Parcelable` reference to the state of the superclass.
*   **`getSuperState()`**: Returns the state of the superclass.
*   **`EMPTY_STATE`**: A singleton instance representing a state with no data, typically used at the root of the inheritance chain.

### Marshalling (Parcelable)
*   **`writeToParcel(Parcel, int)`**: Writes the superclass state to the parcel.
*   **`CREATOR`**: A `ClassLoaderCreator` that handles unmarshalling. It ensures that the `EMPTY_STATE` is correctly identified when reading from a parcel.

## Java-to-C++ Translation Guide
*   **Primary Type**: In C++, this can be implemented as a base class for state objects, holding a `std::unique_ptr` or `std::shared_ptr` to the parent state.
*   **Serialization**: Use `android::Parcel` for native marshalling, mirroring the Java implementation's order (saving the super state first).

## Implementation Risks
*   **Circular References**: If a state object accidentally references its own subclass state, it can lead to infinite recursion during serialization.
*   **Null Checks**: The `superState` must not be null unless it is the `EMPTY_STATE`.
