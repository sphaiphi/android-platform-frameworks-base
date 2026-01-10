# Gravity - Reverse Engineering Documentation

## Executive Summary
`Gravity` is a utility class providing constants and static methods for placing an object within a larger container. It handles calculations for alignment (Top, Bottom, Center) and relative layout directions (Start, End) based on the LTR (Left-to-Right) or RTL (Right-to-Left) configuration.

## Architecture Overview
*   **Role**: Geometric alignment calculator.
*   **Mechanism**: Uses bitmasks to represent different alignment axes (Horizontal and Vertical).

## Detailed Functionality

### 1. Alignment Constants
*   **Vertical**: `TOP`, `BOTTOM`, `CENTER_VERTICAL`.
*   **Horizontal**: `LEFT`, `RIGHT`, `CENTER_HORIZONTAL`, `START`, `END`.
*   **Combinations**: `CENTER`, `FILL`.

### 2. Core Logic
*   **`apply()`**: Calculates the final `Rect` for an object given its size, the container bounds, and the gravity flags.
*   **`getAbsoluteGravity()`**: Resolves relative directions (`START`, `END`) into absolute ones (`LEFT`, `RIGHT`) based on the layout direction.

### 3. Display Clipping
*   **`applyDisplay()`**: Adjusts a rectangle to ensure it fits within the visible bounds of a display, respecting clipping flags.

## Java-to-C++ Translation Guide
*   **Bitmasks**: C++ implementation should use identical bit values for the constants to ensure consistency with AIDL and system server logic.
*   **Geometry**: Directly uses `android::Rect`.

## Implementation Risks
*   **RTL Logic**: Incorrectly resolving `START`/`END` is a common source of UI bugs in multi-language environments.
*   **Overflow**: Clipping logic must handle cases where the object is larger than the container.
