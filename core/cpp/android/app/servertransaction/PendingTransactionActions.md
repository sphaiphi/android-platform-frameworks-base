# PendingTransactionActions - Reverse Engineering Documentation

## Executive Summary
`PendingTransactionActions` is a container object used to pass shared state and actions between different items within a single `ClientTransaction` execution. It effectively acts as a context or scratchpad for the transaction.

## Architecture Overview
- **Type**: POJO (Plain Old Java Object).
- **Role**: State container / Context object.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `clear()`
**Purpose**: Resets the state.
**Fields Cleared**: `mRestoreInstanceState`, `mCallOnPostCreate`, `mOldState`, `mStopInfo`.

### Accessors
- Getters and setters for all fields.

### Inner Class: `StopInfo`
- **Role**: Runnable that reports activity stop to the server.
- **Functionality**:
  - Holds reference to activity, state bundles, description.
  - `run()`: calls `ActivityClient.activityStopped`.
  - **Error Handling**: Catches `RuntimeException` (specifically `TransactionTooLargeException`) to log bundle stats if data is too large.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mRestoreInstanceState` | `boolean` | Should instance state be restored? |
| `mCallOnPostCreate` | `boolean` | Should `onPostCreate` be called? |
| `mOldState` | `Bundle` | Previous state (for comparison/cleanup). |
| `mStopInfo` | `StopInfo` | Runnable info for stop reporting. |

## Java-to-C++ Translation Guide

### Structure
- C++ struct or class with public accessors.

### Inner Class
- `StopInfo` acts as a callback/closure. In C++, this might be a `std::function` or a dedicated struct passed to the handler.

### Exception Handling
- The `TransactionTooLargeException` handling in `StopInfo` is specific to Binder limitations. C++ Binder usage also faces this limit. Logic to inspect bundle sizes on failure is valuable.

## Implementation Risks
- **Lifecycle**: This object is reused (`clear()` called by executor). In C++, ensure clear ownership or reset logic to prevent stale data between transactions.
