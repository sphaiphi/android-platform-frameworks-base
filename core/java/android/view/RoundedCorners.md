# RoundedCorners - Reverse Engineering Documentation

## Executive Summary
`RoundedCorners` is a container class that manages the four potential rounded corners of a display. It handles the logic for loading these values from system resources and adjusting them based on display rotation, scaling, and window insets.

## Architecture Overview
*   **Role**: Multi-corner geometry manager.
*   **Data Structure**: An array of four `RoundedCorner` objects.
*   **Source**: Loads data based on system-wide configuration arrays (e.g., `config_roundedCornerRadiusArray`).

## Detailed Functionality

### 1. Coordinate Mapping
*   **`inset()`**: Adjusts the center points of all corners when the window is moved or resized (e.g., in split-screen mode).
*   **`rotate()`**: Re-calculates corner positions when the display orientation changes (e.g., the "Top Right" corner becomes the "Bottom Right" corner after a 90° clockwise rotation).

### 2. Resource Integration
*   **`fromResources()`**: The primary factory method. It calculates the physical pixel locations of corners based on the device's stable density and physical dimensions.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::RoundedCorners`.
*   **Parceling**: Bit-for-bit parity with `frameworks/native/libs/ui/` is required for Binder communication with WMS.

## Implementation Risks
*   **Caching**: Calculating corner positions involves complex display metrics; the class uses a static cache to prevent redundant calculations.
*   **Default Values**: For round devices (watches), the radius defaults to half the display width if not explicitly specified.
