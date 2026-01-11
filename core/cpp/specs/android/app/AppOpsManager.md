# AppOpsManager - Reverse Engineering Documentation

## Executive Summary
`AppOpsManager` provides an API for tracking and controlling application operations (AppOps) such as location access, camera usage, and background execution. It supports both permission-style access control and silent tracking (noting).

## Architecture Overview
*   **Pattern**: Service Wrapper.
*   **Service**: `IAppOpsService`.
*   **Dependencies**: `Context` (for package name/attribution tag).

## Detailed Functionality

### Operations
*   `checkOp`: Checks if an operation is allowed (snapshot).
*   `noteOp`: Checks and records the operation execution (access accounting).
*   `startOp` / `finishOp`: Tracks long-running operations (e.g., audio recording).

### Modes
*   `MODE_ALLOWED`: Allowed.
*   `MODE_IGNORED`: Silently denied (app should degrade gracefully).
*   `MODE_ERRORED`: Throw SecurityException.
*   `MODE_DEFAULT`: Use default permission check.

### Monitoring
*   `startWatchingMode`: Listen for mode changes (e.g., user toggles permission in Settings).
*   `OnOpNotedCallback`: Callback for async notes (data auditing).

## Java-to-C++ Translation Guide
*   Binder proxy.
*   Enums/Constants for all `OP_` codes.

## Implementation Risks
*   **Sync vs Async**: `noteOp` can be synchronous (Binder call). High frequency calls can affect performance.
