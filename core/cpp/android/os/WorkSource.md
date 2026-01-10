# WorkSource - Reverse Engineering Documentation

## Executive Summary
`WorkSource` describes the source of some work that may be executed by another process. It allows system services (like PowerManager or WifiManager) to attribute resource usage (battery, data) to the original requesting app (UID) rather than the system service itself.

## Architecture Overview
-   **Pattern**: Attribution Tag / Accounting Token.
-   **Structure**: Supports both a flat list of UIDs (`mUids`) and "Work Chains" (`mChains`) for complex attribution scenarios (e.g., App A -> Service B -> Service C).

## Data Model
-   **Flat List**:
    -   `mUids` (int[]): List of UIDs.
    -   `mNames` (String[]): Optional corresponding package names.
-   **Chains**:
    -   `mChains` (ArrayList<WorkChain>): List of attribution chains.
    -   **WorkChain**: An ordered list of (UID, Tag) pairs representing the call stack.

## API Reference
-   **Constructors**: `WorkSource(int uid)`, `WorkSource(WorkSource orig)`.
-   **Modification**: `add(int uid)`, `add(WorkSource other)`, `remove(WorkSource other)`.
-   **Access**: `get(int index)` (UID), `getName(int index)`.
-   **Diffs**: `diff(WorkSource other)` returns true if content differs.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::os::WorkSource` (Parcelable in Binder).
-   **Usage**: Often passed as an argument in AIDL interfaces.
-   **Logic**: The `diff` and `updateLocked` logic is complex and critical for battery stats delta reporting. C++ implementation should likely rely on `WorkSource.h` / `WorkSource.cpp` in frameworks/native if available, or replicate the merging logic carefully.

## Implementation Risks
-   **Chains vs Flat**: Older battery stats logic might ignore chains. Ensure full support for WorkChains if implementing attribution logic.
