# IFeatureFlags - Reverse Engineering Documentation

## Executive Summary
`IFeatureFlags` is the AIDL interface for the `FeatureFlagsService`.

## API Reference
- **`syncFlags`**: Bulk exchange of flag definitions and values.
- **`registerCallback`**: Subscribe to dynamic flag updates.
- **`unregisterCallback`**: Unsubscribe.
- **`queryFlags`**: Read-only query (for debug tools).
- **`overrideFlag`**: Force a value (debug).
- **`resetFlag`**: Clear overrides (debug).

## Java-to-C++ Translation Guide
- **IPC**: AIDL interface.

## Source Reference
Defined in `IFeatureFlags.aidl`.
