# AppCompatCallbacks - Reverse Engineering Documentation

## Executive Summary
`AppCompatCallbacks` serves as the app-process implementation of the `Compatibility` API (specifically `BehaviorChangeDelegate`). It is responsible for reporting and querying the state of app compatibility changes (feature flags/gates for backward compatibility).

## Architecture Overview
*   **Role**: Delegate implementation.
*   **Key Dependencies**: `ChangeReporter` (internal), `Compatibility` (public API facade).

## Detailed Functionality

### Installation
*   `install(long[] disabledChanges, long[] loggableChanges)`: Static method to initialize the singleton delegate. It takes lists of change IDs that are disabled or loggable.

### Change Reporting
*   `onChangeReported(long changeId)`: Logs that a compatibility change was accessed/used. Uses `ChangeReporter` to send data to system stats.

### Change Querying
*   `isChangeEnabled(long changeId)`: Checks if a specific change ID is enabled.
    *   Logic: Returns `true` if the ID is *not* in the `mDisabledChanges` array.
    *   Side Effect: Reports the access via `reportChange`.

## Data Model
*   `mDisabledChanges`: Sorted `long[]` of disabled change IDs.
*   `mLoggableChanges`: Sorted `long[]` of loggable change IDs.

## Java-to-C++ Translation Guide
*   **Bitsets/Arrays**: Efficient storage for change IDs. `std::vector<int64_t>` or sorted array for binary search.
*   **Singleton/Static Global**: Needs a mechanism to set the process-wide delegate.

## Implementation Risks
*   **Performance**: `isChangeEnabled` is hot-path. Binary search is O(log N), which is efficient, but caching might be needed if called frequently.
*   **System Integration**: Needs a way to report back to the system (statsd or similar).
