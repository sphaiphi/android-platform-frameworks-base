# VpnConfig - Reverse Engineering Documentation

## Executive Summary
`VpnConfig` is an internal container class used to aggregate the configuration parameters for a VPN connection. It is used by `VpnBuilder`, `VpnDialogs`, and the system's `Vpn` management logic to pass networking details (IPs, routes, DNS) and policy rules (allowed/disallowed apps) between the UI and the connectivity service.

## Architecture Overview
- **Type**: Internal Data Container.
- **Package**: `com.android.internal.net`.
- **Usage**: Encapsulates both legacy (Settings-based) and modern (`VpnService`) VPN configurations.
- **IPC**: Implements `Parcelable` for transfer across Binder.

## Detailed Functionality

### Networking Configuration
**Purpose**: To define the tunnel parameters.
- `addresses`: List of `LinkAddress` for the virtual interface.
- `routes`: List of `RouteInfo` to be directed through the tunnel.
- `dnsServers`: IP addresses of DNS resolvers.
- `mtu`: Maximum Transmission Unit for the tunnel.

### Traffic Policy
**Purpose**: To implement Split Tunneling.
- `allowedApplications`: Only these apps' traffic goes through the VPN.
- `disallowedApplications`: All apps EXCEPT these go through the VPN.

### Security and UI
- `user`: The system user ID owning the VPN.
- `interfaze`: The name of the TUN interface (e.g., `tun0`).
- `configureIntent`: A `PendingIntent` to launch the VPN's settings UI.
- `allowBypass`: If true, allows apps to bypass the VPN and use the underlying network directly.

## Data Model

### Members
- `user` (`String`)
- `interfaze` (`String`)
- `session` (`String`): User-visible name of the VPN session.
- `mtu` (`int`)
- `startTime` (`long`): Timestamp when the VPN was established.
- `legacy` (`boolean`): True if this is a system-configured legacy VPN.
- `blocking` (`boolean`): If true, blocks all traffic when VPN is down.

## API Reference (Internal)

### Key Methods
- `getIntentForConfirmation()`: Returns the intent for the system VPN consent dialog.
- `getVpnLabel(Context, String)`: Utility to get the user-friendly name of a VPN provider.
- `addLegacyRoutes(String)`: Helper to parse space-separated route strings.

## Java-to-C++ Translation Guide

### Data Mapping
- **Java**: `List<LinkAddress>`, `List<RouteInfo>`.
- **C++**: Use `std::vector<std::string>` or native `android::net::LinkAddress` equivalents from the `netd` client library.

### Policy Enforcement
- **Java**: `List<String> allowedApplications`.
- **C++**: In C++, these policies are often pushed down to `netd` as UID range rules in the routing tables (IP Rules).

## Test Cases & Validation
1. **App Filtering**: Verify that adding a package name to `allowedApplications` results in that app's UID being correctly routed to the `tun` interface while others remain on `wlan0`.
2. **MTU Clamping**: Ensure that the `mtu` set in the config is reflected on the physical `tun` interface via `ifconfig` or `ip link`.
3. **Parceling Integrity**: Verify that a complex config with 50+ routes survives a round-trip through `writeToParcel`/`createFromParcel`.

## Implementation Risks
- **Permission Mapping**: `VpnConfig` uses package names for app filtering, but the kernel uses UIDs. The system service must handle UID changes (app reinstall) correctly.
- **Route Conflicts**: Overlapping routes in the config must be prioritized or merged to avoid kernel routing errors.
