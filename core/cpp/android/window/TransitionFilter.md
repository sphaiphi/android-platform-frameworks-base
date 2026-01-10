# TransitionFilter - Reverse Engineering Documentation

## Executive Summary
`TransitionFilter` is a complex Parcelable class used to define criteria for matching and rerouting transitions to remote animation players. It allows the system to filter transitions based on types, flags, and specific requirements of the changing containers (e.g., "match if a task of type HOME is opening").

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Filter/Predicate for transitions.
*   **Inner Class**: `Requirement`.

## Detailed Functionality

### Matching Logic (`matches(TransitionInfo)`)
**Algorithm**:
1.  Check `mTypeSet`: If not null, the transition type must be in the set.
2.  Check `mFlags`: All bits in `mFlags` must be set in `info.getFlags()`.
3.  Check `mNotFlags`: No bits in `mNotFlags` can be set.
4.  Check `mRequirements`: All requirements must match. If a requirement matches and has `mNot` set to true, the whole filter fails.

### `Requirement` Matching Logic
**Algorithm**:
Checks each `Change` in the `TransitionInfo`:
1.  Token match (if `mTaskFragmentToken` set).
2.  Independence check (if `mMustBeIndependent` set).
3.  Z-order check (`mOrder == CONTAINER_ORDER_TOP`).
4.  Activity Type and Component match.
5.  Mode match (Open, Close, etc.).
6.  Flags match.
7.  Task status match.
8.  Custom animation support.
9.  Windowing mode match.

## Java-to-C++ Translation Guide

### Data Types
*   `ComponentName` -> `android::content::ComponentName`.
*   `IBinder` -> `sp<IBinder>`.

### Parceling
*   Standard sequential write. `mTypeSet` is an `int[]`. `mRequirements` is a typed array.

## Implementation Risks
*   **Complexity**: The matching logic is deep and nested. Precise translation of Boolean logic is critical.
