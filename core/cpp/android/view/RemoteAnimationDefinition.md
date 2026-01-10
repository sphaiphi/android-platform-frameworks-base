# RemoteAnimationDefinition - Reverse Engineering Documentation

## Executive Summary
`RemoteAnimationDefinition` is a mapping that defines which specific window transitions (e.g., Task Open, Activity Close) should be handled by which `RemoteAnimationAdapter`. It allows an application (like the Launcher) to register interest in multiple types of system-level transitions.

## Architecture Overview
*   **Role**: Transition-to-Adapter registry.
*   **Mapping**: Uses a `SparseArray` where keys are transition types (`TRANSIT_OLD_*`) and values are `RemoteAnimationAdapterEntry` objects.

## Detailed Functionality

### 1. Registration
*   **`addRemoteAnimation()`**: Associates a transition type and an optional `activityTypeFilter` with an adapter.

### 2. Lookup
*   **`getAdapter()`**: Finds the appropriate adapter for a given transition, taking into account the types of activities involved in the move.

### 3. Lifecycle
*   **`linkToDeath()`**: Ensures that if the process managing the animations dies, the system server is notified to clean up the registered transitions.

## Java-to-C++ Translation Guide
*   **Structure**: In C++, use a `std::map<int, RemoteAnimationAdapterEntry>`.
*   **Parcelling**: Serialize the map size followed by the key-value pairs.

## Implementation Risks
*   **Overlapping Filters**: If multiple entries match a transition, the lookup logic must define a consistent "winner" (usually the first match or the most specific filter).
