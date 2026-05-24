# ProgramList - Reverse Engineering Documentation

## Executive Summary
`ProgramList` manages a dynamic list of radio programs (`RadioManager.ProgramInfo`), handling updates received in chunks (additions, removals, modifications). It provides thread-safe access to the list and notification mechanisms for clients.

## Architecture Overview
-   **Type**: System API, Thread-safe Data Container.
-   **Package**: `android.hardware.radio`.
-   **Role**: Acts as a live view of available radio programs, updated by the `RadioTuner`.

## Detailed Functionality

### Core Components
-   **Storage**: `mPrograms` is an `ArrayMap` mapping `ProgramSelector.Identifier` (primary ID) to another `ArrayMap` of `UniqueProgramIdentifier` -> `RadioManager.ProgramInfo`. This hierarchical structure supports multiple programs with the same primary ID (e.g., same frequency but different DAB services).
-   **Locking**: Uses a private `Object mLock` for synchronization.
-   **State**:
    -   `mIsClosed`: Boolean, tracks if the list is closed.
    -   `mIsComplete`: Boolean, tracks if the scan is complete.
-   **Callbacks**:
    -   `mListCallbacks`: List of `ListCallback` (onItemChanged, onItemRemoved).
    -   `mOnCompleteListeners`: List of `OnCompleteListener`.
    -   `mOnCloseListener`: Single listener for close events.

### Logic Flow
1.  **Applying Updates (`apply(Chunk chunk)`)**:
    -   **Purge**: If `chunk.isPurge()` is true, clears all entries except those explicitly marked for removal in the chunk (though the logic `removed.getValue() != null` implies keeping them temporarily to notify removal, but `programsIterator.remove()` clears them). *Correction*: It iterates, adds to `removedList`, and removes from map.
    -   **Remove**: Iterates `chunk.getRemoved()`, removing them from `mPrograms`. If a primary ID bucket becomes empty, it's added to `removedList`.
    -   **Modify/Add**: Iterates `chunk.getModified()`, adding/updating them in `mPrograms`. Adds primary IDs to `changedSet`.
    -   **Completion**: If `chunk.isComplete()`, marks `mIsComplete` and notifies listeners.
    -   **Notification**: Calls `onItemRemoved` and `onItemChanged` on registered callbacks.

2.  **Conversion (`toList()`)**:
    -   Flattens the nested map structure into a single `List<RadioManager.ProgramInfo>`.

### Inner Classes
-   **Filter** (Parcelable):
    -   Filters programs based on identifier types, specific identifiers, categories, and modifications.
    -   Fields: `mIdentifierTypes`, `mIdentifiers`, `mIncludeCategories`, `mExcludeModifications`, `mVendorFilter`.
-   **Chunk** (Parcelable):
    -   Represents a batch update.
    -   Fields: `mPurge` (bool), `mComplete` (bool), `mModified` (Set), `mRemoved` (Set).
-   **ListCallback**: Abstract class for receiving granular updates.

## Data Model
-   **Primary Key**: `ProgramSelector.Identifier`.
-   **Secondary Key**: `UniqueProgramIdentifier`.
-   **Value**: `RadioManager.ProgramInfo`.

## Java-to-C++ Translation Guide
-   **Synchronization**: Use `std::mutex` and `std::lock_guard`.
-   **Collections**:
    -   `ArrayMap` -> `std::map` or `std::unordered_map`.
    -   `List` -> `std::vector`.
    -   `Set` -> `std::set` or `std::unordered_set`.
-   **Callbacks**: Use `std::function` or observer pattern interfaces.
-   **Parcelables**: `Filter` and `Chunk` should be mapped to AIDL-generated C++ structures or similar DTOs.

## Implementation Risks
-   **Concurrency**: Ensure rigorous locking when accessing `mPrograms` and callback lists, especially during the `apply` method which modifies state and notifies external listeners (potential re-entrancy issues, though Java implementation copies listener lists before iterating).
-   **Memory Management**: Clean up listeners and maps on `close()`.

---
