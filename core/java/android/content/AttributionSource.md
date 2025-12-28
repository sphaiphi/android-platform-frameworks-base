# AttributionSource - Reverse Engineering Documentation

## Executive Summary
`AttributionSource` represents the identity of an app (or a chain of apps) for permission enforcement and data access attribution. It encapsulates UID, package name, attribution tag, and a token. It supports chaining to represent proxy access (App A acting on behalf of App B).

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Relationship:** Used in `Context`, `ContentProvider`, and permission checks (`PermissionChecker`).
- **Pattern:** Immutable Value Object / Builder Pattern.

## Detailed Functionality

### `AttributionSource(uid, packageName, attributionTag, ...)` (Constructors)
**Purpose**: Initializes the state.
**Algorithm**: Stores values in `mAttributionSourceState` (a raw Parcelable holder). Validates UID/PID when unparceled from Binder.

### `enforceCallingUid() / checkCallingUid()`
**Purpose**: Validates that the `AttributionSource` matches the current IPC caller.
**Algorithm**: Compares `Binder.getCallingUid()` with the stored UID.

### `checkCallingPid()`
**Purpose**: Validates PID.
**Note**: PID check is skipped for oneway Binder calls (where calling PID is 0).

### `myAttributionSource()` (Static)
**Purpose**: Returns the `AttributionSource` for the current process.
**Algorithm**: Fetches from `ActivityThread.currentAttributionSource()` or builds one using `Process.myUid()`.

### `ScopedParcelState` (Inner Class)
**Purpose**: Optimized way to pass `AttributionSource` to native code without marshalling/unmarshalling through JNI boundaries manually. It flattens the object into a `Parcel` immediately.

## Data Model
- `mAttributionSourceState`: `AttributionSourceState` - Holds the actual data (AIDL generated).
    - `uid`: `int`
    - `packageName`: `String`
    - `attributionTag`: `String`
    - `token`: `IBinder`
    - `next`: `AttributionSourceState[]` (Chain)

## API Reference
- `public int getUid()`
- `public String getPackageName()`
- `public String getAttributionTag()`
- `public AttributionSource getNext()`
- `public void enforceCallingUid()`
- `public boolean isTrusted(Context context)`

## Java-to-C++ Translation Guide
- **Parcelable**: Directly maps to Android's C++ Binder/Parcelable implementation.
- **Binder Identity**: `Binder.getCallingUid()` maps to `IPCThreadState::self()->getCallingUid()`.
- **Immutability**: The class is `@Immutable`. C++ implementation should use `const` fields or getters.

## Implementation Risks
- **Security**: This class is central to permission checks ("Blame"). Spoofing an `AttributionSource` allows an app to bypass checks or blame others. The `enforceCallingUid` checks are critical.
- **Chaining**: Handling the `next` pointer (chaining) correctly during marshaling/unmarshaling to avoid infinite loops or excessive depth.
