# WifiActivityEnergyInfo - Reverse Engineering Documentation

## Executive Summary
`WifiActivityEnergyInfo` records the energy and activity state of the Wi-Fi controller since boot. It captures the state of the Wi-Fi stack (Active, Scanning, Idle), durations for transmission/reception/scan/idle, and the total energy consumed. It includes logic to calculate energy estimates using `PowerProfile` if the hardware doesn't provide direct energy readings.

## Architecture Overview
-   **Type**: Data Object / Parcelable.
-   **Usage**: System API (`@SystemApi`). Returned by `WifiManager` or `BatteryStatsManager` to report instantaneous or accumulated energy stats.
-   **Calculated Fields**: `mControllerEnergyUsedMicroJoules` can be calculated on-demand (lazy) if provided as `DEFERRED_ENERGY_ESTIMATE`.

## Data Model
-   `mTimeSinceBootMillis` (long): Elapsed realtime since boot.
-   `mStackState` (int): Enum (`STACK_STATE_INVALID`, `ACTIVE`, `SCANNING`, `IDLE`).
-   `mControllerTxDurationMillis` (long): TX time.
-   `mControllerRxDurationMillis` (long): RX time.
-   `mControllerScanDurationMillis` (long): Scan time.
-   `mControllerIdleDurationMillis` (long): Idle time.
-   `mControllerEnergyUsedMicroJoules` (long): Total energy.

## API Reference
-   **Constructors**:
    -   Standard constructor taking all durations + energy.
    -   Deferred constructor (energy = -1) which triggers calculation logic.
-   **Calculations**: `calculateEnergyMicroJoules` uses `PowerProfile` (frameworks/base/core/java/com/android/internal/os/PowerProfile.java) to look up average current (mA) for TX/RX/Idle and voltage (V) to compute MicroJoules.
    -   Formula: `(TxTime*TxCurrent + RxTime*RxCurrent + IdleTime*IdleCurrent) * Voltage`.

## Java-to-C++ Translation Guide
-   **Parceling Order**:
    1.  `mTimeSinceBootMillis` (Long)
    2.  `mStackState` (Int)
    3.  `mControllerTxDurationMillis` (Long)
    4.  `mControllerRxDurationMillis` (Long)
    5.  `mControllerScanDurationMillis` (Long)
    6.  `mControllerIdleDurationMillis` (Long)
    -   **Critical**: The energy value (`mControllerEnergyUsedMicroJoules`) is **NOT** written to the Parcel. The receiving side re-instantiates it with `DEFERRED_ENERGY_ESTIMATE` (-1), expecting the receiver (usually `BatteryStatsService`) to recalculate it.

## Implementation Risks
-   **Energy Calculation**: The calculation depends on `PowerProfile`, which is a Java-framework concept reading `power_profile.xml`. A C++ implementation acting as the receiver/calculator must have access to these hardware power constants to compute the energy if it wasn't provided by the driver.