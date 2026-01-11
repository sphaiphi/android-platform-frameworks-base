# HdmiTvClient - Reverse Engineering Documentation

## Executive Summary
`HdmiTvClient` represents an HDMI-CEC TV logical device. It provides extensive control over inputs, audio, and recording features.

## Architecture Overview
- **Inheritance**: Extends `HdmiClient`.
- **Device Type**: `HdmiDeviceInfo.DEVICE_TV` (0).

## Detailed Functionality

### Input Switching
- `portSelect(int portId, SelectCallback callback)`: Switch to physical HDMI port.
- `setInputChangeListener(InputChangeListener listener)`: Listen for Active Source changes.

### System Audio Control
- `setSystemAudioMode(boolean enabled, SelectCallback callback)`: Enable/Disable System Audio Mode (SAM).
- `setSystemAudioVolume(int oldIndex, int newIndex, int maxIndex)`: Control AVR volume.
- `setSystemAudioMute(boolean mute)`: Control AVR mute.

### Recording
- `startOneTouchRecord(int recorderAddress, RecordSource source)`: Start recording on recorder.
- `stopOneTouchRecord(int recorderAddress)`: Stop recording.
- `startTimerRecording(int recorderAddress, int sourceType, TimerRecordSource source)`: Schedule timer recording.
- `clearTimerRecording(...)`: Clear scheduled timer.
- `setRecordListener(HdmiRecordListener listener)`: Set listener for incoming record requests.

### MHL
- `sendMhlVendorCommand(...)`: Send vendor command to MHL device.
- `setHdmiMhlVendorCommandListener(...)`: Listen for MHL vendor commands.

## Data Model
- **Callbacks**: `SelectCallback`, `InputChangeListener`, `HdmiMhlVendorCommandListener`.

## Java-to-C++ Translation Guide
- **Complex Logic**: Most logic is in the service (`IHdmiControlService`). The client acts as a proxy.
- **Callbacks**: C++ needs to handle multiple callback types (Input change, Record listener, MHL listener).

