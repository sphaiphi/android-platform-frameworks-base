# OnBackInvokedCallbackInfo - Reverse Engineering Documentation

## Executive Summary
`OnBackInvokedCallbackInfo` is a Parcelable DTO that pairs an `IOnBackInvokedCallback` (binder) with its registration priority and metadata (whether it's an animation callback).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: DTO for registering callbacks with WindowManager.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mCallback` | `IOnBackInvokedCallback` | The binder interface for the callback. |
| `mPriority` | `int` | Priority level (Overlay, Default, System). |
| `mIsAnimationCallback` | `boolean` | True if the callback handles animation events. |
| `mOverrideBehavior` | `int` | Override behavior type. |

## Detailed Functionality

### `isSystemCallback()`
Returns true if priority is `PRIORITY_SYSTEM` or if `overrideBehavior` is set.

## Java-to-C++ Translation Guide

### Data Types
*   `IOnBackInvokedCallback` -> `sp<IOnBackInvokedCallback>`.

### Parceling
*   **Write**:
    1.  `mCallback` (StrongInterface)
    2.  `mPriority`
    3.  `mIsAnimationCallback`
    4.  `mOverrideBehavior`

## Implementation Risks
*   None.
