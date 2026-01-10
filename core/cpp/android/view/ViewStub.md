# ViewStub - Reverse Engineering Documentation

## Executive Summary
`ViewStub` is an invisible, zero-sized `View` that acts as a lazy-loading placeholder for layout resources. it allows for postponing the inflation of complex UI parts (like progress bars or error states) until they are actually needed, reducing initial layout time and memory usage.

## Architecture Overview
*   **Role**: Deferred layout factory.
*   **Transition**: Once `inflate()` or `setVisibility(VISIBLE)` is called, the `ViewStub` is removed from its parent and replaced by the newly inflated views.

## Detailed Functionality

### 1. Inflation
*   **`inflate()`**: Obtains a `LayoutInflater`, parses the `mLayoutResource`, and performs the physical swap in the parent `ViewGroup`.
*   **`inflatedId`**: Allows overriding the ID of the root view of the newly inflated hierarchy.

### 2. Lifecycle
*   **`OnInflateListener`**: Notifies the app when the stub has been swapped, allowing for early setup of the new views.

## Java-to-C++ Translation Guide
*   **Pattern**: Factory / Proxy Pattern.
*   **Parent Management**: Requires direct manipulation of the parent's child array (`indexOfChild`, `removeViewInLayout`).

## Implementation Risks
*   **Null Parent**: If `inflate()` is called before the stub is attached to a `ViewGroup`, it throws an `IllegalStateException`.
*   **One-Shot**: A `ViewStub` can only be inflated once. subsequent calls to `setVisibility` are forwarded to the inflated view.
