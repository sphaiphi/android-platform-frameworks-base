# Display - Reverse Engineering Documentation

## Executive Summary
`Display` provides information about the size, density, and characteristics of a logical display. It distinguishes between the "Application Display Area" (window-constrained) and the "Real Display Area" (hardware-constrained). It interacts with the `DisplayManagerService` to track display state changes (on/off/doze).

## Architecture Overview
*   **Role**: Information provider for logical displays.
*   **Dependencies**: `DisplayManagerGlobal` (singleton client for DMS).
*   **Logical vs Physical**: A single `Display` object represents a logical display which may be mirrored across multiple physical devices.
*   **Key Data**: `DisplayInfo` (internal Parcelable containing all display metrics).

## Detailed Functionality

### 1. Metric Retrieval
*   **`getSize(Point)` / `getMetrics(DisplayMetrics)`**: (Deprecated) Returns size adjusted for system decorations and compatibility scaling.
*   **`getRealSize(Point)` / `getRealMetrics(DisplayMetrics)`**: Returns the true physical dimensions of the display.

### 2. Display State
*   **`getState()`**: Returns the current power state (ON, OFF, DOZE, VR).
*   **`isValid()`**: Checks if the display still exists in the system.

### 3. Capabilities
*   **`getFlags()`**: Indicates features like `FLAG_SECURE` (hardware protection), `FLAG_PRIVATE`, or `FLAG_ROUND`.
*   **`getRefreshRate()`**: Returns the active refresh rate in Hz.
*   **`getHdrCapabilities()`**: Information about HDR support (Dolby Vision, HDR10, etc.).

## Java-to-C++ Translation Guide
*   **IPC**: Proxies calls to `IDisplayManager`.
*   **Native Metrics**: In C++, use `DisplayInfo` and `DisplayViewport` structures.
*   **Enum Mapping**: Power states map directly to `android::view::DisplayState`.

## Implementation Risks
*   **Staleness**: Display properties can change (e.g., resolution switch or rotation). The `Display` object must be refreshed from `DisplayManagerGlobal`.
*   **Multi-Display**: Handling coordinate systems across multiple logical displays with different densities requires careful normalization.
