# RadioTuner - Reverse Engineering Documentation

## Executive Summary
`RadioTuner` is an abstract base class defining the interface for controlling a radio tuner. It provides methods for tuning, scanning, muting, and retrieving program information. It is the client-facing API returned by `RadioManager.openTuner`.

## Architecture Overview
-   **Type**: Abstract Class, System API.
-   **Package**: `android.hardware.radio`.
-   **Role**: Interface for Tuner operations. Implemented by `TunerAdapter`.

## Detailed Functionality

### Core Methods (Abstract)
-   `close()`: Releases resources.
-   `setConfiguration(BandConfig)` / `getConfiguration(...)`: Deprecated (HAL 1.x).
-   `setMute(boolean)` / `getMute()`: Mutes/unmutes audio.
-   `step(direction, skipSubChannel)`: Steps to next adjacent station.
-   `scan(direction, skipSubChannel)`: Scans for next valid station (Deprecated, use `seek`).
-   `seek(direction, skipSubChannel)`: Seeks for next valid station.
-   `tune(ProgramSelector)`: Tunes to a specific station.
-   `cancel()`: Cancels current operation (scan/seek).
-   `startBackgroundScan()`: Initiates background scan.
-   `getDynamicProgramList(Filter)`: Returns a `ProgramList` object for live updates.
-   `isConfigFlagSupported` / `setConfigFlag`: Manages flags like `CONFIG_FORCE_MONO`.
-   `setParameters` / `getParameters`: Vendor-specific Opaque key-value storage.

### Inner Class: Callback
-   Abstract class for receiving async results.
-   `onTuneFailed`: Called when tuning/scanning fails.
-   `onProgramInfoChanged`: Called when the tuned station changes or metadata updates.
-   `onTrafficAnnouncement`, `onEmergencyAnnouncement`.
-   `onAntennaState`: Connection status.
-   `onBackgroundScanComplete`.
-   `onProgramListChanged`.

### Constants
-   **Directions**: `DIRECTION_UP`, `DIRECTION_DOWN`.
-   **Errors**: `ERROR_HARDWARE_FAILURE`, `ERROR_SCAN_TIMEOUT`, etc.
-   **Tuner Results**: `TUNER_RESULT_OK`, `TUNER_RESULT_TIMEOUT`, etc.

## Java-to-C++ Translation Guide
-   **Interface**: This maps to a C++ abstract base class or interface.
-   **Async Model**: Methods like `tune` and `scan` are asynchronous; the C++ implementation should likely accept a callback or delegate to a listener, mirroring the Java design.
-   **Error Handling**: Map `TUNER_RESULT_*` to a robust error handling mechanism (e.g., `std::expected` or status codes).

---
