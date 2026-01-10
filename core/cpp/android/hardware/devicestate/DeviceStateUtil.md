# DeviceStateUtil - Reverse Engineering Documentation

## Executive Summary
`DeviceStateUtil` provides static utility methods for calculating state identifiers based on device properties.

## Detailed Functionality

### `calculateBaseStateIdentifier`
**Signature**: `int calculateBaseStateIdentifier(DeviceState currentState, List<DeviceState> supportedStates)`

**Algorithm**:
1. Get the physical properties of the `currentState`.
2. Iterate through `supportedStates`.
3. For each supported state:
    - Skip if it has *no* physical properties.
    - Check if the supported state's physical properties are a subset of (or match) the current state's physical properties.
    - **Logic Check**: The Java code iterates the *supported state's* physical properties and checks if the `currentState` has them.
        - `isDeviceStateMatchingPhysicalProperties`: Iterates `physicalProperties` (from supported state). Checks if `currentState.hasProperty(property)`.
    - If match found, return that supported state's identifier.
4. Return `INVALID_DEVICE_STATE_IDENTIFIER` (-1) if no match.

## Java-to-C++ Translation Guide
- Implement as a static utility function or part of a helper class.
- Replicate the iteration logic exactly: finding the supported state whose physical properties are fully satisfied by the current state.
