# BroadcastReceiver - Reverse Engineering Documentation

## Executive Summary
`BroadcastReceiver` is a base class for components that listen for and react to broadcast Intents. It receives events sent via `Context.sendBroadcast` and related methods. It supports both synchronous and asynchronous (`goAsync`) execution modes.

## Architecture Overview
- **Inheritance:** Abstract class.
- **Relationship:** Registered via `AndroidManifest.xml` or `Context.registerReceiver`.
- **Key Inner Class:** `PendingResult` - Represents the state of an active broadcast handling, allowing asynchronous processing.

## Detailed Functionality

### `onReceive(Context, Intent)` (Abstract)
**Purpose**: Called when a broadcast is received.
**Thread**: Main thread (by default).

### `goAsync()`
**Purpose**: Allows the receiver to finish processing on a background thread.
**Algorithm**:
1. Returns the `mPendingResult` object.
2. Clears `mPendingResult` from the receiver (so the system knows the receiver is "done" synchronously but the result is kept alive).
3. Caller must call `PendingResult.finish()` later.

### `PendingResult` (Inner Class)
**Purpose**: Holds result code, data, extras, and abort state for ordered broadcasts.
**Functionality**:
- `setResultCode`, `setResultData`, `setResultExtras`: Update result values.
- `abortBroadcast`: Stops propagation of an ordered broadcast.
- `finish()`: Signals to `ActivityManager` that the broadcast handling is complete.

## Data Model
- `mPendingResult`: `PendingResult` - Valid only during `onReceive`.
- `mDebugUnregister`: `boolean` - Debug flag.

## API Reference
- `public abstract void onReceive(Context context, Intent intent)`
- `public final PendingResult goAsync()`
- `public final void setResultCode(int code)`
- `public final void abortBroadcast()`

## Java-to-C++ Translation Guide
- **Component Lifecycle**: In Java, instances might be ephemeral (manifest-registered) or long-lived (dynamic). C++ implementation depends on how the framework manages object lifetimes.
- **Binder**: `PendingResult` holds an `IBinder` token to communicate back to the system (`IActivityManager`). This uses standard Binder IPC.

## Implementation Risks
- **ANRs**: `onReceive` blocks the main thread. `goAsync` prevents this but the system still imposes a hard timeout (10s/30s).
- **Thread Safety**: `PendingResult` is not thread-safe itself but intended to be passed to another thread.
