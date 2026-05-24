# FilterQueryProvider - Reverse Engineering Documentation

## Executive Summary
`FilterQueryProvider` is an interface used by `CursorAdapter` to allow external clients to define how the cursor query should be generated based on a filtering constraint.

## Architecture Overview
*   **Type**: Interface.
*   **Method**: `Cursor runQuery(CharSequence constraint)`.

## Java-to-C++ Translation Guide
*   **Callback**: `std::function` or interface.

## Implementation Risks
*   None.
