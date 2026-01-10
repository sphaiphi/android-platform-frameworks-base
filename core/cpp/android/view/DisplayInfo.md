# DisplayInfo - Reverse Engineering Documentation

## Executive Summary
`DisplayInfo` is an internal data class that contains all the static and dynamic characteristics of a logical display. It is the primary data structure passed between the `DisplayManagerService` and the `DisplayManagerGlobal` client to represent the state of a display.

## Data Model

### 1. Physical Characteristics
*   **`logicalWidth` / `logicalHeight`**: The usable resolution of the display (may be emulated).
*   **`appWidth` / `appHeight`**: Resolution available to apps after subtracting system decorations.
*   **`physicalXDpi` / `physicalYDpi`**: Exact physical pixels per inch.
*   **`logicalDensityDpi`**: The density bucket (e.g., 480 for xxhdpi).

### 2. State & Policy
*   **`state`**: Current power state (`ON`, `OFF`, `DOZE`).
*   **`rotation`**: Current orientation relative to natural.
*   **`flags`**: Capability bitmask (`FLAG_SECURE`, `FLAG_PRIVATE`, etc.).

### 3. Display Features
*   **`displayCutout`**: Info about notches and holes.
*   **`hdrCapabilities`**: Supported HDR types and luminance data.
*   **`supportedModes`**: List of valid resolution/refresh rate combinations.

## Detailed Functionality
*   **`calculateInsets()`**: Helper to determine window insets based on display state and decorations.
*   **`getAppMetrics()`**: populates a `DisplayMetrics` object for application use.

## Java-to-C++ Translation Guide
*   **Mapping**: Map to a C++ `struct` or `class` named `DisplayInfo`.
*   **Parceling**: Serialization MUST be identical to the native `DisplayInfo` in `frameworks/native/libs/ui/`.

## Implementation Risks
*   **Field Sync**: Since this is a massive structure with many primitive fields, ensure the unmarshalling logic precisely matches the marshalling order to prevent data corruption.
*   **Indeterminate States**: Some fields (like `rotation`) may be indeterminate if a logical display spans multiple physical screens.
