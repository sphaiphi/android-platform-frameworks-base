# PendingIntent - Reverse Engineering Documentation

## Executive Summary
`PendingIntent` is a reference to a token maintained by the system that allows another application to perform an action on behalf of your application, with your application's identity and permissions. It acts as a wrapper around an `Intent` that can be triggered at a later time, even if the creating application's process is no longer running. It is fundamental for notifications, alarms, and widget interactions.

## Architecture Overview
- **Key Components**:
    - `mTarget`: The underlying `IIntentSender` (a Binder object) that represents the token.
    - `mCachedInfo`: Locally cached metadata about the intent (creator package, UID, etc.).
    - `CancelListerInfo`: Manages callbacks for when the intent is cancelled.
- **Inheritance**: Implements `Parcelable`.
- **Identity**: Two `PendingIntent` objects are considered equal if their underlying `IIntentSender` tokens match. Intents are matched using `Intent.filterEquals`.

## Detailed Functionality

### Factory Methods (`getActivity`, `getBroadcast`, `getService`, etc.)
**Purpose**: Creates or retrieves a `PendingIntent` for a specific target type.
**Algorithm**:
1. Checks for required mutability flags (`FLAG_IMMUTABLE` or `FLAG_MUTABLE`).
2. Validates against implicit intents if mutable.
3. Prepares the `Intent` for leaving the process (migrating extra streams, etc.).
4. Calls `ActivityManagerService.getIntentSender(...)` to obtain the token.

### Sending (`send`)
**Purpose**: Executes the wrapped `Intent`.
**Mechanism**: Calls `ActivityManager.getService().sendIntentSender(...)`. The invoker can provide an additional `Intent` to merge with the original if it was created with `FLAG_MUTABLE`.

### Cancellation
**Purpose**: Invalidates the token so it can no longer be used.
**Mechanism**: Calls `mTarget.cancel()`. Apps can register `CancelListener` to be notified when this occurs.

### Security and Mutability
- **FLAG_IMMUTABLE**: Prevents the recipient of the `PendingIntent` from modifying the wrapped `Intent`.
- **FLAG_MUTABLE**: Required if the recipient needs to fill in unspecified parts of the intent (e.g., adding a reply string in a notification).
- **UID Tracking**: The system tracks the creator's UID and package to enforce permissions during execution.

## API Reference (Key Methods)
- `public void send()`: Executes the intent.
- `public void cancel()`: Invalidates the intent.
- `public String getCreatorPackage()`: Returns the owning package name.
- `public int getCreatorUid()`: Returns the owning UID.
- `public IntentSender getIntentSender()`: Wraps the token for use in APIs expecting `IntentSender`.

## Java-to-C++ Translation Guide
- **Token Management**: Map `IIntentSender` to the AIDL-generated C++ interface.
- **Parceling**: Implement `writeToParcel` by writing the strong binder of the `IIntentSender`.
- **Equality**: Compare the underlying `IBinder` pointers for `equals` and `hashCode`.
- **Callback Dispatch**: Use `android::os::Handler` or a similar C++ event loop to dispatch `OnFinished` callbacks.

## Implementation Risks
- **Token Leakage**: `PendingIntent` tokens are long-lived in the system server. In C++, ensure that `PendingIntent` objects are not leaked, allowing the system to potentially reclaim resources when no longer referenced.
- **Mutability Risks**: Improper use of `FLAG_MUTABLE` with implicit intents is a major security risk (Intent Hijacking). The C++ implementation must strictly enforce the mutability flag requirements introduced in S+.
- **IPC Failures**: Methods like `getCreatorPackage()` perform IPC. C++ callers should be aware of potential latency or `RemoteException`.
