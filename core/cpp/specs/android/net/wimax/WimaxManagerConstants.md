# WimaxManagerConstants.java - Reverse Engineering Documentation

## Executive Summary
`WimaxManagerConstants` defines the strings and integer constants used by the legacy WiMAX management service. This includes intent actions for state changes, extra keys for broadcasts, and status codes for 4G connectivity.

## Architecture Overview
- **Type**: Constants Definition Class
- **Package**: `android.net.wimax`
- **Scope**: Internal (`@hide`).

## Detailed Functionality

### Intent Actions
-   `NET_4G_STATE_CHANGED_ACTION`: Broadcast for general 4G/WiMAX state.
-   `WIMAX_NETWORK_STATE_CHANGED_ACTION`: Detailed network state changes.
-   `SIGNAL_LEVEL_CHANGED_ACTION`: Signal strength updates.

### Extra Keys
-   `EXTRA_WIMAX_STATUS`
-   `EXTRA_WIMAX_STATE` / `EXTRA_4G_STATE` / `EXTRA_WIMAX_STATE_INT`
-   `EXTRA_NEW_SIGNAL_LEVEL` (0 to 3)

### Status Constants
-   `NET_4G_STATE_DISABLED` (1)
-   `NET_4G_STATE_ENABLED` (3)
-   `WIMAX_STATE_CONNECTED` (7)
-   `WIMAX_STATE_DISCONNECTED` (9)
-   `WIMAX_IDLE` (6)

## Java-to-C++ Translation Guide

### Enum Definition
In C++, these constants should be grouped into strongly-typed enums.

```cpp
namespace android::net::wimax {

enum class WimaxState : int32_t {
    UNKNOWN = 0,
    CONNECTED = 7,
    DISCONNECTED = 9,
    IDLE = 6
};

enum class FourGState : int32_t {
    DISABLED = 1,
    ENABLED = 3,
    UNKNOWN = 4
};

} // namespace android::net::wimax
```

### Considerations
-   WiMAX is a legacy technology and has been largely removed from modern Android devices. These constants are likely maintained for backward compatibility or very specific industrial hardware support.
