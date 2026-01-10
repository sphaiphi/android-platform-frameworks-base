# VirtualTouchDeviceConfig - Reverse Engineering Documentation

## Executive Summary
`VirtualTouchDeviceConfig` is an intermediate abstract class for devices that map to screen coordinates (Touchscreen, Stylus).

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDeviceConfig`.

## Detailed Functionality
- **Fields**: `mWidth`, `mHeight` (screen size).
- **Validation**: Dimensions must be positive.

## Java-to-C++ Translation Guide
- Struct with width/height.
