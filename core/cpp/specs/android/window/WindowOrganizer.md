# WindowOrganizer - Reverse Engineering Documentation

## Executive Summary
`WindowOrganizer` is the base class for all components that perform organizational tasks on windows (Tasks, DisplayAreas, TaskFragments). it provides the core API for applying transactions and managing transitions through the `IWindowOrganizerController`.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Base)
*   **Role**: Hierarchy Command Proxy.
*   **Key Interfaces**: `IWindowOrganizerController`.

## Detailed Functionality

### Transaction API
*   `applyTransaction(WindowContainerTransaction)`: Applies a batch of operations.
*   `applySyncTransaction(WCT, WindowContainerTransactionCallback)`: Applies changes and waits for the resulting `SurfaceControl` transaction.

### Transition API
*   `startNewTransition(...)`: Requests a new system transition.
*   `startTransition(...)`: Initiates an existing transition.
*   `finishTransition(...)`: Marks a transition as complete.

### Metric Reporting
*   `getTransitionMetricsReporter()`: Returns the binder interface for metrics.

## Java-to-C++ Translation Guide

### Singleton
*   Holds a singleton handle to `IWindowOrganizerController`.

### Binder
*   Requires mapping Java `RemoteException` to C++ `status_t` or equivalent binder error codes.

## Implementation Risks
*   **Permission**: Most methods require `MANAGE_ACTIVITY_TASKS`.
