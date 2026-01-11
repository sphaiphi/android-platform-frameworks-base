# WeakSparseArray - Reverse Engineering Documentation

## Executive Summary
A specialized `SparseArray` that holds `WeakReference` to its values. It includes logic to clean up unreachable values from the array when the references are collected.

## Logic
*   **`mRefQueue`**: ReferenceQueue to track collected objects.
*   **`removeUnreachableValues`**: Polls the queue and removes corresponding keys from the sparse array.

## Java-to-C++ Translation Guide
*   **Weak Pointers**: C++ `std::map<int, std::weak_ptr<T>>` with a custom cleanup mechanism would be the equivalent.
