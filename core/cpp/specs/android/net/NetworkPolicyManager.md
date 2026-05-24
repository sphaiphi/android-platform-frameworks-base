# NetworkPolicyManager.java - Reverse Engineering Documentation

## Executive Summary
`NetworkPolicyManager` is the public API surface for managing network policies. It interacts with the `NetworkPolicyManagerService` via AIDL (`INetworkPolicyManager`) to enforce data limits, restrict background data (Data Saver), and handle UID-specific rules.

## Architecture Overview
- **Type**: System Service Manager
- **Package**: `android.net`
- **Service**: `Context.NETWORK_POLICY_SERVICE`.
- **Communication**: IPC via `INetworkPolicyManager`.

## Key Concepts

### Policy Flags (Application Level)
-   `POLICY_REJECT_METERED_BACKGROUND`: Restrict background data on metered networks.
-   `POLICY_ALLOW_METERED_BACKGROUND`: Allow background data even if Data Saver is on.

### Rules (UID Level - Computed)
-   `RULE_ALLOW_METERED`: Allowed on metered.
-   `RULE_REJECT_METERED`: Rejected on metered.
-   `RULE_ALLOW_ALL`: Allowed everywhere.
-   `RULE_REJECT_ALL`: Blocked everywhere.

### Restrict Background (Data Saver)
-   Global toggle to restrict background data for all apps unless allowlisted.

## API Reference
-   `setUidPolicy(uid, policy)`: Sets policies for an app.
-   `getUidPolicy(uid)`: Gets current policy.
-   `getRestrictBackground()`: Checks Data Saver status.
-   `registerSubscriptionCallback(...)`: Listens for carrier config changes (limits/overrides).

## Java-to-C++ Translation Guide
This is primarily a client wrapper. A C++ equivalent would wrap the `INetworkPolicyManager` Binder interface.

### Binder Interface
The core logic resides in `INetworkPolicyManager`. C++ clients would use the generated AIDL headers to call:
-   `getUidPolicy(int uid)`
-   `isUidNetworkingBlocked(int uid, boolean metered)`

### Constants
The `POLICY_*` and `RULE_*` constants are critical for interpreting the integer values returned by the service. These should be defined in a shared C++ header (e.g., `NetworkPolicy.h`).
