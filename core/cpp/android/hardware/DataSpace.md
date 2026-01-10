# DataSpace - Reverse Engineering Documentation

## Executive Summary
`DataSpace` is a utility class that defines how buffer data (like images or hardware buffers) should be interpreted in terms of color. It encapsulates three distinct aspects: color primaries (standard), transfer function (gamma), and coordinate range. It uses a packed integer representation.

## Architecture Overview
The class defines a set of constants and bitmasks used to construct and deconstruct a "dataspace" value. This value is used throughout the graphics and camera stacks (e.g., `SurfaceControl`, `HardwareBuffer`, `Image`).

## Detailed Functionality

### Packed Representation
A 32-bit integer encodes three components:
- **Standard (Bits 16-21)**: Defines chromaticity (e.g., BT.709, BT.2020).
- **Transfer (Bits 22-26)**: Defines the transfer characteristic curve (e.g., sRGB, Linear, HLG).
- **Range (Bits 27-29)**: Defines the range of values (e.g., Full, Limited, Extended).

### Helper Methods
- `pack(standard, transfer, range)`: Combines the components into a single integer.
- `getStandard(dataSpace)`, `getTransfer(dataSpace)`, `getRange(dataSpace)`: Extract components using bitmasks.

## Data Model

### Standards (Partial List)
- `STANDARD_UNSPECIFIED` (0)
- `STANDARD_BT709` (1 << 16)
- `STANDARD_BT2020` (6 << 16)
- `STANDARD_DCI_P3` (10 << 16)

### Transfers (Partial List)
- `TRANSFER_UNSPECIFIED` (0)
- `TRANSFER_LINEAR` (1 << 22)
- `TRANSFER_SRGB` (2 << 22)
- `TRANSFER_ST2084` (7 << 22) (PQ)
- `TRANSFER_HLG` (8 << 22)

### Ranges
- `RANGE_UNSPECIFIED` (0)
- `RANGE_FULL` (1 << 27)
- `RANGE_LIMITED` (2 << 27)
- `RANGE_EXTENDED` (3 << 27)

### Named DataSpaces
Pre-packed combinations like `DATASPACE_SRGB`, `DATASPACE_DISPLAY_P3`, `DATASPACE_BT2020_HLG`.

## Java-to-C++ Translation Guide
- **Constants**: Mirror the exact bit-shifts and values. In C++, these are often found in `system/graphics-base.h` or similar headers as `android_dataspace_t`.
- **Enums**: Use `enum class` for type safety while allowing bitwise operations if necessary.

## Implementation Risks
- Desynchronization with the native `android_dataspace_t` enumeration.
- Misinterpretation of "Extended" range which varies by pixel format (FP16 vs integer).
