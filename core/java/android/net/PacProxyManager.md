# PacProxyManager.java - Reverse Engineering Documentation

## Executive Summary
`PacProxyManager` manages the Proxy Auto-Config (PAC) system. It interacts with the `PacProxyService` to set PAC scripts and listen for proxy installation events.

## Architecture Overview
- **Type**: System Service Manager
- **Package**: `android.net`
- **Service**: `Context.PAC_PROXY_SERVICE`.

## Functionality
-   `setCurrentProxyScriptUrl(ProxyInfo)`: Updates the PAC script.
-   `addPacProxyInstalledListener(...)`: Registers a callback (`IPacProxyInstalledListener`) to receive updates when the PAC proxy is ready.

## Java-to-C++ Translation Guide
Client wrapper around `IPacProxyManager`.
