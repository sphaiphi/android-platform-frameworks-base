# DisplayViewport - Reverse Engineering Documentation

## Executive Summary
`DisplayViewport` describes the mapping between a physical display device and a logical display. It is critical for the Input System to translate raw touch coordinates (physical) into logical window coordinates.

## Architecture Overview
- **Type**: Mutable Data Object.
- **Scope**: Internal (System Server).

## Data Model
- `valid` (bool)
- `isActive` (bool)
- `displayId` (int)
- `orientation` (int: 0, 90, 180, 270)
- `logicalFrame` (Rect): The area in logical coordinates.
- `physicalFrame` (Rect): The area on the physical panel.
- `deviceWidth` / `deviceHeight`: Physical dimensions.
- `type`: Internal, External, Virtual.

## Java-to-C++ Translation Guide
- **Identity**: Matches `DisplayViewport.h` in the native InputReader configuration (likely `frameworks/native/libs/input`).
- **Usage**: Used to configure `InputManagerService` (native).
- **Copying**: `copyFrom` / `makeCopy` methods.
