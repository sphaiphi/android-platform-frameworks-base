# HdmiUtils - Reverse Engineering Documentation

## Executive Summary
`HdmiUtils` contains static utility methods for HDMI-CEC address parsing and validation.

## Architecture Overview
- **Type**: Utility Class (static methods).

## Detailed Functionality

### Address Logic
- `getLocalPortFromPhysicalAddress(int target, int my)`: Determines the local port number on the current device (`my`) that leads to the `target` device. Returns `TARGET_NOT_UNDER_LOCAL_DEVICE` if target is not downstream.
- `isValidPhysicalAddress(int address)`: Validates physical address format (0.0.0.0 to F.F.F.F, ensuring no non-zero digits after a zero).
- `getHdmiAddressRelativePosition(int src, int dest)`: Returns relationship:
    - `DIRECTLY_BELOW`, `BELOW`
    - `DIRECTLY_ABOVE`, `ABOVE`
    - `SAME`
    - `SIBLING`
    - `DIFFERENT_BRANCH`
    - `UNKNOWN`

## Constants
- `TARGET_NOT_UNDER_LOCAL_DEVICE` (-1)
- `TARGET_SAME_PHYSICAL_ADDRESS` (0)

## Java-to-C++ Translation Guide
- **Bitwise Logic**: `getLocalPortFromPhysicalAddress` and `getHdmiAddressRelativePosition` rely on bitwise masking (`0xF000` shifted). This translates directly to C++.
- **Validation**: Replicate `isValidPhysicalAddress` logic.

## Implementation Risks
- **Edge Cases**: `0xFFFF` (Unregistered/Invalid) handling.
