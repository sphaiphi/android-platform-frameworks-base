# Vr2dDisplayProperties - Reverse Engineering Documentation

## Executive Summary
`Vr2dDisplayProperties` is a data class used to specify the characteristics of a virtual display used for rendering 2D applications while the device is in Virtual Reality (VR) mode. It allows configuring the display's dimensions (width, height), resolution (DPI), and specific behavior flags (like enabling the virtual display).

## Architecture Overview
- **Structure**:
    - `mWidth`, `mHeight`: Physical resolution of the virtual display.
    - `mDpi`: Pixel density.
    - `mAddedFlags`: Bitmask of flags to enable.
    - `mRemovedFlags`: Bitmask of flags to disable.
- **Inheritance**: Implements `Parcelable`.
- **Builder Pattern**: Uses an internal `Builder` class for construction.

## Detailed Functionality

### Virtual Display Flags
**Purpose**: Controlling the VR 2D experience.
**Flags**:
- `FLAG_VIRTUAL_DISPLAY_ENABLED` (1): Toggles whether 2D apps should be rendered on a virtual surface in the VR environment.

### Builder Logic
**Mechanism**: The `Builder` allows setting dimensions and toggling flags. It translates negative values for width/height/DPI as "ignore" signals to the `VrManagerService`, indicating that those specific properties should remain unchanged.

## API Reference
- `public int getWidth()`: Returns display width.
- `public int getHeight()`: Returns display height.
- `public int getDpi()`: Returns pixel density.
- `public int getAddedFlags()`: Returns enabled features.

## Java-to-C++ Translation Guide
- **Simple Struct**: Map to a simple C++ `struct` or `class`.
- **Flag Manipulation**: Use bitwise `OR` and `AND NOT` for flag management.
- **Parceling**: Implement standard `writeToParcel` and `readFromParcel` using `libbinder`.

## Implementation Risks
- **Dimension Sanity**: The system server will likely enforce minimum/maximum bounds for these dimensions. C++ logic should be aware of these constraints.
- **DPI Scaling**: Changing the DPI of a virtual display affects how all 2D UI elements are scaled. Discrepancies between Java and C++ DPI handling can lead to layout issues.
