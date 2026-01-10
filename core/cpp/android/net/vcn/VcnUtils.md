# VcnUtils.java - Reverse Engineering Documentation

## Executive Summary
`VcnUtils` is a utility class for Virtual Carrier Network (VCN) callers to retrieve information about the underlying networks supporting a VCN connection. It helps extract Wi-Fi details or Telephony Subscription IDs from `NetworkCapabilities`.

## Architecture Overview
- **Type**: Static Utility Class
- **Package**: `android.net.vcn`
- **Scope**: Internal (`@hide`).

## Detailed Functionality

### Core Responsibilities
1.  **Transport Identification**: Identifies if a given set of `NetworkCapabilities` belongs to a VCN network by checking for `VcnTransportInfo`.
2.  **Underlying Network Extraction**: VCN networks wrap an underlying physical network (Wi-Fi or Cell). This utility extracts the capabilities of that underlying link.
3.  **Wi-Fi Info Retrieval**: `getWifiInfoFromVcnCaps` extracts `WifiInfo` from the underlying Wi-Fi network of a VCN.
4.  **SubId Retrieval**: `getSubIdFromVcnCaps` extracts the cellular Subscription ID from the underlying telephony network of a VCN.

### Logic Flow
-   Check `caps.getTransportInfo()` for `VcnTransportInfo`.
-   Call `caps.getUnderlyingNetworks()`.
-   Take the first underlying network (as of Android 16, VCN only has one).
-   Query `ConnectivityManager` for the capabilities of that underlying network.
-   Cast the `TransportInfo` (for Wi-Fi) or `NetworkSpecifier` (for Cell) to the appropriate type.

## Java-to-C++ Translation Guide

### Data Mapping
-   **VcnTransportInfo**: Needs a C++ equivalent class/struct.
-   **ConnectivityManager**: Use the C++ Binder client for `IConnectivityManager`.

### Implementation Sketch
```cpp
class VcnUtils {
public:
    static std::optional<int32_t> getSubId(IConnectivityManager& cm, const NetworkCapabilities& caps) {
        if (!isVcn(caps)) return std::nullopt;
        auto underlying = caps.getUnderlyingNetworks();
        if (underlying.empty()) return std::nullopt;
        
        auto underlyingCaps = cm.getNetworkCapabilities(underlying[0]);
        auto specifier = underlyingCaps.getNetworkSpecifier();
        // check for TelephonyNetworkSpecifier
    }
};
```

## Key Considerations
-   **Dependency**: This utility is highly coupled with `ConnectivityManager`. In C++, ensure the service is available and permissions are handled.
-   **Future-proofing**: The Java code notes that VCN might support multiple underlying networks in the future, but currently only handles the first one.
