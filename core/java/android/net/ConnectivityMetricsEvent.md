# ConnectivityMetricsEvent.java - Reverse Engineering Documentation

## Executive Summary
`ConnectivityMetricsEvent` is a data class used to transport core networking events collected by the `IpConnectivityLog` to the `ConnectivityMetrics` service. It encapsulates a timestamp, network ID, interface name, transport types, and opaque event-specific data.

## Architecture Overview
- **Type**: POJO / `Parcelable`
- **Package**: `android.net`
- **Role**: Data carrier for metrics events.
- **Dependencies**: `android.os.Parcelable`, `android.os.Parcel`.

## Detailed Functionality
The class serves as a container for logging events. It does not contain business logic other than serialization.

### Fields
| Field | Type | Description |
| :--- | :--- | :--- |
| `timestamp` | `long` | Timestamp of collection (System.currentTimeMillis()). |
| `transports` | `long` | Bitmask of transports (from `NetworkCapabilities`). |
| `netId` | `int` | Network ID (0 if unspecified). |
| `ifname` | `String` | Interface name (e.g., "wlan0"). |
| `data` | `Parcelable` | Opaque event data (subclasses of `IpConnectivityLog.Event`). |

## Java-to-C++ Translation Guide
This class corresponds to `android.net.ConnectivityMetricsEvent` in AIDL.

### C++ Definition
```cpp
// Corresponding AIDL-generated C++ struct or custom struct
struct ConnectivityMetricsEvent {
    int64_t timestamp;
    int64_t transports;
    int32_t netId;
    std::string ifname;
    // 'data' is polymorphic. In C++, this might be a std::variant or a parcelable holder.
    // Given the AIDL usage, it likely maps to android::os::Parcelable or a specific union.
};
```

### Serialization
- Follows standard Parcelable pattern:
    1. `timestamp` (long)
    2. `transports` (long)
    3. `netId` (int)
    4. `ifname` (String)
    5. `data` (Parcelable)
