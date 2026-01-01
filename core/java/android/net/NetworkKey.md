# NetworkKey.java - Reverse Engineering Documentation

## Executive Summary
`NetworkKey` uniquely identifies a network. It is currently primarily used for Wi-Fi networks (wrapping a `WifiKey`). It was part of the deprecated `NetworkScoreManager` architecture.

## Architecture Overview
- **Type**: Parcelable Identifier
- **Package**: `android.net`
- **Dependencies**: `android.net.WifiKey`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `type` | `int` | Network type (e.g., `TYPE_WIFI`). |
| `wifiKey` | `WifiKey` | Valid only if type is WIFI. |

## API Reference
-   `createFromScanResult(ScanResult)`: Factory.
-   `createFromWifiInfo(WifiInfo)`: Factory.

## Java-to-C++ Translation Guide
A tagged union or variant.

```cpp
struct NetworkKey {
    enum Type { WIFI = 1 };
    Type type;
    std::optional<WifiKey> wifiKey;
};
```
