# HdmiDeviceInfo - Reverse Engineering Documentation

## Executive Summary
`HdmiDeviceInfo` is a comprehensive data class encapsulating information about an HDMI device. It handles three types of devices: CEC Devices, MHL Devices, and Hardware Ports. It is Parcelable.

## Architecture Overview
- **Type**: Data Class / Parcelable.
- **Device Types**:
    - `HDMI_DEVICE_TYPE_CEC` (0)
    - `HDMI_DEVICE_TYPE_MHL` (1)
    - `HDMI_DEVICE_TYPE_HARDWARE` (2)
    - `HDMI_DEVICE_TYPE_INACTIVE` (100)

## Detailed Functionality

### Fields
- **Common**: `id`, `hdmiDeviceType`, `physicalAddress`, `portId`.
- **CEC**: `logicalAddress`, `deviceType` (TV, Playback, etc.), `cecVersion`, `vendorId`, `displayName`, `devicePowerStatus`, `deviceFeatures`.
- **MHL**: `deviceId`, `adopterId`.

### ID Generation
- IDs are offset-based:
    - CEC: `0x0` + Logical Address.
    - MHL: `0x80` + Port ID.
    - Hardware: `0xC0` + Port ID.

### Helper Methods
- `idForCecDevice(int address)`
- `idForMhlDevice(int portId)`
- `idForHardware(int portId)`
- `isSourceType()`: Checks if device is Playback, Recorder, Tuner (CEC) or MHL.

### Builder Pattern
- `cecDeviceBuilder()`: Starts builder for CEC.
- `mhlDevice(...)`: Static factory for MHL.
- `hardwarePort(...)`: Static factory for Hardware Port.

## Data Model
- **Parcelable**: Custom `writeToParcel` and `createFromParcel` logic based on `hdmiDeviceType`.
- **Constants**:
    - Logical Addresses: `ADDR_INTERNAL` (0), `ADDR_INVALID` (-1).
    - Physical Address: `PATH_INTERNAL` (0x0000), `PATH_INVALID` (0xFFFF).
    - Device Types: `DEVICE_TV`, `DEVICE_PLAYBACK`, `DEVICE_AUDIO_SYSTEM`, etc.

## Java-to-C++ Translation Guide
- **Class**: C++ class `HdmiDeviceInfo`.
- **Parcelable**: Implement `android::os::Parcelable`.
- **Union/Variant**: Since fields are mutually exclusive based on type, C++ could use `std::variant` or a union-like structure, though a flat class with unused fields (like Java) is easier to port directly.
- **Serialization**: Ensure exact matching of the write order in `writeToParcel`.

## Test Cases & Validation
- **Serialization**: Verify round-trip parceling for CEC, MHL, and Hardware types.
- **ID Generation**: Validate ID offsets logic.
