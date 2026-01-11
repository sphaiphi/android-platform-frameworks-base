# RssiCurve.java - Reverse Engineering Documentation

## Executive Summary
`RssiCurve` defines a mapping function from RSSI (signal strength) to a score (byte). It uses a linear interpolation buckets approach. Used in network scoring.

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `start` | `int` | Starting RSSI (dBm). |
| `bucketWidth` | `int` | Width of each bucket (dBm). |
| `rssiBuckets` | `byte[]` | Score values for each bucket. |
| `activeNetworkRssiBoost` | `int` | Bonus RSSI if network is active. |

## Algorithm (`lookupScore`)
1.  Apply boost if active.
2.  Index = `(rssi - start) / bucketWidth`.
3.  Clamp index to `[0, rssiBuckets.length - 1]`.
4.  Return `rssiBuckets[index]`.

## Java-to-C++ Translation Guide
Simple math logic.
```cpp
int8_t lookupScore(int rssi, bool isActive) {
    if (isActive) rssi += activeNetworkRssiBoost;
    int index = (rssi - start) / bucketWidth;
    // clamp and return
}
```
