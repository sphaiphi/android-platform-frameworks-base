# MobileLinkQualityInfo.java - Reverse Engineering Documentation

## Executive Summary
`MobileLinkQualityInfo` is a subclass of `LinkQualityInfo` specifically for mobile (cellular) networks. It adds fields for LTE, CDMA, EVDO, and GSM signal metrics.

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`
- **Extends**: `LinkQualityInfo`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mMobileNetworkType` | `int` | `TelephonyManager` network type. |
| `mRssi` | `int` | GSM Signal Strength. |
| `mGsmErrorRate` | `int` | GSM Bit Error Rate. |
| `mCdmaDbm` | `int` | CDMA RSSI (dBm). |
| `mCdmaEcio` | `int` | CDMA Ec/Io. |
| `mEvdoDbm` | `int` | EVDO RSSI (dBm). |
| `mEvdoEcio` | `int` | EVDO Ec/Io. |
| `mEvdoSnr` | `int` | EVDO Signal-to-Noise Ratio. |
| `mLteSignalStrength` | `int` | LTE Signal Strength. |
| `mLteRsrp` | `int` | LTE Reference Signal Received Power. |
| `mLteRsrq` | `int` | LTE Reference Signal Received Quality. |
| `mLteRssnr` | `int` | LTE RSSNR. |
| `mLteCqi` | `int` | LTE Channel Quality Indicator. |

## Serialization
Overrides `writeToParcel` to append its fields after the base class fields.
The base class `CREATOR` handles delegation to `createFromParcelBody` for this type.

## Java-to-C++ Translation Guide
Extend the base C++ struct.

```cpp
struct MobileLinkQualityInfo : public LinkQualityInfo {
    int mobileNetworkType = INT_MAX;
    int rssi = INT_MAX;
    int gsmErrorRate = INT_MAX;
    // ... all other fields initialized to INT_MAX
};
```
