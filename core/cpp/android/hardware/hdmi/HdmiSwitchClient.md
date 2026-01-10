# HdmiSwitchClient - Reverse Engineering Documentation

## Executive Summary
`HdmiSwitchClient` represents an HDMI-CEC Switch device (device type 6) or any Android device capable of switching inputs (like a TV or AVR acting as a switch).

## Architecture Overview
- **Inheritance**: Extends `HdmiClient`.
- **Device Type**: `HdmiDeviceInfo.DEVICE_PURE_CEC_SWITCH` (6).

## Detailed Functionality

### Device Selection
- **Method**: `selectDevice(int logicalAddress, OnSelectListener listener)`
- **Purpose**: Switches to the device with the given logical address.
- **Mechanism**: Calls `mService.deviceSelect`.

### Port Selection
- **Method**: `selectPort(int portId, OnSelectListener listener)`
- **Purpose**: Switches to the specified HDMI port ID.
- **Mechanism**: Calls `mService.portSelect`.

### Listeners
- `OnSelectListener`: Callback for selection result.

## Data Model
- **Callbacks**: `OnSelectListener`.

## Java-to-C++ Translation Guide
- **Logic**: Thin wrapper around `IHdmiControlService`.
- **Callback**: Use `std::function` for `OnSelectListener`.

