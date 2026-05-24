# AppPredictionSessionId - Reverse Engineering Documentation

## Executive Summary
`AppPredictionSessionId` is a unique identifier for a prediction session. It consists of a string ID and a user ID, allowing the system to distinguish between multiple prediction sessions, potentially across different users.

## Architecture Overview
*   **Type**: Data Transfer Object (DTO) / Value Object.
*   **Interface**: Implements `android.os.Parcelable`.
*   **Role**: Used as a key in `AppPredictor` and the backing service to track session state.

## Detailed Functionality

### Identity
**Purpose**: Uniquely identify a session.
**Composition**:
*   `mId` (String): A unique string, typically `packageName + ":" + UUID`.
*   `mUserId` (int): The Android user ID (e.g., 0 for system/owner).

## Data Model

| Java Field | Type | C++ Equivalent | Description |
| :--- | :--- | :--- | :--- |
| `mId` | `String` | `std::string` / `android::String8` | Unique session string. |
| `mUserId` | `int` | `int32_t` | User ID. |

## API Reference

### Getters
*   `getUserId()`: Returns the integer user ID.
*   `toString()`: Returns `mId + "," + mUserId`.

### Equality
*   Checks both `mId` and `mUserId`.

## Java-to-C++ Translation Guide

### Data Structure
```cpp
struct AppPredictionSessionId : public android::Parcelable {
    std::string mId;
    int32_t mUserId;
    
    // Implement readFromParcel and writeToParcel
};
```

### Serialization
*   **Write**: `mId` (String), `mUserId` (Int).
*   **Read**: `mId` (String), `mUserId` (Int).

## Test Cases & Validation
*   **Unique Generation**: Verify that `AppPredictor` generates unique IDs (usually via UUID).
*   **Equality**: Objects with same ID string and User ID must be equal.

## Implementation Risks
*   None significant. Standard Parcelable.
