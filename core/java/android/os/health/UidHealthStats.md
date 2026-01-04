# UidHealthStats - Reverse Engineering Documentation

## Executive Summary
`UidHealthStats` defines the comprehensive schema for per-UID health metrics. This is the root-level key set for the `HealthStats` object returned by `SystemHealthManager.takeUidSnapshot`. It covers battery usage, network activity (Wi-Fi, Mobile, Bluetooth), WakeLocks, CPU time, and nested statistics for Processes, Packages, and PIDs.

## Architecture Overview
-   **Role**: Key Definition Class.
-   **Context**: The "Master" schema for app health data.

## Data Model

### Metric Categories
1.  **Battery & Screen**:
    -   `MEASUREMENT_REALTIME_BATTERY_MS`, `MEASUREMENT_UPTIME_BATTERY_MS`: General duration.
    -   `MEASUREMENT_REALTIME_SCREEN_OFF_BATTERY_MS`: Duration while screen off (deep sleep candidate).
2.  **WakeLocks** (`TYPE_TIMERS` - Map of Tags):
    -   `TIMERS_WAKELOCKS_FULL`: Screen-keeping locks.
    -   `TIMERS_WAKELOCKS_PARTIAL`: CPU-keeping locks (Critical for battery).
    -   `TIMERS_WAKELOCKS_DRAW`, `TIMERS_WAKELOCKS_WINDOW`.
3.  **Network** (`MEASUREMENT` & `TIMER`):
    -   **Wi-Fi**: `RX_MS`, `TX_MS`, `IDLE_MS`, `POWER_MAMS`, `SCAN` (Timer), `RX/TX_BYTES`, `RX/TX_PACKETS`.
    -   **Mobile**: Similar set (RX/TX MS/Bytes/Packets, Power).
    -   **Bluetooth**: Similar set.
4.  **Hardware Usage**:
    -   `TIMER_GPS_SENSOR`: GPS usage.
    -   `TIMERS_SENSORS`: Map of Sensor Handles -> TimerStat.
    -   `TIMER_FLASHLIGHT`, `TIMER_CAMERA`, `TIMER_VIBRATOR`.
    -   `TIMER_AUDIO`, `TIMER_VIDEO`.
5.  **Process State** (`TIMER`):
    -   Breakdown of time spent in various states: `TOP`, `FOREGROUND_SERVICE`, `BACKGROUND`, `CACHED`, `TOP_SLEEPING`.
6.  **CPU**:
    -   `MEASUREMENT_USER_CPU_TIME_MS`, `MEASUREMENT_SYSTEM_CPU_TIME_MS`.
7.  **Sub-Stats** (`STATS`):
    -   `STATS_PACKAGES`: Breakdown by APK.
    -   `STATS_PIDS`: Live process stats.
    -   `STATS_PROCESSES`: Aggregated process stats.

## API Reference
-   `CONSTANTS`: Static `HealthKeys.Constants` object.

## Java-to-C++ Translation Guide
-   **Base Offset**: `BASE_UID = 10000`.
-   This class defines a large range of constants (10001 to 10064+).
-   Crucial for mapping BatteryStats data to C++.
