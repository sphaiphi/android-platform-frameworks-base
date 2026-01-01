# HdmiAudioSystemClient - Reverse Engineering Documentation

## Executive Summary
`HdmiAudioSystemClient` represents an HDMI-CEC Audio System logical device (e.g., Soundbar, AVR). It extends `HdmiClient` and provides specific functionality for audio systems, such as reporting audio status and controlling system audio mode.

## Architecture Overview
- **Inheritance**: Extends `HdmiClient`.
- **Device Type**: `HdmiDeviceInfo.DEVICE_AUDIO_SYSTEM` (5).
- **Service Interaction**: Uses `IHdmiControlService` via `HdmiClient`.

## Detailed Functionality

### Audio Status Reporting
- **Method**: `sendReportAudioStatusCecCommand(boolean isMuteAdjust, int volume, int maxVolume, boolean isMute)`
- **Purpose**: Sends `<Report Audio Status>` to TV.
- **Rate Limiting**: Enforces a minimum interval (`REPORT_AUDIO_STATUS_INTERVAL_MS` = 500ms) between reports unless `isMuteAdjust` is true (immediate report for mute changes). Uses a `Handler` for delayed sending.
- **Pending Updates**: If a request comes during the block period, it is marked pending and sent after the interval expires.

### System Audio Mode
- **Method**: `setSystemAudioMode(boolean state, SetSystemAudioModeCallback callback)`
- **Status**: Currently a placeholder (TODO in code).
- **Method**: `setSystemAudioModeOnForAudioOnlySource()`
- **Purpose**: Broadcasts System Audio Mode ON without querying TV support. Used for audio-only sources (like STB) to enable volume passthrough.

## Data Model
- **State**:
    - `mLastVolume`, `mLastMaxVolume`, `mLastIsMute`: Caches last reported values.
    - `mCanSendAudioStatus`: Boolean flag for rate limiting.
    - `mPendingReportAudioStatus`: Boolean flag for queued updates.

## API Reference
- `getDeviceType()`: Returns 5.
- `sendReportAudioStatusCecCommand(...)`
- `setSystemAudioMode(...)`
- `setSystemAudioModeOnForAudioOnlySource()`

## Java-to-C++ Translation Guide
- **Rate Limiting**: Implement equivalent logic using a timer or delayed task mechanism in C++.
- **IPC**: Call `IHdmiControlService::reportAudioStatus`.
- **Handler**: Use `looper` or `std::thread` equivalent for delayed execution.

## Implementation Risks
- **Concurrency**: Ensure thread safety for flags `mCanSendAudioStatus` and `mPendingReportAudioStatus`.
