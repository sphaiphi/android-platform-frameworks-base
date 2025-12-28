# UndoOwner - Reverse Engineering Documentation

## Executive Summary
`UndoOwner` identifies the owner of data being modified (e.g., a specific TextView). It is used to scope undo/redo operations.

## Architecture Overview
- **Relationship:** Managed by `UndoManager`.

## Data Model
- `mTag`: `String`.
- `mManager`: `UndoManager`.
- `mData`: `Object` (Weak reference or similar in usage, though here it's strong).
- `mOpCount`: `int` (Number of active operations).

## Java-to-C++ Translation Guide
- **Data Association**: In C++, `mData` would likely be `void*` or a `std::any`, or a weak pointer to the owning object.

## Implementation Risks
- **Lifecycle**: `mOpCount` is used to determine when an owner is no longer active and can be removed from the manager.