# DeviceFeatures - Reverse Engineering Documentation

## Executive Summary
`DeviceFeatures` is an immutable class that represents the support status of various HDMI-CEC features, corresponding to the `[Device Features]` operand introduced in HDMI-CEC 2.0. It allows parsing this operand from a byte array and serializing it back.

## Architecture Overview
- **Type**: Immutable Data Class.
- **Role**: Helper for parsing and storing CEC 2.0 device feature flags.
- **Pattern**: Builder Pattern used for construction.

## Detailed Functionality

### Feature Support Status
Each feature tracks a status using `FeatureSupportStatus`:
- `FEATURE_NOT_SUPPORTED` (0)
- `FEATURE_SUPPORTED` (1)
- `FEATURE_SUPPORT_UNKNOWN` (2)

### Features Tracked
1.  **Record TV Screen**: Whether the device is a TV that supports `<Record TV Screen>`.
2.  **Set OSD String**: Whether the device is a TV that supports `<Set OSD String>`.
3.  **Deck Control**: Whether the device supports deck control.
4.  **Set Audio Rate**: Whether the device is a Source that supports `<Set Audio Rate>`.
5.  **ARC Tx**: Whether the device is a Sink that supports ARC Tx (Transmission).
6.  **ARC Rx**: Whether the device is a Source that supports ARC Rx (Reception).
7.  **Set Audio Volume Level**: Whether the device supports `<Set Audio Volume Level>`.

### Key Methods
- `fromOperand(byte[] deviceFeaturesOperand)`: Static factory to parse a byte array (operand) into a `DeviceFeatures` instance. Bit 7 of the first byte is ignored (extension bit).
- `toOperand()`: Serializes the features into a byte array (currently 1 byte). Maps `UNKNOWN` to 0 (Not Supported).
- `toBuilder()`: Creates a builder from an existing instance.
- `update(DeviceFeatures newDeviceFeatures)`: Updates unknown statuses with new information.

## Data Model
- **Storage**: `int` fields for each feature status.
- **Operand Format**:
    - Bit 6: Record TV Screen
    - Bit 5: Set OSD String
    - Bit 4: Deck Control
    - Bit 3: Set Audio Rate
    - Bit 2: ARC Tx
    - Bit 1: ARC Rx
    - Bit 0: Set Audio Volume Level

## API Reference
- `getRecordTvScreenSupport()`
- `getSetOsdStringSupport()`
- `getDeckControlSupport()`
- `getSetAudioRateSupport()`
- `getArcTxSupport()`
- `getArcRxSupport()`
- `getSetAudioVolumeLevelSupport()`

## Java-to-C++ Translation Guide
- **Class**: C++ class/struct.
- **Enums**: Map `FeatureSupportStatus` to C++ enum or constants.
- **Bit Manipulation**: Replicate `fromOperand` and `toOperand` bitwise logic exactly.
- **Immutability**: Make members const or use private setters in C++.

## Test Cases & Validation
- **Serialization**: Verify `fromOperand` -> `toOperand` consistency.
- **Unknown Handling**: Verify `update` method correctly overwrites `UNKNOWN` but respects existing values.
