# PacProxySelector.java - Reverse Engineering Documentation

## Executive Summary
`PacProxySelector` is a specific implementation of `java.net.ProxySelector` that delegates proxy resolution to the system `IProxyService`. It handles PAC file resolution via the system service.

## Architecture Overview
- **Type**: `java.net.ProxySelector` Implementation
- **Package**: `android.net`
- **Dependencies**: `IProxyService`.

## Detailed Functionality
-   **Selection**: In `select(URI)`, it calls `mProxyService.resolvePacFile(host, url)`.
-   **Parsing**: Parses the string response from the service (e.g., "PROXY host:port; SOCKS host:port; DIRECT") into a list of `java.net.Proxy` objects.
-   **Fallback**: Returns `NO_PROXY` (Direct) if service is unavailable or returns "DIRECT".

## Java-to-C++ Translation Guide
-   **Logic**: The parsing logic ("PROXY host:port", "SOCKS", etc.) logic is reusable.
-   **Dependencies**: Requires a C++ binder client for `IProxyService`.
