# FeatureFlags - Reverse Engineering Documentation

## Executive Summary
`FeatureFlags` is the central manager (Singleton) for querying and synchronizing feature flags in the Android framework. It handles the communication with the `FeatureFlagsService`.

## Architecture Overview
- **Pattern**: Singleton (`getInstance()`).
- **Dependencies**: `IFeatureFlags` (Binder IPC).
- **Threading**: Synchronized access to flag sets.

## Detailed Functionality

### Core Operations
- **`booleanFlag(...)`**: Factory method for stable boolean flags.
- **`dynamicBooleanFlag(...)`**: Factory method for dynamic boolean flags.
- **`fusedOff/OnFlag(...)`**: Factory methods for constant flags.
- **`isEnabled(BooleanFlag)`**: Returns the effective value of a flag.

### Synchronization Logic
- **`sync()`**: Syncs dirty (newly registered) flags with the system service.
- **`syncInternal`**: Calls `mIFeatureFlags.syncFlags()`. Updates local overrides map based on server response.
- **Caching**: Flag values are cached in `mBooleanOverrides` map.

### Dynamic Updates
- **Callback**: `mIFeatureFlagsCallback` listens for `onFlagChange` events from the system server.
- **Dispatch**: Updates the internal map and notifies local `ChangeListener`s.

## Data Model
- `mKnownFlags`: Set of all registered flags.
- `mDirtyFlags`: Set of flags registered but not yet synced with service.
- `mBooleanOverrides`: Nested Map `[Namespace -> [FlagName -> Value]]`.

## Java-to-C++ Translation Guide
- **Singleton**: Standard C++ Singleton.
- **IPC**: Wraps `IFeatureFlags` Bp class.
- **Synchronization**: Need `std::mutex` for thread safety on the maps.
- **Callback**: Implement `BnFeatureFlagsCallback`.

## Source Reference
Defined in `FeatureFlags.java`.
