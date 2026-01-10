# CursorWrapper - Reverse Engineering Documentation

## Executive Summary
`CursorWrapper` implements the Decorator pattern for the `Cursor` interface. It wraps an existing `Cursor` instance and delegates all method calls to it. It allows creating modified cursors (like `CrossProcessCursorWrapper`) by overriding specific methods while keeping default behavior for others.

## Architecture Overview
*   **Inheritance**: Implements `Cursor`.
*   **Pattern**: Wrapper / Decorator.

## Detailed Functionality
*   **Constructor**: Accepts a `Cursor` to wrap.
*   **Delegation**: Every method (e.g., `getCount`, `getString`, `close`) calls `mCursor.method()`.
*   **Exception Safety**: No added logic, simply passes through exceptions.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `mCursor` | `Cursor` | The wrapped cursor instance. |

## API Reference
*   `getWrappedCursor()`: Returns the underlying cursor.
*   All `Cursor` methods: Delegated.

## Java-to-C++ Translation Guide
*   **Implementation**: A C++ class accepting a `Cursor*` (or smart pointer) in constructor.
*   **Virtual Methods**: Forward all virtual calls to the stored pointer.

## Test Cases & Validation
1.  **Delegation**: Mock inner cursor. Call wrapper methods. Verify inner cursor received calls.
2.  **State**: Verify wrapper state matches inner cursor state (position, closed status).
