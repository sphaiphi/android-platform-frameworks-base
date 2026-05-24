# AppTargetId - Reverse Engineering Documentation

## Executive Summary
`AppTargetId` is a simple wrapper around a string identifier for a specific app target. It provides type safety and a Parcelable container for target IDs.

## Architecture Overview
*   **Type**: Wrapper / Value Object.
*   **Interface**: Implements `android.os.Parcelable`.

## Detailed Functionality

### Identity
**Purpose**: Encapsulate a target ID string.
**Attributes**:
*   `mId` (String): The identifier.

## Data Model

| Java Field | Type | C++ Equivalent | Description |
| :--- | :--- | :--- | :--- |
| `mId` | `String` | `std::string` | The target ID. |

## API Reference

### Methods
*   `getId()`: Returns the ID string.
*   `equals(Object)`: Comparison based on string ID.

## Java-to-C++ Translation Guide

### Data Structure
```cpp
struct AppTargetId : public android::Parcelable {
    std::string mId;
    
    // Parcelable implementation
};
```

### Serialization
*   **Write**: `writeString(mId)`.
*   **Read**: `readString()`.

## Test Cases & Validation
*   **Equality**: Two objects with same ID string are equal.
*   **Nullability**: `mId` is `@NonNull`.

## Implementation Risks
*   None.
