# NetworkPolicy.java - Reverse Engineering Documentation

## Executive Summary
`NetworkPolicy` defines a set of constraints and accounting rules for a network identified by a `NetworkTemplate`. It controls data usage limits, warning thresholds, and billing cycles (e.g., monthly resets).

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`
- **Dependencies**: `NetworkTemplate`, `RecurrenceRule`.
- **Comparable**: Implements `Comparable<NetworkPolicy>` based on `limitBytes`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `template` | `NetworkTemplate` | Identifies the network(s) this policy applies to. |
| `cycleRule` | `RecurrenceRule` | Defines the cycle reset period (e.g., monthly on the 5th). |
| `warningBytes` | `long` | Usage threshold for user warning (-1 if disabled). |
| `limitBytes` | `long` | Usage hard limit (-1 if disabled). |
| `lastWarningSnooze` | `long` | Timestamp when warning was last snoozed. |
| `lastLimitSnooze` | `long` | Timestamp when limit was last snoozed. |
| `metered` | `boolean` | Whether the network is metered. |
| `inferred` | `boolean` | Whether the policy was inferred (not manually set). |

## Functionality
-   **Cycle Calculation**: `cycleIterator()` returns ranges of time for the billing cycles.
-   **Threshold Checks**: `isOverWarning(totalBytes)`, `isOverLimit(totalBytes)`.
-   **Backup**: Includes custom manual serialization for backup/restore (`getBytesForBackup`, `getNetworkPolicyFromBackup`). Supports versioning.

## Java-to-C++ Translation Guide

### Data Structure
```cpp
struct NetworkPolicy {
    NetworkTemplate template;
    RecurrenceRule cycleRule; // Needs C++ equivalent
    int64_t warningBytes = -1;
    int64_t limitBytes = -1;
    int64_t lastWarningSnooze = -1;
    int64_t lastLimitSnooze = -1;
    bool metered = true;
    bool inferred = false;
    
    bool isOverLimit(int64_t totalBytes) const;
};
```

### Logic
The `isOverLimit` adds a buffer of `2 * DEFAULT_MTU` (3000 bytes) before triggering, to account for kernel packet processing race conditions.

### Serialization
Backup serialization is manual DataOutputStream/DataInputStream. If C++ needs to read these backups, the logic must be ported byte-for-byte, handling the versioning (`VERSION_INIT` to `VERSION_RAPID`).
