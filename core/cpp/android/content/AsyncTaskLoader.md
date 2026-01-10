# AsyncTaskLoader - Reverse Engineering Documentation

## Executive Summary
`AsyncTaskLoader` is an abstract `Loader` that performs data loading using an `AsyncTask`. It handles the complexity of loading data on a background thread, cancelling loads, and throttling updates.
**Note**: This class is deprecated in favor of the Support Library/AndroidX version.

## Architecture Overview
- **Inheritance:** Extends `Loader<D>`.
- **Relationship:** Uses `AsyncTask` (specifically `LoadTask` inner class) to perform work.
- **Pattern:** Template Method pattern (`loadInBackground`).

## Detailed Functionality

### `loadInBackground()` (Abstract)
**Purpose**: Subclasses implement this to perform the actual data load.
**Thread**: Worker thread.

### `onForceLoad()`
**Purpose**: Triggers a load.
**Algorithm**:
1. Cancels any existing load.
2. Creates a new `LoadTask`.
3. Calls `executePendingTask()`.

### `executePendingTask()`
**Purpose**: Executes the waiting task, respecting throttling.
**Algorithm**:
1. Checks if a cancellation is in progress.
2. Checks `mUpdateThrottle` to see if we need to delay execution.
3. If delayed, posts a handler message.
4. If not delayed, executes `mTask` on the executor.

### `LoadTask` (Inner Class)
**Purpose**: The `AsyncTask` implementation.
**Algorithm**:
- `doInBackground`: Calls `AsyncTaskLoader.this.onLoadInBackground()`. Handles `OperationCanceledException`.
- `onPostExecute`: Dispatches load complete to the loader.
- `onCancelled`: Dispatches cancellation to the loader.

### `dispatchOnLoadComplete`
**Purpose**: Handles the result from the task.
**Algorithm**:
1. If the task is old (not current), dispatches cancellation.
2. If the loader is abandoned, ignores result.
3. Otherwise, commits content change and calls `deliverResult`.

## Data Model
- `mTask`: `LoadTask` - Current running task.
- `mCancellingTask`: `LoadTask` - Task currently being cancelled.
- `mUpdateThrottle`: `long` - Delay in milliseconds between loads.
- `mLastLoadCompleteTime`: `long` - Timestamp of last completion.

## API Reference
- `public abstract D loadInBackground()`
- `public void setUpdateThrottle(long delayMS)`
- `public void cancelLoadInBackground()`
- `public boolean isLoadInBackgroundCanceled()`

## Java-to-C++ Translation Guide
- **AsyncTask**: This is a specific Android Java construct. C++ replacement would use `std::thread`, `std::future`, or a thread pool.
- **Generics**: `AsyncTaskLoader<D>` maps to a C++ template class `AsyncTaskLoader<T>`.
- **Handler**: Used for throttling. C++ needs a delayed execution mechanism (e.g., timerfd, loop with timeout).

## Implementation Risks
- **Race Conditions**: Managing `mTask` and `mCancellingTask` requires careful synchronization logic, effectively handled by the main thread constraint of Loaders.
- **Object Lifetime**: Ensuring the Loader outlives the background task or that the task creates a strong reference (which Java inner classes do implicitly).
