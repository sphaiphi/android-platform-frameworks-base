# RestrictionsReceiver - Reverse Engineering Documentation

## Executive Summary
`RestrictionsReceiver` is an abstract `BroadcastReceiver` that serves as the base for implementing a **Restrictions Provider**. It is part of the managed configuration framework, allowing an administrator (local or remote) to approve or deny sensitive operations requested by applications.

## Architecture Overview
*   **Inheritance**: Extends `android.content.BroadcastReceiver`.
*   **Role**: Acts as a bridge between a local application requesting permission and an administrative authority.
*   **Registration**: A device owner or profile owner app registers this component via `DevicePolicyManager.setRestrictionsProvider`.
*   **Communication**:
    1.  Apps initiate requests via `RestrictionsManager.requestPermission`.
    2.  The system broadcasts `ACTION_REQUEST_PERMISSION`.
    3.  `RestrictionsReceiver` handles the broadcast and calls `onRequestPermission`.
    4.  The provider delivers the response later via `RestrictionsManager.notifyPermissionResponse`.

## Detailed Functionality

### `onReceive(Context, Intent)`
**Purpose**: Intercepts the system broadcast and extracts request parameters.
**Algorithm**:
1.  Verifies the action is `RestrictionsManager.ACTION_REQUEST_PERMISSION`.
2.  Extracts `EXTRA_PACKAGE_NAME`, `EXTRA_REQUEST_TYPE`, `EXTRA_REQUEST_ID`, and `EXTRA_REQUEST_BUNDLE`.
3.  Invokes `onRequestPermission`.

### `onRequestPermission` (Abstract)
**Purpose**: The main entry point for processing a permission request.
**Parameters**:
*   `packageName`: The app making the request.
*   `requestType`: Determines the context (e.g., `REQUEST_TYPE_APPROVAL`).
*   `requestId`: Unique ID for tracking this specific request.
*   `request`: A `PersistableBundle` containing request details.
**Requirements**: The implementation must transport this request to the administrator and handle the asynchronous response.

## API Reference

### Constants
*   `RestrictionsManager.ACTION_REQUEST_PERMISSION`: `"android.content.action.REQUEST_PERMISSION"`

## Java-to-C++ Translation Guide

### Component Type
*   **Java**: `BroadcastReceiver`.
*   **C++**: Receivers are usually handled in the system server's `BroadcastQueue`. A C++ implementation of a restrictions provider would likely be a system service that registers for these broadcasts via the `ActivityManager` binder interface.

### Data Model
*   `PersistableBundle` is used for request data, mapping to `android::os::PersistableBundle` in C++.

## Implementation Risks
*   **Latency**: Permission responses can take an indefinite amount of time (waiting for a parent/admin to see a notification). Providers must handle timeouts and persistence of pending requests.
*   **Security**: The provider is a trusted component. It must ensure that responses are authentic and not forged.
