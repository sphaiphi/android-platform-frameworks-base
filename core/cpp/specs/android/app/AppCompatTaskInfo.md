# AppCompatTaskInfo - Reverse Engineering Documentation

## Executive Summary
`AppCompatTaskInfo` is a Parcelable class that transfers App Compatibility state information about a Task from system server to the client (or between system components). It specifically focuses on letterboxing (visual padding) and camera compatibility state.

## Architecture Overview
*   **Type**: Data Object / Parcelable.
*   **Usage**: Part of `TaskInfo`.

## Detailed Functionality

### Letterbox State
*   **Position**: `topActivityLetterboxVerticalPosition`, `topActivityLetterboxHorizontalPosition`.
*   **Dimensions**: `topActivityLetterboxWidth`, `topActivityLetterboxHeight`.
*   **Bounds**: `topActivityLetterboxBounds`.
*   **App Bounds**: `topActivityAppBounds`.

### Flags (`TopActivityFlag`)
*   Encodes boolean states into a bitmask `mTopActivityFlags`:
    *   Letterboxed status.
    *   Size compat mode status.
    *   Education enabled status.
    *   Double-tap enablement.
    *   Fullscreen overrides.

### Camera Compatibility
*   **Component**: `CameraCompatTaskInfo`.

### Equality Checks
*   `equalsForTaskOrganizer`: Checks equality of fields relevant to task organizers.
*   `equalsForCompatUi`: Checks equality of fields relevant to UI rendering (bounds, flags).

## Data Model
*   Simple struct-like class with public fields and helper methods for flags.

## Java-to-C++ Translation Guide
*   Map to a C++ `struct`.
*   Implement serialization/deserialization (Parcelable equivalent).
*   Bitmask manipulation helpers.

## Implementation Risks
*   **Sync**: Ensure fields match the system server's definition exactly to avoid serialization mismatches.
