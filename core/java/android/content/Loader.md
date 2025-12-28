# Loader - Reverse Engineering Documentation

## Executive Summary
`Loader` is a class that performs asynchronous loading of data. It monitors the data source and delivers new results when content changes.
**Note**: Deprecated in favor of AndroidX.

## Architecture Overview
- **Inheritance:** `Object`.
- **States:** Started, Stopped, Reset, Abandoned.
- **Observers:** `OnLoadCompleteListener`, `OnLoadCanceledListener`.

## Detailed Functionality

### Lifecycle Methods
- **`startLoading()`**: Transitions to started state. Calls `onStartLoading()`.
- **`stopLoading()`**: Transitions to stopped state. Calls `onStopLoading()`.
- **`reset()`**: Resets the loader. Calls `onReset()`.
- **`abandon()`**: Tells loader it is being abandoned (e.g., Activity destroyed but LoaderManager keeping it around briefly?). Calls `onAbandon()`.

### Data Delivery
- **`deliverResult(D data)`**: Sends data to the listener (`LoaderManager`).
- **`deliverCancellation()`**: Notifies listener of cancellation.

### `ForceLoadContentObserver` (Inner Class)
- Bridge between `ContentObserver` and `Loader.onContentChanged()`.

## Data Model
- `mId`: `int`.
- `mListener`: `OnLoadCompleteListener`.
- `mContext`: `Context`.
- `mStarted`, `mAbandoned`, `mReset`, `mContentChanged`: State flags.

## API Reference
- `public void startLoading()`
- `public void stopLoading()`
- `public void reset()`
- `public void deliverResult(D data)`

## Java-to-C++ Translation Guide
- **Generics**: Template class `Loader<T>`.
- **Context**: Weak reference or strict ownership management needed.

## Implementation Risks
- **Memory Leaks**: Listeners (often Activities/Fragments) must be unregistered or the Loader must not outlive them if it holds strong references.
- **State Machine**: The state transitions (Started -> Stopped -> Reset) must be strictly followed.
