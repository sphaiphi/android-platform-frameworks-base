# CellularBatteryStats - Reverse Engineering Documentation

## Executive Summary
`CellularBatteryStats` is a Parcelable class responsible for encapsulating power consumption and activity statistics related to the cellular radio (modem). It provides granular data such as transmission/reception times, time spent in different radio access technologies (RAT), signal strength levels, and energy consumption metrics. This class is primarily used by the system to track and attribute battery usage to cellular connectivity.

## Architecture Overview
-   **Type**: Data Object / Parcelable.
-   **Usage**: System API (`@SystemApi`), primarily used by `BatteryStatsService` and connectivity subsystems to pass battery stats across processes.
-   **Data Source**: Likely populated from modem firmware stats or `NetworkStatsService`.

## Data Model
-   **Timestamps**: `mLoggingDurationMs`, `mKernelActiveTimeMs`, `mSleepTimeMs`, `mIdleTimeMs`, `mRxTimeMs`.
-   **Data Traffic**: `mNumPacketsTx`, `mNumBytesTx`, `mNumPacketsRx`, `mNumBytesRx`.
-   **Energy**: `mEnergyConsumedMaMs` (Milli-ampere milliseconds), `mMonitoredRailChargeConsumedMaMs`.
-   **Granular Metrics (Arrays)**:
    -   `mTimeInRatMs`: Time spent in different Radio Access Technologies (e.g., LTE, NR).
    -   `mTimeInRxSignalStrengthLevelMs`: Time spent at various signal strength levels (0-4).
    -   `mTxTimeMs`: Time spent transmitting at various power levels (0-4).

## API Reference
-   **Getters**: Accessors for all fields (e.g., `getLoggingDurationMillis()`, `getEnergyConsumedMaMillis()`).
-   **Granular Getters**:
    -   `getTimeInRatMicros(int networkType)`: Returns time in microseconds for a specific RAT.
    -   `getTimeInRxSignalStrengthLevelMicros(int bin)`: Returns time in microseconds for a specific signal strength.
    -   `getTxTimeMillis(int level)`: Returns time in milliseconds for a specific TX power level.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: Likely corresponds to a structure in `frameworks/native/libs/binder` or a generated AIDL C++ backend.
-   **Parceling**:
    -   **Write Order**:
        1.  Longs: LoggingDuration, KernelActiveTime, PacketsTx, BytesTx, PacketsRx, BytesRx, SleepTime, IdleTime, RxTime, EnergyConsumed.
        2.  Long Arrays: TimeInRat, TimeInRxSignalStrength, TxTime.
        3.  Long: MonitoredRailCharge.
-   **Arrays**: Note that the arrays are bounded by constants (`BatteryStats.NUM_DATA_CONNECTION_TYPES`, `CellSignalStrength.getNumSignalStrengthLevels()`, `ModemActivityInfo.getNumTxPowerLevels()`). The C++ implementation must respect these sizes during serialization/deserialization.

## Implementation Risks
-   **Array Bounds**: The constructor truncates input arrays to expected sizes. A C++ implementation reading this Parcel must handle potential mismatches or ensure it reads the array length written by `writeLongArray` correctly (standard Parcel behavior).
-   **Units**: Mixed units (milliseconds vs microseconds in getters). `getTimeInRatMicros` returns micros, but storage is `mTimeInRatMs` (millis?).