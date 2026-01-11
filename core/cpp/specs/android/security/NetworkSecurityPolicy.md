# NetworkSecurityPolicy - Reverse Engineering Documentation

## Executive Summary
`NetworkSecurityPolicy` is a singleton class that manages network security configurations for the process. It controls whether cleartext (non-TLS) traffic is permitted and if Certificate Transparency (CT) is required.

## Architecture Overview
*   **Package**: `android.security`
*   **Type**: Class (Public, Singleton)
*   **Backing Implementation**: Delegates to `libcore.net.NetworkSecurityPolicy`.
*   **Extension**: `OverlayNetworkSecurityPolicy` is used to override settings dynamically.

## Detailed Functionality

### 1. Cleartext Traffic Policy
*   **Method**: `isCleartextTrafficPermitted()`
*   **Purpose**: Checks if the process allows unencrypted HTTP/FTP/etc.
*   **Default**: Typically true, but configured via manifest or `NetworkSecurityConfig`.
*   **Granularity**: Can be queried per hostname: `isCleartextTrafficPermitted(String hostname)`.

### 2. Policy Modification
*   **Method**: `setCleartextTrafficPermitted(boolean permitted)`
*   **Usage**: Used by the platform during app initialization.
*   **Mechanism**:
    *   Gets the current `libcore` policy.
    *   Wraps it in `OverlayNetworkSecurityPolicy` with the new boolean flag.
    *   Sets the new instance as the global `libcore` policy.

### 3. Certificate Transparency
*   **Method**: `isCertificateTransparencyVerificationRequired(String hostname)`
*   **Purpose**: Determines if CT checks are mandatory for a host.
*   **Dependency**: Relies on `Flags.FLAG_CERTIFICATE_TRANSPARENCY_CONFIGURATION`.

### 4. Application Config Handling
*   **Method**: `getApplicationConfigForPackage`
*   **Purpose**: Loads `ApplicationConfig` for a specific package.
*   **Logic**: Creates a `ManifestConfigSource` from the package's context.

## API Reference
*   `static NetworkSecurityPolicy getInstance()`
*   `boolean isCleartextTrafficPermitted()`
*   `boolean isCleartextTrafficPermitted(String hostname)`
*   `void setCleartextTrafficPermitted(boolean permitted)` (Hidden)
*   `void handleTrustStorageUpdate()` (Hidden)

## Java-to-C++ Translation Guide
*   **Singleton**: Use `static` instance or singleton pattern in C++.
*   **Delegation**: This class is largely a wrapper around `libcore` functionality. In the Android C++ framework, equivalent checks might consult `libnetwork` or netd configuration.
*   **Flag Handling**: Check `aconfig` flags for CT verification logic.
