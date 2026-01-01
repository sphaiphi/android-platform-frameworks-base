# TelephonyNetworkSpecifier.java - Reverse Engineering Documentation

## Executive Summary
`TelephonyNetworkSpecifier` specifies a cellular network by Subscription ID (SubId).

## Architecture Overview
- **Type**: Data Class
- **Package**: `android.net`
- **Extends**: `NetworkSpecifier`.

## Data Model
-   `mSubId`: `int` (Subscription ID).

## Functionality
-   Matches if `mSubId` equals the other specifier's `mSubId`.
-   Matches `MatchAllNetworkSpecifier`.

## Java-to-C++ Translation Guide
```cpp
class TelephonyNetworkSpecifier : public NetworkSpecifier {
    int subId;
    // ...
};
```
