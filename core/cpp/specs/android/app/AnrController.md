# AnrController - Reverse Engineering Documentation

## Executive Summary
`AnrController` is an interface defined to allow system services (likely `ActivityManagerService`) to delegate control over Application Not Responding (ANR) dialogs. It allows customization of delay and suppression of the ANR UI.

## Architecture Overview
*   **Type**: Interface.
*   **Usage**: Registered with `ActivityManagerInternal`.

## Detailed Functionality

### Delay Management
*   `getAnrDelayMillis(packageName, uid)`: Returns how long to delay the ANR dialog. Used if a controller wants to give an app more time (e.g., if it's undergoing a known heavy operation or debugging).

### Notification
*   `onAnrDelayStarted(packageName, uid)`: Notify controller that delay has started. Controller might show its own progress UI.
*   `onAnrDelayCompleted(packageName, uid)`: Notify delay is over. Returns `true` to show the standard ANR dialog, `false` to cancel it.

## Java-to-C++ Translation Guide
*   Pure virtual class (interface) in C++.
*   Used internally by system server components.

## Implementation Risks
*   **System Server coupling**: This is a system-side internal API, likely not relevant for the client-side framework unless implementing the system server itself.
