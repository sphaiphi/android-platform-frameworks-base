# VpnService.java - Reverse Engineering Documentation

## Executive Summary
`VpnService` is a base class for applications implementing custom VPN solutions (non-platform). It provides a `Builder` to configure the `TUN` interface (address, routes, DNS) and methods to protect sockets from being routed through the VPN.

## Architecture Overview
- **Type**: Service / API Class
- **Package**: `android.net`
- **Extends**: `android.app.Service`
- **Service**: Interacts with `IVpnManager` (formerly `IConnectivityManager` for VPNs).

## Key Components

### `VpnService.Builder`
Constructs the `VpnConfig` object.
-   `addAddress`, `addRoute`, `addDnsServer`: Builds network configuration.
-   `establish()`: Calls `mService.establishVpn(config)`. Returns a `ParcelFileDescriptor` to the `TUN` interface.

### `protect()`
-   `protect(Socket)` / `protect(int fd)`: Calls `NetworkUtilsInternal.protectFromVpn(socket)`. This prevents infinite loops by ensuring the VPN tunnel's own traffic bypasses the VPN interface.

### Lifecycle
-   `prepare()`: Checks permissions/consent.
-   `onRevoke()`: Called when VPN is revoked (e.g., another VPN started).

## Java-to-C++ Translation Guide
This is the *provider* side logic.
-   **protect**: Maps to `setsockopt(fd, SOL_SOCKET, SO_MARK, ...)` (setting the FW value to bypass VPN).
-   **establish**: Requires interaction with `netd` or system server to create the `tun` device and configure routing rules.
