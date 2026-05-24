# VpnManager.java - Reverse Engineering Documentation

## Executive Summary
`VpnManager` is the app-facing API for managing platform VPNs (IPsec/IKEv2) and interacting with the `VpnManagerService`. It allows apps to provision profiles, start/stop VPNs, and check always-on status.

## Architecture Overview
- **Type**: System Service Manager
- **Package**: `android.net`
- **Service**: `Context.VPN_MANAGEMENT_SERVICE` (`IVpnManager`).

## Key APIs
-   `provisionVpnProfile(PlatformVpnProfile)`: Installs a profile. Returns Intent for user consent if needed.
-   `startProvisionedVpnProfileSession()`: Starts the VPN. Returns session key.
-   `stopProvisionedVpnProfile()`: Stops it.
-   `deleteProvisionedVpnProfile()`: Deletes it.
-   `getProvisionedVpnProfileState()`: Returns current state (Connecting, Connected, Failed).

## Java-to-C++ Translation Guide
Client wrapper around `IVpnManager` AIDL.
