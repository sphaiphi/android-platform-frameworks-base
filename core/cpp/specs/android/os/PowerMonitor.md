# PowerMonitor - Reverse Engineering Documentation

## Executive Summary
`PowerMonitor` represents a source of power consumption data, such as a hardware power rail (ODPM - On-Device Power Measurement) or a modeled energy consumer (e.g., GPU model).

## Architecture Overview
-   **Role**: Data Identifier.
-   **Types**: `POWER_MONITOR_TYPE_CONSUMER` (0), `POWER_MONITOR_TYPE_MEASUREMENT` (1).

## Data Model
-   `index` (int): Internal index (unstable across reboots).
-   `mType` (int): Type.
-   `mName` (String): Human-readable name (e.g., "S2S_VDD_G3D").

## Java-to-C++ Translation Guide
-   **Parcelable**: Matches `PowerMonitor.aidl`.
-   **Struct**: `struct PowerMonitor { int32_t index; int32_t type; String16 name; };`.
