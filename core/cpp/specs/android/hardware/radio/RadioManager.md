# RadioManager - Reverse Engineering Documentation

## Executive Summary
`RadioManager` is the primary system service client for the broadcast radio subsystem (`Context.RADIO_SERVICE`). It allows applications to list available radio modules (tuners), open them for control, and manage global settings. It acts as a factory for `RadioTuner` instances.

## Architecture Overview
-   **Type**: System Service Manager.
-   **Package**: `android.hardware.radio`.
-   **IPC Interface**: `IRadioService`.
-   **Key Concepts**:
    -   **Modules**: Physical radio hardware (AM/FM, DAB, Sat).
    -   **Bands**: Frequency ranges (AM, FM, HD).
    -   **ProgramInfo**: Snapshot of current station state.

## Detailed Functionality

### Core Methods
-   `listModules(List<ModuleProperties>)`: Queries `IRadioService` for available hardware modules. Populates the provided list.
-   `openTuner(...)`: Opens a specific module.
    -   Inputs: `moduleId`, `BandConfig`, `withAudio`, `callback`, `handler`.
    -   Mechanism: Calls `mService.openTuner(...)`, wraps the returned `ITuner` in a `TunerAdapter`, and the callback in a `TunerCallbackAdapter`.
-   `addAnnouncementListener(...)`: Registers a listener for specific announcement types (Traffic, Emergency). Uses `ICloseHandle` for unregistration.

### Inner Classes (Data Structures)
1.  **ModuleProperties**:
    -   Describes a radio module: ID, Service Name, Class (AM_FM, SAT, DT), Implementor, Version, Serial, NumTuners, NumAudioSources.
    -   `mBands`: Array of `BandDescriptor`.
    -   `isCaptureSupported`, `isBackgroundScanningSupported`.
    -   `mDabFrequencyTable`: Map for DAB channels.
2.  **BandDescriptor** (and subclasses `FmBandDescriptor`, `AmBandDescriptor`):
    -   Describes a frequency band: Region, Type (AM/FM/HD), Limits (Lower/Upper), Spacing.
    -   **FmBandDescriptor**: Adds flags for Stereo, RDS, TA (Traffic), AF (Alt Freq), EA (Emergency).
    -   **AmBandDescriptor**: Adds flag for Stereo.
3.  **BandConfig** (and subclasses `FmBandConfig`, `AmBandConfig`):
    -   Configuration for a band. Wraps a `BandDescriptor`.
    -   Builders provided to construct these configs.
4.  **ProgramInfo**:
    -   Comprehensive snapshot of a tuned program.
    -   Fields: `mSelector`, `mLogicallyTunedTo`, `mPhysicallyTunedTo`, `mRelatedContent`, `mInfoFlags` (Live, Muted, Stereo, Tuned), `mSignalQuality`, `mMetadata`, `mVendorInfo`.
    -   `RadioAlert`: Optional field for EAS alerts.

### Constants
-   **Status Codes**: `STATUS_OK`, `STATUS_ERROR`, `STATUS_PERMISSION_DENIED`, etc.
-   **Classes**: `CLASS_AM_FM`, `CLASS_SAT`, `CLASS_DT`.
-   **Bands**: `BAND_AM`, `BAND_FM`, `BAND_AM_HD`, `BAND_FM_HD`.
-   **Regions**: `REGION_ITU_1` (Europe), `REGION_ITU_2` (Americas), etc.
-   **Config Flags**: `CONFIG_FORCE_MONO`, `CONFIG_FORCE_ANALOG`, `CONFIG_RDS_AF`, etc.

## Data Model
-   **ModuleProperties**: Static description of hardware capabilities.
-   **BandConfig**: Runtime configuration for the hardware.
-   **ProgramInfo**: Dynamic status of the current station.

## Java-to-C++ Translation Guide
-   **Service Interaction**: Use Android NDK Binder (`AIBinder` or `libbinder`) to communicate with `IRadioService`.
-   **Parcelables**: All inner classes (`ModuleProperties`, `BandConfig`, etc.) need C++ Parcelable equivalents.
-   **Callbacks**: `openTuner` requires creating a native callback stub.
-   **Type Safety**: Use `enum class` for the integer constants (Status, Band, Region).

## Implementation Risks
-   **Binder Complexity**: The interaction involves complex Binder callbacks (`ITunerCallback`) and data structures. Ensure proper lifetime management of callback objects.
-   **Truncation**: Note that `ProgramInfo` contains legacy fields (`channel`, `subChannel`) derived from selectors; C++ logic should prefer using `ProgramSelector` directly.

---
