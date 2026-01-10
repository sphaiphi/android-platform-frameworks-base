# SelectionsRequest - Reverse Engineering Documentation

## Executive Summary
`SelectionsRequest` encapsulates the parameters required to request content selections from the Content Suggestions service. It specifies the context (via Task ID) and optionally a point of interest on the screen to prioritize.

## Architecture Overview
This is a **Data Transfer Object (DTO)** implementing `Parcelable`. It uses the **Builder pattern** for construction. It is immutable.

## Detailed Functionality

### `SelectionsRequest`
**Purpose**: Request parameters for `suggestContentSelections`.
**Components**:
1.  `mTaskId`: The ID of the Activity/Task to analyze.
2.  `mInterestPoint`: An optional `android.graphics.Point` indicating where the user is focusing/touching.
3.  `mExtras`: A `Bundle` for additional implementation-specific data.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mTaskId` | `int` | The task ID. |
| `mInterestPoint` | `Point` | Optional X,Y coordinate. |
| `mExtras` | `Bundle` | Optional extras. |

## API Reference

### Public Methods
*   `getTaskId()`: Returns int.
*   `getInterestPoint()`: Returns `Point` (nullable).
*   `getExtras()`: Returns `Bundle` (non-null).
*   `writeToParcel(...)`: Serializes to Parcel.

### Builder
*   `Builder(int taskId)`: Constructor.
*   `setInterestPoint(Point)`: Sets the interest point.
*   `setExtras(Bundle)`: Sets the extras.
*   `build()`: Creates the request.

## Java-to-C++ Translation Guide

### Serialization
*   **`writeToParcel`**:
    *   `mTaskId`: `Parcel::writeInt`.
    *   `mInterestPoint`: `Parcel::writeTypedObject`. Note: `Point` is a Parcelable. In C++, this might be `android::ui::Point` or similar, or written manually as two integers if a direct Parcelable mapping doesn't exist in the NDK/Framework C++ layer. **Check `android.graphics.Point` C++ equivalent.**
    *   `mExtras`: `Parcel::writeBundle`.

### Types
*   `int` -> `int32_t`.
*   `android.graphics.Point` -> `android::graphics::Point` (if available) or struct `{int x; int y;}`.
*   `Bundle` -> `android::os::Bundle`.

## Test Cases & Validation
1.  **Serialization**: Verify `taskId`, `interestPoint`, and `extras` are correctly serialized.
2.  **Nullable Point**: Verify behavior when `mInterestPoint` is null vs non-null.

## Implementation Risks
*   **Point Parceling**: Ensure the C++ serialization of `Point` matches the Java side exactly (likely just two ints, X then Y).
