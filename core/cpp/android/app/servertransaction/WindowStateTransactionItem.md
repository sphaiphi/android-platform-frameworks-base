# WindowStateTransactionItem - Reverse Engineering Documentation

## Executive Summary
`WindowStateTransactionItem` is an abstract base class for transaction items that target a specific window (`IWindow`).

## Architecture Overview
- **Inheritance**: Extends `ClientTransactionItem`.
- **Role**: Window-targeting base class.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute` (template)
**Purpose**: Resolves window and executes.
**Algorithm**:
1. If `mWindow` implements `TransactionListener`, notify `onExecutingWindowStateTransactionItem`.
2. Call abstract `execute(..., mWindow, ...)`

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mWindow` | `IWindow` | The target window interface. |

### Serialization (Parcelable)
- **Flattening**: `writeStrongBinder`.
- **Unflattening**: `IWindow.Stub.asInterface`.

## Java-to-C++ Translation Guide

### Interfaces
- `IWindow` -> `android::sp<IWindow>` (Binder proxy).
- `TransactionListener` callback pattern.

## Implementation Risks
- **Binder Proxy**: The `mWindow` is a binder proxy. Calls on it are IPC calls (or local if same process).
