# SliceManager - Reverse Engineering Documentation

## Executive Summary
`SliceManager` is the high-level system service interface for managing Slices. It handles permissions, pinning (active observation state), and the resolution of Intents to Slice URIs. Crucially, it also acts as a client helper to directly bind (fetch) Slice content from `SliceProvider`s via the ContentResolver framework.

## Architecture Overview
*   **Package**: `android.app.slice`
*   **Type**: System Service (`Context.SLICE_SERVICE`).
*   **Dependencies**:
    *   `ISliceManager` (Binder interface to system_server).
    *   `Context` (for `ContentResolver`, `PackageManager`).
    *   `SliceProvider` (direct interaction via `ContentProviderClient`).

## Detailed Functionality

### 1. Pinning Management
**Purpose**: "Pinning" is a signal that a Slice is being actively displayed by a host (like a Launcher).
**Methods**: `pinSlice(Uri, Set<SliceSpec>)`, `unpinSlice(Uri)`.
**Mechanism**:
*   Calls `mService.pinSlice` / `mService.unpinSlice` via Binder.
*   Requires `IBinder` token to identify the client session.
*   Restricted to default launcher or voice interaction service (enforced by system server).

### 2. Binding Slices (`bindSlice`)
**Purpose**: Retrieves the current `Slice` content for a given Uri or Intent.
**Algorithm**:
1.  **Resolve Uri**: If passed an Intent, calls `mapIntentToUri` first.
2.  **Acquire Provider**: Uses `mContext.getContentResolver().acquireUnstableContentProviderClient(uri)`.
3.  **IPC Call**: Calls `provider.call(SliceProvider.METHOD_SLICE, ...)` passing the Uri and supported Specs.
4.  **Deserialize**: Returns the `Slice` object from the result Bundle.
5.  **Error Handling**: Catches `RemoteException`, returns null.
**Note**: This bypasses `ISliceManager` and talks directly to the app's `SliceProvider`.

### 3. Intent Resolution (`mapIntentToUri`)
**Purpose**: Finds the Slice Uri corresponding to an Intent.
**Algorithm**:
1.  **Static Resolution**:
    *   If Intent has Data and type is `SLICE_TYPE`, return Data.
    *   If Intent matches an Activity with meta-data `android.metadata.SLICE_URI`, return that Uri.
2.  **Dynamic Resolution**:
    *   Find the provider authority for the Intent (using `queryIntentContentProviders` with `CATEGORY_SLICE`).
    *   Connect to provider via `ContentProviderClient`.
    *   Call `provider.call(SliceProvider.METHOD_MAP_ONLY_INTENT, ...)` or `METHOD_MAP_INTENT`.
    *   Provider executes logic to map Intent -> Uri.

### 4. Permission Management
**Methods**: `checkSlicePermission`, `grantSlicePermission`, `revokeSlicePermission`.
**Mechanism**: Proxies calls to `ISliceManager` system service.

## Data Model

### Constants
*   `SLICE_METADATA_KEY`: "android.metadata.SLICE_URI"
*   `CATEGORY_SLICE`: "android.app.slice.category.SLICE"

## API Reference
*   `getInstance(Context)`: Standard system service pattern.
*   `getPinnedSpecs(Uri)`: Returns specs supported by all pinned clients.
*   `getPinnedSlices()`: Returns list of Uris pinned for this app.

## Java-to-C++ Translation Guide

### IPC Strategy
*   **System Server**: Need an `ISliceManager` C++ Bp (proxy) class generated from AIDL.
*   **Content Provider**: Need a mechanism to perform `ContentResolver.call`. In Android native code, this usually involves `IContentProvider`.

### Dependency Injection
The C++ version will need access to a `Context`-like object to get `ContentResolver` and `PackageManager`.

## Implementation Risks
*   **ContentProvider Protocol**: The interaction with `SliceProvider` uses raw Bundle IPC (`provider.call`). The keys (`EXTRA_BIND_URI`, `METHOD_SLICE`) must match exactly.
*   **Thread Safety**: `acquireUnstableContentProviderClient` is a blocking IPC. Should not be called on the main thread (though Java doc implies it's blocking).

## Questions for C++ Team
*   Is there a C++ wrapper for `ContentResolver` and `ContentProviderClient` available?
