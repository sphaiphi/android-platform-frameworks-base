# BatteryStats - Reverse Engineering Documentation

## Executive Summary
`BatteryStats` is a massive, abstract class defining the schema for battery usage statistics. It defines constants, data structures (Timer, Counter, Uid, Proc, Pkg), and the reporting interface for the entire battery accounting system. It is the data source for the "Battery Usage" settings screen and `dumpsys batterystats`.

## Architecture Overview
-   **Role**: Data Schema / Abstract Interface.
-   **Implementation**: `com.android.internal.os.BatteryStatsImpl` (in a different package) is the concrete implementation that tracks state.
-   **Scope**: Tracks metrics per UID, Process, Package, Sensor, Wakelock, Network Interface, etc.

## Data Model

### Key Abstractions
-   **`Uid`**: Aggregates stats for a specific User ID (application).
-   **`Timer`**: Tracks time duration and count (e.g., Wakelock duration).
-   **`Counter`**: Tracks simple counts (e.g., Sensor activation count).
-   **`ControllerActivityCounter`**: Tracks Modem/WiFi/Bluetooth radio states (Idle, Rx, Tx levels).

### Metrics Covered
-   **Power States**: Screen On/Off, Battery Saver, Doze.
-   **Connectivity**: Mobile Radio, WiFi, Bluetooth, GPS.
-   **Application Activity**: WakeLocks (Partial, Full, Window), Jobs, Syncs, Alarms, CPU time (User/System), Foreground time.

## API Reference
-   **`getUidStats()`**: Returns a map of `Uid` stats.
-   **`getPhoneSignalStrengthTime(...)`**: Signal quality metrics.
-   **`getScreenOnTime(...)`**: Screen usage.
-   **`dump(...)`**: Generates the textual report used by `dumpsys`.

## Java-to-C++ Translation Guide
-   **Complexity**: This is one of the largest and most complex data structures in Android.
-   **Proto**: There is a mapping to `BatteryStatsServiceDumpProto`.
-   **Native Interface**: Much of the low-level tracking (CPU time, kernel wakelocks) happens in native code (`power_profile`, `suspend_blocker`) and is pulled into Java.
-   **Flattening**: `BatteryStats` implements custom binary serialization (not standard Parcelable) for persistence to disk (`/data/system/batterystats.bin`). C++ tools wishing to read this file must exactly match the serialization logic.

## Implementation Risks
-   **Versioning**: `CHECKIN_VERSION` changes frequently. Binary compatibility is fragile.
-   **Concurrency**: Access to stats is heavily synchronized in `BatteryStatsImpl`.
