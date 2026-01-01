# HdmiControlManager - Reverse Engineering Documentation

## Executive Summary
`HdmiControlManager` is the primary system service manager for HDMI control (CEC, MHL, eARC). It provides access to specific clients (TV, Playback, Audio System) and manages global settings and listeners.

## Architecture Overview
- **Type**: Manager (System Service Wrapper).
- **Service**: `Context.HDMI_CONTROL_SERVICE`.
- **IPC**: Wraps `IHdmiControlService` Binder interface.
- **Factory**: Creates `HdmiTvClient`, `HdmiPlaybackClient`, `HdmiAudioSystemClient`, `HdmiSwitchClient`.

## Detailed Functionality

### Client Factory
- `getClient(int type)`: Returns specific `HdmiClient` based on type.
- **Getters**: `getTvClient()`, `getPlaybackClient()`, `getAudioSystemClient()`, `getSwitchClient()`. Checks device capabilities (e.g., `mHasTvDevice`) before returning.

### Global Device Control
- `getConnectedDevices()`: Returns list of `HdmiDeviceInfo` for all connected CEC devices.
- `getPortInfo()`: Returns list of `HdmiPortInfo`.
- `powerOffDevice(HdmiDeviceInfo)` / `powerOnDevice(HdmiDeviceInfo)`: Sends CEC power commands.
- `setActiveSource(HdmiDeviceInfo)`: Requests a device to become active source.
- `setStandbyMode(boolean)`: Puts the system to standby.

### Global Settings & Features
- **Volume Control**: `setHdmiCecVolumeControlEnabled(int)`.
- **System Audio**: `setSystemAudioControl(int)`, `setSystemAudioModeMuting(int)`.
- **TV Wake**: `setTvWakeOnOneTouchPlay(int)`.
- **Power Control**: `setPowerControlMode(String)`, `setPowerStateChangeOnActiveSourceLost(String)`.
- **Routing Control**: `setRoutingControl(int)`.
- **Soundbar Mode**: `setSoundbarMode(int)`.
- **eARC**: `setEarcEnabled(int)`.
- **SAD Query**: `setSadPresenceInQuery(...)`.

### Listeners
- **Hotplug**: `addHotplugEventListener`. Updates local physical address cache.
- **Control Status**: `addHdmiControlStatusChangeListener`.
- **Volume Control Feature**: `addHdmiCecVolumeControlFeatureListener`.
- **CEC Settings**: `addHdmiCecEnabledChangeListener`.

### Constants
- Defines extensive constants for:
    - Results (`RESULT_SUCCESS`, `RESULT_TIMEOUT`, etc.).
    - One Touch Record results/errors.
    - Timer Recording results/errors.
    - CEC Settings names and values (`HDMI_CEC_CONTROL_ENABLED`, `POWER_CONTROL_MODE_TV`, etc.).

## Data Model
- **Local State**: `mLocalPhysicalAddress` (cached via hotplug listener).
- **Capability Flags**: `mHasTvDevice`, `mHasPlaybackDevice`, `mHasAudioSystemDevice`, `mHasSwitchDevice`, `mIsSwitchDevice`.
- **Listener Maps**: Maps Java listeners to AIDL stubs (`mHotplugEventListeners`, etc.).

## Java-to-C++ Translation Guide
- **Singleton/Manager**: This maps to a manager class in C++ interacting with the Binder service.
- **Listener Maps**: Need a mechanism to map C++ callbacks/listeners to `sp<IHdmi...Listener>` Binder objects.
- **Cache**: Implement `mLocalPhysicalAddress` caching and updating via hotplug events.
- **Constants**: Map all integer and string constants to C++ `enum` or `constexpr`.

## Implementation Risks
- **Thread Safety**: Access to `mLocalPhysicalAddress` is guarded by `mLock`. Listeners are invoked on Binder threads or specific Executors.
- **Permissions**: Java enforces `@RequiresPermission`. C++ service side must enforce permissions.
