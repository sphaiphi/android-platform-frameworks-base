# OverlayNetworkSecurityPolicy - Reverse Engineering Documentation

## Executive Summary
`OverlayNetworkSecurityPolicy` is an internal helper class that extends `libcore.net.NetworkSecurityPolicy`. It wraps an existing policy and overrides the "Cleartext Traffic Permitted" setting.

## Architecture Overview
*   **Package**: `android.security`
*   **Type**: Class (Hidden)
*   **Parent**: `libcore.net.NetworkSecurityPolicy`

## Functionality
*   **Constructor**: Takes a parent policy and a boolean `cleartextTrafficPermitted`.
*   **Override**: `isCleartextTrafficPermitted()` returns the boolean provided at construction.
*   **Delegation**: All other methods (like `isCertificateTransparencyVerificationRequired`) delegate to the parent policy.

## Java-to-C++ Translation Guide
*   This pattern (decorator/proxy) can be implemented in C++ if the Network Security Policy logic is mirrored there.
*   It serves to dynamically update the policy state without replacing the entire logic engine.
