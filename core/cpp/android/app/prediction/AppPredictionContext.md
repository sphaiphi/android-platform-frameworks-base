# AppPredictionContext - Reverse Engineering Documentation

## Executive Summary
`AppPredictionContext` is a data class (Parcelable) that captures the environmental context in which app predictions are requested and used. It defines *where* the predictions will be shown (UI surface), *how many* are requested, and for *which package*.

## Architecture Overview
*   **Type**: Data Transfer Object (DTO) / Value Object.
*   **Interface**: Implements `android.os.Parcelable`.
*   **Pattern**: Builder Pattern used for construction.
*   **Role**: Passed to `AppPredictionManager` when creating a new prediction session.

## Detailed Functionality

### Data Holding
**Purpose**: Encapsulates context metadata.
**Attributes**:
1.  `mUiSurface` (String): Identifier for the UI area (e.g., "share_sheet", "launcher").
2.  `mPredictedTargetCount` (int): Hint for the number of targets requested.
3.  `mPackageName` (String): The package name of the app requesting predictions.
4.  `mExtras` (Bundle): Arbitrary additional data.

### Serialization (Parcelable)
**Purpose**: IPC transport.
**Algorithm**:
*   **Write**: Writes `mUiSurface`, `mPredictedTargetCount`, `mPackageName`, `mExtras` (Bundle) to Parcel.
*   **Read**: Reads in the same order.

## Data Model

| Java Field | Type | C++ Equivalent | Description |
| :--- | :--- | :--- | :--- |
| `mUiSurface` | `String` | `std::string` / `android::String8` | UI Surface ID. |
| `mPredictedTargetCount` | `int` | `int32_t` | Number of targets desired. |
| `mPackageName` | `String` | `std::string` / `android::String8` | Client package name. |
| `mExtras` | `Bundle` | `android::os::Bundle` | Optional extra parameters. |

## API Reference

### Getters
*   `getUiSurface()`: Returns UI surface string.
*   `getPredictedTargetCount()`: Returns target count.
*   `getPackageName()`: Returns package name.
*   `getExtras()`: Returns the Bundle extras.

### Builder
*   `setPredictedTargetCount(int)`: Sets count.
*   `setUiSurface(String)`: Sets surface.
*   `setExtras(Bundle)`: Sets extras.
*   `build()`: Creates `AppPredictionContext`.

## Java-to-C++ Translation Guide

### Data Structure
```cpp
struct AppPredictionContext : public android::Parcelable {
    std::string mUiSurface;
    int32_t mPredictedTargetCount;
    std::string mPackageName;
    android::os::Bundle mExtras;

    // Implement readFromParcel and writeToParcel
};
```

### Serialization
Match Java's order: String, Int, String, Bundle.

## Test Cases & Validation
*   **Equality**: Two contexts with same surface, count, and package name must be equal. Note: `equals()` does *not* check `mExtras`.
*   **Parceling**: Write to parcel, read back, verify fields match.

## Implementation Risks
*   **Extras Equality**: The Java `equals` method ignores `mExtras`. C++ implementation should replicate this behavior if it's used for comparison logic (e.g., caching).
*   **Nullability**: `mUiSurface` and `mPackageName` are `@NonNull`. `mExtras` is `@Nullable`.
