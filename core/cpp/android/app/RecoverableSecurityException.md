# RecoverableSecurityException - Reverse Engineering Documentation

## Executive Summary
`RecoverableSecurityException` is a specialized `SecurityException` that provides information on how a user can recover from a security failure. It includes a user-friendly message and a `RemoteAction` (usually an `Intent`) that the app can launch to resolve the issue (e.g., prompting for a PIN or asking for a specific permission).

## Architecture Overview
- **Inheritance**: Extends `SecurityException`.
- **Core Components**:
    - `mUserMessage`: A localized, short description of the problem for the end user.
    - `mUserAction`: A `RemoteAction` containing the title and `PendingIntent` for recovery.
- **Serialization**: Implements `Parcelable`.

## Detailed Functionality

### Recovery UI
**Purpose**: To provide a standardized way to handle actionable security errors.
**Mechanism**:
- `showAsNotification(Context context, String channelId)`: Creates a system notification with the recovery action.
- `showAsDialog(Activity activity)`: Displays an `AlertDialog` where the positive button triggers the recovery intent.

### Dialog Implementation (`LocalDialog`)
**Purpose**: An internal `DialogFragment` that manages the recovery dialog.
**Logic**: 
1. Retrieves the exception from arguments.
2. Builds an `AlertDialog` with the user message.
3. On "OK", sends the `PendingIntent` from the `RemoteAction`.

## API Reference
- `public CharSequence getUserMessage()`: Gets the localized error text.
- `public RemoteAction getUserAction()`: Gets the recovery action.
- `public void showAsDialog(Activity activity)`: Helper to show the recovery UI.

## Java-to-C++ Translation Guide
- **Exception Class**: Map to a C++ exception class that carries an `android::app::RemoteAction` payload.
- **Parceling**: Ensure the `message`, `userMessage`, and `userAction` are correctly serialized into the `Parcel`.
- **UI Interaction**: In a native environment, recovery logic might involve calling back into a UI framework or using a system-level overlay manager.

## Implementation Risks
- **Legacy Compatibility**: Code that doesn't expect this specific exception might treat it as a generic `SecurityException`, losing the recovery path. C++ callers should explicitly check for this type.
- **PendingIntent Expiration**: The recovery action's `PendingIntent` must be valid and persistent enough for the user to act upon it.
