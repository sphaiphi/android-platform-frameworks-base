# InterfaceConfiguration.java - Reverse Engineering Documentation

## Executive Summary
`InterfaceConfiguration` is a Parcelable class used to retrieve and set the configuration of a network interface (link). It handles hardware address (MAC), IP address (LinkAddress), and interface flags (Up, Down, etc.).

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`
- **Dependencies**: `android.net.LinkAddress`.
- **Usage**: Typically used with `INetworkManagementService` (netd) to configure interfaces.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mHwAddr` | `String` | Hardware MAC address (e.g., "00:11:22:33:44:55"). |
| `mAddr` | `LinkAddress` | IP address and prefix length. |
| `mFlags` | `HashSet<String>` | Set of string flags (e.g., "up", "down", "broadcast", "multicast"). |

## API Reference

### Configuration Methods
-   `setHardwareAddress(String)` / `getHardwareAddress()`
-   `setLinkAddress(LinkAddress)` / `getLinkAddress()`
-   `setFlag(String)` / `clearFlag(String)` / `hasFlag(String)`
-   `setInterfaceUp()`: Removes "down", adds "up".
-   `setInterfaceDown()`: Removes "up", adds "down".
-   `ignoreInterfaceUpDownStatus()`: Clears both "up" and "down" (used when updating other props without changing state).

### Logic
-   `isActive()`: Checks if interface is "up" AND has a non-zero IP address (valid octets).

### Parcelable
-   Standard serialization: HwAddr -> HasAddr(byte) -> Addr -> FlagCount -> Flags...

## Java-to-C++ Translation Guide

### Class Definition
```cpp
class InterfaceConfiguration {
public:
    std::string hwAddr;
    LinkAddress addr; // Assuming LinkAddress C++ equivalent exists
    std::unordered_set<std::string> flags;

    void setInterfaceUp();
    void setInterfaceDown();
    bool isActive() const;
    // serialization methods...
};
```

### Flags
Legacy behavior uses string flags ("up", "down"). In C++ interaction with kernel/netd, these map to `IFF_UP`, `IFF_DOWN` (from `net/if.h`) bitmasks. The Java class is an abstraction layer that converts these to/from strings for the AIDL interface.

### Active Check
The `isActive` check iterates bytes of the IP address. In C++, check `in_addr` or `in6_addr` for non-zero.

## Implementation Risks
-   **Flag Validation**: The Java code validates flags don't contain spaces. C++ should enforce similar or stricter rules if these strings are passed to shell commands (though `netd` usually handles this via native calls now).
-   **Concurrency**: `HashSet` is not thread-safe.
