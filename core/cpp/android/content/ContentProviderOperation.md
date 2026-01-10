# ContentProviderOperation - Reverse Engineering Documentation

## Executive Summary
`ContentProviderOperation` represents a single operation (Insert, Update, Delete, Assert, Call) that can be executed as part of a batch transaction on a `ContentProvider`. It supports "back references", allowing operations to use results from previous operations in the same batch.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Pattern:** Command Pattern / Builder Pattern.

## Detailed Functionality

### `apply(ContentProvider, ContentProviderResult[], int)`
**Purpose**: Executes the operation against a provider.
**Algorithm**:
1. Resolves "back references" (values dependent on previous results).
2. Executes the specific operation type (`insert`, `delete`, `update`, `query` for assert, `call`).
3. For `TYPE_ASSERT`, verifies query results match expected values.
4. Verifies expected row counts.
5. Returns `ContentProviderResult`.

### Builder (Inner Class)
**Purpose**: Fluent API to construct operations.
- `withValueBackReference`: Sets a value to be resolved at runtime from a previous result.

## Data Model
- `mType`: `int` (INSERT, UPDATE, DELETE, ASSERT, CALL).
- `mUri`: `Uri`.
- `mValues`: `ArrayMap` (Values to save).
- `mSelection`: `String` (Where clause).
- `mSelectionArgs`: `SparseArray` (Args, potentially with back refs).
- `mExpectedCount`: `Integer`.

## API Reference
- `public static Builder newInsert(Uri uri)`
- `public static Builder newUpdate(Uri uri)`
- `public static Builder newDelete(Uri uri)`
- `public static Builder newAssertQuery(Uri uri)`
- `public ContentProviderResult apply(...)`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.
- **Back References**: Logic for resolving back references (`BackReference` inner class) needs to be implemented.
- **Polymorphism**: The `apply` method switches on type. C++ could use polymorphism or a similar switch.

## Implementation Risks
- **Back Reference Resolution**: Complex logic involved in resolving previous results (IDs vs Counts).
- **Atomic Execution**: `applyBatch` is often transactional. Ensuring failure handling works correctly is key.
