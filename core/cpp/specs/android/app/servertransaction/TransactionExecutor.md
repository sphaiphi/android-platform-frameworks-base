# TransactionExecutor - Reverse Engineering Documentation

## Executive Summary
`TransactionExecutor` is the engine that processes a `ClientTransaction`. It iterates through the transaction items, resolves lifecycle dependencies (using helper logic to fill in missing states), and executes the callbacks and lifecycle requests in order.

## Architecture Overview
- **Type**: Logic/Controller class.
- **Role**: Transaction Processor.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute(ClientTransaction)`
**Purpose**: Main entry point.
**Algorithm**:
1. Start trace.
2. Call `executeTransactionItems(transaction)`.
3. End trace (finally).
4. Clear `mPendingActions`.

### `executeTransactionItems`
**Purpose**: Iterates and executes items.
**Algorithm**:
1. Loop through items in transaction.
2. If item is `ActivityLifecycleItem` -> `executeLifecycleItem`.
3. Else -> `executeNonLifecycleItem`.

### `executeNonLifecycleItem`
**Purpose**: Handles callbacks.
**Algorithm**:
1. Resolve `ActivityClientRecord`.
2. **Pre-destroyed Check**: If activity is destroyed/marked for destruction but record is missing, skip.
3. **Pre-execution State**: If item requires a pre-state (e.g., needs to be RESUMED), calculate shortest path using `mHelper` and cycle activity to that state (`cycleToPath`).
4. `item.execute(...)`.
5. `item.postExecute(...)`.
6. **Post-execution State**: If item requests a post-state, cycle activity to that state.
   - **Optimization**: `shouldExcludeLastLifecycleState` checks if a subsequent explicit lifecycle item covers this requirement to avoid redundant transitions.

### `executeLifecycleItem`
**Purpose**: Handles final lifecycle request.
**Algorithm**:
1. Resolve record.
2. **Cycle**: Cycle activity to the state *before* the target state (`excludeLastState=true`).
3. **Execute**: Perform the final transition using the item's specific parameters (e.g., specific intent for Launch, or flags for Pause).
4. `item.postExecute`.

### `cycleToPath` & `performLifecycleSequence`
**Purpose**: Moves activity through states.
**Algorithm**:
1. `mHelper.getLifecyclePath`: Computes list of states (e.g., PAUSE -> STOP).
2. Iterate through path:
   - Call corresponding handler on `mTransactionHandler` (ActivityThread) for each state.
   - Example: For `ON_RESUME`, call `handleResumeActivity`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mTransactionHandler` | `ClientTransactionHandler` | The delegate (ActivityThread). |
| `mPendingActions` | `PendingTransactionActions` | Shared context. |
| `mHelper` | `TransactionExecutorHelper` | Path calculation logic. |

## Java-to-C++ Translation Guide

### State Machine
- This class implements the core state machine driver. The C++ implementation must replicate the logic of `cycleToPath` and `performLifecycleSequence` exactly to maintain Android's strict lifecycle guarantees.

### Dependencies
- `TransactionExecutorHelper`: Critical for path finding.
- `ClientTransactionHandler`: Abstract interface to the app logic.

## Implementation Risks
- **State Resolution**: The `getClosestPreExecutionState` and path finding logic is complex. Errors here can lead to illegal state transitions (crashing apps).
- **Optimization**: The `shouldExcludeLastLifecycleState` optimization is subtle but important for performance and correctness (avoiding double-resumes).
