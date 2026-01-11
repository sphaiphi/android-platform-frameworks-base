# WindowInfosListenerForTest - Reverse Engineering Documentation

## Executive Summary
`WindowInfosListenerForTest` is a Test API wrapper around `WindowInfosListener`. It provides a more convenient interface for unit tests to inspect the state of windows and displays on the screen, converting raw handles into a simplified `WindowInfo` DTO.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Test Utility)
*   **Role**: Testing shim.

## Data Model (WindowInfo DTO)
*   `windowToken`: IBinder.
*   `name`: String.
*   `displayId`: int.
*   `bounds`: Rect.
*   `isVisible`: boolean.
*   `isTouchable`: boolean.
*   `transform`: Matrix.

## Detailed Functionality

### Coordinate Transformation
**Algorithm**:
The raw window handles from `SurfaceFlinger` are in physical display coordinates. This utility:
1.  Finds the `DisplayInfo` for the window's display.
2.  Applies the `display.mTransform` to the window's `bounds` using `Matrix.mapRect`.
3.  Converts the bounds into logical display coordinates for easier assertion in tests.

### Registration
*   `addWindowInfosListener(BiConsumer)`: Registers an internal `WindowInfosListener` and handles the initial state dispatching via a `CountDownLatch` to ensure sequence consistency.

## Java-to-C++ Translation Guide
*   This is a test utility. C++ translation is only needed if implementing a C++ testing framework for the window manager.

## Implementation Risks
*   None.
