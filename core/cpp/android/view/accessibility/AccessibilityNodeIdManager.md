# AccessibilityNodeIdManager - Reverse Engineering Documentation

## Executive Summary
Internal utility to map Accessibility View IDs to `View` instances within a process. Used to find the actual `View` object corresponding to an ID reported in an `AccessibilityNodeInfo`.

## Data Model
*   `WeakSparseArray<View> mIdsToViews`: Maps integer IDs to WeakReferences of Views.

## Java-to-C++ Translation Guide
*   **Weak References**: Critical to avoid memory leaks. C++ `std::weak_ptr` or similar.
