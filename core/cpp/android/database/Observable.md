# Observable - Reverse Engineering Documentation

## Executive Summary
`Observable<T>` is a generic base class for managing a list of observers. It provides thread-safe registration and unregistration.

## Architecture Overview
*   **Generics**: `T` is the observer type.
*   **Storage**: `ArrayList<T> mObservers`.

## API Reference
*   `registerObserver(T)`: Adds to list. Throws if null or already present.
*   `unregisterObserver(T)`: Removes. Throws if missing.
*   `unregisterAll()`: Clears list.

## Thread Safety
*   **Synchronization**: All accesses to `mObservers` are synchronized on `mObservers`.

## Java-to-C++ Translation Guide
*   **Template**: `template <typename T> class Observable`.
*   **Storage**: `std::vector<std::shared_ptr<T>>` or `std::vector<T*>`.
*   **Mutex**: `std::mutex`.
