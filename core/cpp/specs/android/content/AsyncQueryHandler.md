# AsyncQueryHandler - Reverse Engineering Documentation

## Executive Summary
`AsyncQueryHandler` is a helper class designed to handle `ContentResolver` operations (query, insert, update, delete) asynchronously on a background thread. This prevents blocking the main UI thread with potentially slow database operations.

## Architecture Overview
- **Inheritance:** Extends `Handler`.
- **Relationship:** Wraps a `ContentResolver`. Uses a `HandlerThread` ("AsyncQueryWorker") to process requests.
- **Pattern:** Command pattern / Worker thread pattern.

## Detailed Functionality

### `AsyncQueryHandler(ContentResolver cr)` (Constructor)
**Purpose**: Initializes the handler and the worker thread.
**Algorithm**:
1. holds a `WeakReference` to `ContentResolver` to prevent leaks.
2. Synchronized block to create a singleton `HandlerThread` named "AsyncQueryWorker" if it doesn't exist.
3. Creates a `WorkerHandler` attached to the worker thread's Looper.

### `startQuery(int token, Object cookie, Uri uri, ...)`
**Purpose**: Initiates an asynchronous query.
**Algorithm**:
1. Creates a `WorkerArgs` object containing parameters.
2. Sends a message to `mWorkerThreadHandler` with `EVENT_ARG_QUERY`.

### `WorkerHandler.handleMessage(Message msg)`
**Purpose**: Processes the background operations.
**Algorithm**:
1. Retrieves `ContentResolver`. If null, returns.
2. Switch based on event type (QUERY, INSERT, UPDATE, DELETE).
3. Performs the blocking `ContentResolver` operation.
4. For QUERY, calls `cursor.getCount()` to ensure window is filled.
5. Sends a reply message back to the `AsyncQueryHandler` (which runs on the original thread) with the result.

### `handleMessage(Message msg)` (Main Thread)
**Purpose**: Receives results from the worker thread.
**Algorithm**:
1. Switch based on event type.
2. Calls the appropriate callback: `onQueryComplete`, `onInsertComplete`, etc.

## Data Model
- `mResolver`: `WeakReference<ContentResolver>`.
- `mWorkerThreadHandler`: `Handler` for the background thread.
- `WorkerArgs`: Inner class holding arguments for the operation (Uri, projection, selection, values, etc.).

## API Reference
- `public void startQuery(...)`
- `public void startInsert(...)`
- `public void startUpdate(...)`
- `public void startDelete(...)`
- `public void cancelOperation(int token)`
- `protected void onQueryComplete(...)` (and others)

## Java-to-C++ Translation Guide
- **Handler/Looper**: Uses Android's message passing mechanism. C++ equivalent involves `ALooper` and `AMessage` or a custom thread pool with a command queue.
- **WeakReference**: C++ `std::weak_ptr`.
- **Cursor**: `android.database.Cursor` maps to a native cursor interface (likely wrapper around SQLite cursor).

## Implementation Risks
- **Memory Leaks**: The use of `WeakReference` is crucial. In C++, ensure `sp` and `wp` are used correctly.
- **Concurrency**: The worker thread is a singleton (`sLooper`). Ensure thread safety if porting the singleton pattern.
- **Cursor Lifecycle**: The cursor is opened in the worker thread and passed to the main thread. Ownership transfer must be clear.
