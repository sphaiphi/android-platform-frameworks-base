# KeyguardManager - Reverse Engineering Documentation

## Executive Summary
`KeyguardManager` provides access to the lock screen state and keyguard features. It allows checking if the device is locked/secure, dismissing the keyguard, and handling credentials (in some contexts).

## Architecture Overview
*   **Dependencies**: `WindowManagerService`, `ActivityManagerService`, `TrustManager`, `NotificationManager`, `LockPatternUtils`.

## Detailed Functionality
*   **State**: `isKeyguardLocked`, `isDeviceLocked`, `isDeviceSecure`.
*   **Dismissal**: `requestDismissKeyguard(Activity, Callback)`. Calls `ActivityClient.dismissKeyguard`.
*   **Lock Management**: `setLock` (for automotive/tests), `createConfirmDeviceCredentialIntent`.
*   **Escrow**: Weak escrow token management (for FBE).

## Java-to-C++ Translation Guide
*   Binder proxy wrapper aggregating multiple services.

## Implementation Risks
*   **Security**: Handling credentials and lock state is sensitive.
