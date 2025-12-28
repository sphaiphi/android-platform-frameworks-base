# IntentSender - Reverse Engineering Documentation

## Executive Summary
`IntentSender` is a reference to a token maintained by the system (specifically `ActivityManager`) that describes an Intent and a target action to perform with it. It allows a foreign application to perform an action as if it were the creating application (with the creator's permissions and identity). It is the core of `PendingIntent`.

## Architecture Overview
-   **Inheritance:** Implements `Parcelable`.
-   **Relationship:** Created via `PendingIntent.getIntentSender()`. Wraps `IIntentSender` (Binder token).

## Detailed Functionality
-   **`sendIntent`**: Performs the operation.
-   **Equality**: Based on the underlying `IIntentSender` binder token.

## Data Model
-   `mTarget`: `IIntentSender` (Binder).
-   `mWhitelistToken`: `IBinder`.
-   `mCachedInfo`: `PendingIntentInfo` (Cached metadata).

## API Reference
-   `public void sendIntent(Context context, int code, Intent intent, OnFinished onFinished, Handler handler)`
-   `public String getCreatorPackage()`
-   `public int getCreatorUid()`

## Java-to-C++ Translation Guide
-   **Binder**: Wraps `IIntentSender` (AIDL).
-   **Identity**: The token represents the identity. C++ implementation should manage the `sp<IIntentSender>`.

## Implementation Risks
-   **Security**: `IntentSender` allows impersonation (by design). Passing it to an untrusted app allows that app to execute the intent as you.
