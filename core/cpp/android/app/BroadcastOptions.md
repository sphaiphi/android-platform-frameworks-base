# BroadcastOptions - Reverse Engineering Documentation

## Executive Summary
`BroadcastOptions` is a helper class for building an options Bundle used with `Context.sendBroadcast`. It allows setting temporary power allowlists, targeting specific API levels, and configuring delivery policies (deferral, grouping).

## Architecture Overview
*   **Inheritance**: `ComponentOptions`.
*   **Usage**: Passed as `Bundle` to `sendBroadcast`.

## Detailed Functionality
*   **Power Allowlist**: `setTemporaryAppAllowlist` grants temp power save exemptions to the receiver.
*   **Filtering**: `setMinManifestReceiverApiLevel`, `setMaxManifestReceiverApiLevel`, `setRequireAllOfPermissions`, `setRequireNoneOfPermissions`.
*   **Compatibility**: `setRequireCompatChange`.
*   **Delivery Control**: `setDeliveryGroupPolicy` (merge/most recent), `setDeferralPolicy` (until active).
*   **Interactive**: `setInteractive` (prioritize delivery).

## Java-to-C++ Translation Guide
*   **Parceling**: Serializes to `Bundle`.
*   **Bitmasks**: Uses flags for boolean options.

## Implementation Risks
*   **Privilege Checks**: Many options (like allowlist) require system permissions. C++ implementation (if client side) simply packs the bundle; the enforcement is server-side.
