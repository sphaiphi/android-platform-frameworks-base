# FragmentManager - Reverse Engineering Documentation

## Executive Summary
`FragmentManager` is the abstract interface for interacting with Fragments. The internal implementation is `FragmentManagerImpl`. It manages the list of fragments, the back stack, and executes transactions.

## Architecture Overview
*   **Implementation**: `FragmentManagerImpl` (in same file/package typically).
*   **Nested Interfaces**: `BackStackEntry`, `OnBackStackChangedListener`, `FragmentLifecycleCallbacks`.

## Detailed Functionality
*   **Transactions**: `beginTransaction()` returns `FragmentTransaction`.
*   **Execution**: `executePendingTransactions()`, `popBackStack()`.
*   **Query**: `findFragmentById`, `findFragmentByTag`.
*   **State**: `saveFragmentInstanceState`.

### FragmentManagerImpl
*   **Main Loop**: `execPendingActions()` processes the queue of transactions.
*   **State Machine**: `moveToState` moves fragments through their lifecycle states to match the manager's `mCurState`.
*   **Animation**: Loads and runs animations/transitions.

## Java-to-C++ Translation Guide
*   **Core Logic**: This is the heart of the Fragment system.
*   **Transaction Queue**: Needs a command queue.
*   **State Sync**: `moveToState` logic is critical.

## Implementation Risks
*   **Reentrancy**: Handling transactions inside callbacks.
*   **Animation Coordination**: Syncing animations with lifecycle changes.
