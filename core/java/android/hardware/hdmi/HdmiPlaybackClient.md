# HdmiPlaybackClient - Reverse Engineering Documentation

## Executive Summary
`HdmiPlaybackClient` represents an HDMI-CEC Playback logical device (e.g., Set-top Box, Blu-ray player). It extends `HdmiClient`.

## Architecture Overview
- **Inheritance**: Extends `HdmiClient`.
- **Device Type**: `HdmiDeviceInfo.DEVICE_PLAYBACK` (4).

## Detailed Functionality

### One Touch Play
- **Method**: `oneTouchPlay(OneTouchPlayCallback callback)`
- **Purpose**: Sends `<Image View On>` and `<Active Source>` to become the active source.
- **Mechanism**: Calls `mService.oneTouchPlay`.

### Display Status
- **Method**: `queryDisplayStatus(DisplayStatusCallback callback)`
- **Purpose**: Queries the status of the TV (Power Status).
- **Mechanism**: Calls `mService.queryDisplayStatus`.

### Standby
- **Method**: `sendStandby()`
- **Purpose**: Sends `<Standby>` specifically to the TV (`ADDR_TV` = 0).

## Data Model
- **Callbacks**: `OneTouchPlayCallback`, `DisplayStatusCallback`.

## Java-to-C++ Translation Guide
- **Callbacks**: Use callback interfaces or std::function.
- **Logic**: Thin wrapper around `IHdmiControlService` calls.

