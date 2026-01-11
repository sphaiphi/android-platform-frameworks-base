# TapAction - Reverse Engineering Documentation

## Executive Summary
`TapAction` defines the behavior when a user interacts with a UI element. It holds an ID and one of: an `Intent`, a `PendingIntent`, or extra data. It also controls whether the action can bypass the lockscreen.

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Type**: `Parcelable`.

## Detailed Functionality

### Action Definitions
- **Intent**: Direct intent (less common for cross-process secure actions).
- **PendingIntent**: Pre-packaged system token for executing an action as the creator.
- **Extras**: Bundle for custom handling.

### Security
- `mShouldShowOnLockscreen`: Boolean flag. If true, the UI can execute this even if the device is locked.

### Serialization
- Writes ID (CharSequence), Intent, PendingIntent, UserHandle, Extras, Boolean.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mId` | `CharSequence` | Unique ID. |
| `mIntent` | `Intent` | Action intent. |
| `mPendingIntent` | `PendingIntent` | Action pending intent. |
| `mUserHandle` | `UserHandle` | User context. |
| `mExtras` | `Bundle` | Metadata. |
| `mShouldShowOnLockscreen` | `boolean` | Lockscreen visibility. |

## Java-to-C++ Translation Guide
- `CharSequence` -> `String16` / `std::u16string` (support spans if needed, but ID usually doesn't need styling).
- `PendingIntent` / `Intent` -> C++ Parcelable wrappers.

## Test Cases & Validation
- **Validation**: Builder requires at least one of Intent, PendingIntent, or Extras to be non-null.
