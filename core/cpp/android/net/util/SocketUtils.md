# SocketUtils.java - Reverse Engineering Documentation

## Executive Summary
`SocketUtils` provides a set of low-level utilities for interacting with raw sockets, Netlink sockets, and packet sockets on Android. It facilitates binding sockets to specific interfaces, creating specialized socket addresses, and managing socket lifecycles.

## Architecture Overview
- **Type**: Static Utility Class
- **Package**: `android.net.util`
- **Scope**: System API (`@SystemApi`).

## Detailed Functionality

### Interface Binding
-   **`bindSocketToInterface(FileDescriptor, String)`**:
    -   Uses `Os.setsockoptIfreq` with `SO_BINDTODEVICE` to lock a socket to a specific network interface (e.g., "wlan0").
    -   Calls `NetworkUtilsInternal.protectFromVpn(socket)` to ensure traffic on this socket ignores system-wide VPNs. This is critical for low-level networking logic (like DHCP or connectivity probing) that must occur on the physical link.

### Socket Address Factories
-   **Netlink**: `makeNetlinkSocketAddress(portId, groupsMask)` creates a `NetlinkSocketAddress`.
-   **Packet Sockets**: `makePacketSocketAddress` creates a `PacketSocketAddress` (used for `AF_PACKET`).
    -   Can specify protocol (`ETH_P_IP`, etc.), interface index, and hardware (MAC) address.

### Lifecycle
-   **`closeSocket(FileDescriptor)`**: Calls `IoBridge.closeAndSignalBlockedThreads`. This ensures that any threads currently blocked on I/O for this socket are unblocked/signaled during closure.

## Java-to-C++ Translation Guide

### Binding
In C++, this maps to standard socket API:
```cpp
struct ifreq ifr;
memset(&ifr, 0, sizeof(ifr));
strncpy(ifr.ifr_name, iface.c_str(), sizeof(ifr.ifr_name) - 1);
setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof(ifr));
```

### Packet Socket Address
Populating `sockaddr_ll` (Linux standard):
```cpp
struct sockaddr_ll sll;
memset(&sll, 0, sizeof(sll));
sll.sll_family = AF_PACKET;
sll.sll_ifindex = ifIndex;
sll.sll_protocol = htons(protocol);
if (hwAddr) {
    sll.sll_halen = 6;
    memcpy(sll.sll_addr, hwAddr, 6);
}
```

## Key Considerations
-   **VPN Protection**: The "protect from VPN" logic in Android often involves `setsockopt` with `SO_MARK` or similar. In C++, ensure the socket mark is set to a value that bypasses the specific routing tables used for VPNs if this logic is being replicated.
-   **Signal Blocked Threads**: C++ `close(fd)` does not automatically signal other threads. If this behavior is needed, use `shutdown(fd, SHUT_RDWR)` before closing or use a synchronization primitive (like an eventfd or pipe) to signal I/O loops to exit.
