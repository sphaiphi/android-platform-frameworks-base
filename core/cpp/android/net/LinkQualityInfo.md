# LinkQualityInfo.java - Reverse Engineering Documentation

## Executive Summary
`LinkQualityInfo` is a base class for reporting network link quality metrics. It encapsulates common statistics like signal strength, packet counts, errors, and theoretical bandwidths. It is designed to be subclassed for specific network types (WiFi, Mobile).

## Architecture Overview
- **Type**: Base Parcelable Class
- **Package**: `android.net`
- **Subclasses**: `WifiLinkQualityInfo`, `MobileLinkQualityInfo`.
- **Constants**: Defines `UNKNOWN_INT` (Integer.MAX_VALUE) and `UNKNOWN_LONG` (Long.MAX_VALUE) as sentinels for missing data.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mNetworkType` | `int` | ConnectivityManager network type (e.g., TYPE_WIFI). |
| `mNormalizedSignalStrength` | `int` | 0-99 scale. |
| `mPacketCount` | `long` | Total packets sent/received. |
| `mPacketErrorCount` | `long` | Total errors. |
| `mTheoreticalTxBandwidth` | `int` | Kbps. |
| `mTheoreticalRxBandwidth` | `int` | Kbps. |
| `mTheoreticalLatency` | `int` | Milliseconds. |
| `mLastDataSampleTime` | `long` | Timestamp of last sample. |
| `mDataSampleDuration` | `int` | Duration of sample in ms. |

## Serialization
Uses a custom discriminator `objectType` in `writeToParcel` to support polymorphism across Binder.
-   `OBJECT_TYPE_LINK_QUALITY_INFO = 1`
-   `OBJECT_TYPE_WIFI_LINK_QUALITY_INFO = 2`
-   `OBJECT_TYPE_MOBILE_LINK_QUALITY_INFO = 3`

The `CREATOR` reads this int first and delegates to the appropriate subclass creator or initializes the base class.

## Java-to-C++ Translation Guide

### Polymorphism
C++ doesn't support Parcelable polymorphism out-of-the-box in the same way.
-   **Option 1**: A single C++ struct `LinkQualityInfo` containing a union or `std::variant` of subclass data.
-   **Option 2**: A base class with virtual `writeToParcel`, reading the type tag first.

### Sentinel Values
Maintain `UNKNOWN_INT` and `UNKNOWN_LONG` constants exact values (`INT_MAX`, `LONG_MAX`) to ensure compatibility with existing Java consumers.

### Implementation
```cpp
struct LinkQualityInfo {
    int networkType = -1;
    int normalizedSignalStrength = INT_MAX;
    int64_t packetCount = INT64_MAX;
    int64_t packetErrorCount = INT64_MAX;
    int theoreticalTxBandwidth = INT_MAX;
    int theoreticalRxBandwidth = INT_MAX;
    int theoreticalLatency = INT_MAX;
    int64_t lastDataSampleTime = INT64_MAX;
    int dataSampleDuration = INT_MAX;
    
    // ... serialization logic
};
```
