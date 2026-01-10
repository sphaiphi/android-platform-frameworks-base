# WindowInsets - Reverse Engineering Documentation

## Executive Summary
`WindowInsets` is a comprehensive descriptor of the areas of a window that are partially or fully obscured by system UI elements (Status Bar, Navigation Bar, IME, Display Cutouts). it provides applications with the information needed to perform "Edge-to-Edge" layout while avoiding critical overlaps.

## Data Model

### 1. Inset Types (`Type`)
*   `statusBars()`, `navigationBars()`, `ime()`, `systemGestures()`, `displayCutout()`.

### 2. Geometric Data
*   **`getInsets(int types)`**: Returns the physical pixel insets for the requested types.
*   **`getInsetsIgnoringVisibility(int types)`**: Returns the "maximum" possible insets for a type (even if currently hidden).
*   **`getBoundingRects(int types)`**: Provides detailed sub-regions for complex system bars.

## Detailed Functionality

### 1. Consumption
*   **`isConsumed()`**: Checks if all insets have been handled by the application.
*   **`CONSUMED`**: A singleton representing a fully-handled state.

### 2. Coordinate Math
*   **`inset(Insets)`**: Returns a new `WindowInsets` object adjusted for a smaller child frame.

### 3. State Invariants
*   `WindowInsets` is immutable starting with Android P.

## Java-to-C++ Translation Guide
*   **Structure**: In C++, this can be a `class` wrapping a pointer to a native `android::InsetsState`.
*   **Math**: Relies heavily on `Insets` (L, T, R, B) arithmetic.

## Implementation Risks
*   **Type Mapping**: The bitmasks for `InsetsType` must be consistent across the entire system.
*   **IME Dynamic Height**: IME insets are special because they depend on the specific editor's configuration; ensure C++ logic handles this dynamism.
