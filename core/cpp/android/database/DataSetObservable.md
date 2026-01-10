# DataSetObservable - Reverse Engineering Documentation

## Executive Summary
`DataSetObservable` is a specialized `Observable` for `DataSetObserver`. It provides methods to notify observers of data changes (`notifyChanged`) or invalidation (`notifyInvalidated`).

## Detailed Functionality
*   `notifyChanged()`: Calls `onChanged()` on all observers in reverse order.
*   `notifyInvalidated()`: Calls `onInvalidated()` on all observers in reverse order.

## Java-Specific Notes
*   **Reverse Iteration**: Iterates from `size() - 1` down to `0` to allow observers to unregister themselves during the callback without `ConcurrentModificationException`.

## Java-to-C++ Translation Guide
*   **Iteration**: Use reverse iterator or carefully handle unregistration during iteration (copy list or use robust iterator).
