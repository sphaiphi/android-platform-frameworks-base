# WifiBatteryStats - Reverse Engineering Documentation

## Executive Summary
`WifiBatteryStats` is a Parcelable class for detailed Wi-Fi power statistics. Similar to `CellularBatteryStats`, it tracks durations for kernel activity, traffic (packets/bytes), sleep/scan/idle/rx/tx times, and breakdown of time spent in various states and signal strengths.

## Architecture Overview
-   **Type**: Data Object / Parcelable.
-   **Usage**: System API (`@SystemApi`), used by `BatteryStats` to report Wi-Fi usage.

## Data Model
-   **Timestamps**: `mLoggingDurationMillis`, `mKernelActiveTimeMillis`, `mSleepTimeMillis`, `mScanTimeMillis`, `mIdleTimeMillis`, `mRxTimeMillis`, `mTxTimeMillis`.
-   **Traffic**: `mNumPacketsTx`, `mNumBytesTx`, `mNumPacketsRx`, `mNumBytesRx`.
-   **Energy**: `mEnergyConsumedMaMillis`, `mMonitoredRailChargeConsumedMaMillis`.
-   **Activity**: `mAppScanRequestCount`.
-   **Arrays**:
    -   `mTimeInStateMillis`: Time in data connection types (conceptually similar to RAT, but for Wifi? code references `BatteryStats.NUM_WIFI_STATES`).
    -   `mTimeInSupplicantStateMillis`: Time in `BatteryStatsManager.NUM_WIFI_SUPPL_STATES` (e.g., Disconnected, Associating, Completed).
    -   `mTimeInRxSignalStrengthLevelMillis`: Time in `BatteryStats.NUM_WIFI_SIGNAL_STRENGTH_BINS`.

## API Reference
-   **Getters**: Accessors for all fields.
-   **Parceling**: Standard read/write.

## Java-to-C++ Translation Guide
-   **Parceling Order**:
    1.  Longs: LoggingDuration, KernelActiveTime, PacketsTx, BytesTx, PacketsRx, BytesRx, SleepTime, ScanTime, IdleTime, RxTime, TxTime, EnergyConsumed, AppScanRequestCount.
    2.  Long Arrays: TimeInState, TimeInRxSignalStrength, TimeInSupplicantState.
    3.  Long: MonitoredRailCharge.
-   **Array Sizing**:
    -   `mTimeInStateMillis`: `BatteryStatsManager.NUM_WIFI_STATES` (8).
    -   `mTimeInRxSignalStrengthLevelMillis`: `BatteryStats.NUM_WIFI_SIGNAL_STRENGTH_BINS` (5).
    -   `mTimeInSupplicantStateMillis`: `BatteryStatsManager.NUM_WIFI_SUPPL_STATES` (13).

## Implementation Risks
-   **Constants**: The array sizes depend on constants defined in `BatteryStats` and `BatteryStatsManager`. C++ code must sync these constants to avoid parcel mismatch.