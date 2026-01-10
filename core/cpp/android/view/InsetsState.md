# InsetsState - Reverse Engineering Documentation

## Executive Summary
`InsetsState` is the definitive data structure representing the set of all window insets in the system. It contains a collection of `InsetsSource` objects, the display dimensions, and metadata about display cutouts and rounded corners. It is the "source of truth" used to calculate `WindowInsets` for applications.

## Data Model

### 1. Sources
*   **`mSources`**: A `SparseArray` mapping source IDs to `InsetsSource` objects.

### 2. Display Context
*   **`mDisplayFrame`**: The total area of the display.
*   **`mDisplayCutout`**: Physical notch and hole-punch data.
*   **`mRoundedCorners`**: Precise corner radii.
*   **`mDisplayShape`**: The physical outer boundary of the screen.

## Detailed Functionality

### 1. Inset Calculation
*   **`calculateInsets()`**: The primary algorithm for converting raw source frames into a `WindowInsets` object. It handles legacy flag compatibility, cutout avoidance, and visibility rules.

### 2. State Comparison
*   **`traverse()`**: A high-performance utility for iterating through two states and identifying added, removed, or modified sources without triggering binary searches.

### 3. Scaling
*   **`scale()`**: Adjusts all frames and metrics based on a scaling factor (used for high-density or compatibility modes).

## Java-to-C++ Translation Guide
*   **Primary Type**: Map to `android::InsetsState`.
*   **Structure**: Uses a `SparseArray`, which can be implemented in C++ using a sorted `std::vector` or a `std::map`.
*   **Parceling**: Bit-level parity with `frameworks/native/libs/gui/InsetsState.cpp` is required.

## Implementation Risks
*   **Legacy Flags**: Correctly replicating the behavior of `FLAG_FULLSCREEN` and `SOFT_INPUT_ADJUST_RESIZE` is necessary for backward compatibility.
*   **Performance**: Since this is used during every layout pass, the `calculateInsets` and `traverse` methods must be extremely efficient.
