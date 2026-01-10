# BackStackRecord - Reverse Engineering Documentation

## Executive Summary
`BackStackRecord` is the implementation of `FragmentTransaction` that records a set of operations (add, remove, replace, etc.) on fragments. It can be added to the `FragmentManager`'s back stack, allowing the user to reverse the transaction (pop).

## Architecture Overview
*   **Inheritance**: `FragmentTransaction`.
*   **Implements**: `FragmentManager.BackStackEntry`, `FragmentManagerImpl.OpGenerator`.
*   **Dependencies**: `FragmentManagerImpl`, `Fragment`.

## Detailed Functionality

### Operation Recording
*   **Ops**: Maintains a list of `Op` objects. Each `Op` contains:
    *   `cmd`: Command ID (OP_ADD, OP_REMOVE, OP_REPLACE, etc.).
    *   `fragment`: Target fragment.
    *   `enterAnim`, `exitAnim`, `popEnterAnim`, `popExitAnim`: Animation resources.
*   **Methods**: `add`, `replace`, `remove`, `hide`, `show`, `detach`, `attach`, `setPrimaryNavigationFragment`.

### Back Stack Management
*   `addToBackStack(String name)`: Marks the transaction to be saved.
*   `commit()` / `commitAllowingStateLoss()`: Schedules execution. calls `mManager.enqueueAction`.
*   `popBackStack()`: Reverses the operations (implemented via `executePopOps`).

### Execution Logic
*   `executeOps()`: Iterates `mOps` and applies them to the `FragmentManager` (calls `mManager.addFragment`, etc.).
*   `executePopOps()`: Iterates `mOps` in reverse and applies the inverse operation (Add -> Remove).
*   `expandOps()`: Replaces `OP_REPLACE` with `OP_REMOVE` + `OP_ADD`.

### Transition Support
*   `addSharedElement`: Tracks shared elements for transitions.
*   `calculateFragments`: Determines which fragments are entering/exiting for transition system.

## Data Model
*   `mOps`: `ArrayList<Op>`.
*   `mIndex`: Back stack index.
*   `mBreadCrumb*`: Breadcrumb data.

## Java-to-C++ Translation Guide
*   **Logic**: Core logic is state manipulation of the `FragmentManager`.
*   **Op Structure**: Simple struct/class for `Op`.
*   **Command Pattern**: The class effectively implements the Command pattern with Undo support.

## Implementation Risks
*   **Lifecycle Complexity**: Fragment lifecycle management is notoriously complex. Replicating the exact behavior of `executeOps`/`executePopOps` and their interaction with state loss and transitions is difficult.
