# WifiLinkQualityInfo.java - Reverse Engineering Documentation

## Executive Summary
`WifiLinkQualityInfo` is a subclass of `LinkQualityInfo` specifically for Wi-Fi networks. It adds BSSID, RSSI, and TX packet stats.

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`
- **Extends**: `LinkQualityInfo`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `mType` | `int` | Wi-Fi type (e.g., b/g/n - defined in `ScanResult`?). |
| `mBssid` | `String` | AP MAC address. |
| `mRssi` | `int` | Raw RSSI. |
| `mTxGood` | `long` | Good TX packets. |
| `mTxBad` | `long` | Bad TX packets. |

## Serialization
Overrides `writeToParcel` to append fields.

## Java-to-C++ Translation Guide
Extend `LinkQualityInfo` struct.
```cpp
struct WifiLinkQualityInfo : public LinkQualityInfo {
    int type = INT_MAX;
    std::string bssid;
    int rssi = INT_MAX;
    int64_t txGood = INT64_MAX;
    int64_t txBad = INT64_MAX;
};
```
