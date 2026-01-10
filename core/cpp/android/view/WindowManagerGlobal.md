# WindowManagerGlobal - Reverse Engineering Documentation

## Executive Summary
`WindowManagerGlobal` is a singleton class that acts as the central hub for window management within an application process. It maintains the list of all active Views, their `ViewRootImpl`s, and their `LayoutParams`. It handles the low-level communication with the `WindowManagerService` (WMS) and manages global resources like the `InputMethodManager` instance.

## Architecture Overview
*   **Role**: Process-wide window registry and WMS client.
*   **Singleton**: Accessed via `getInstance()`.
*   **Storage**: Maintains `ArrayList`s for `mViews`, `mRoots`, and `mParams`.

## Detailed Functionality

### 1. View Management
*   **`addView()`**: Creates a `ViewRootImpl` for the given view, initializes it, and calls `mWindowSession.addToDisplay()`.
*   **`updateViewLayout()`**: Updates the layout parameters and notifies the `ViewRootImpl` to schedule a traversal.
*   **`removeView()`**: Tears down the `ViewRootImpl` and removes the view from the registry.

### 2. System Service Access
*   **`getWindowManagerService()`**: Lazily connects to the `IWindowManager` binder service.
*   **`getWindowSession()`**: Establishes a session (`IWindowSession`) with WMS for this process.

### 3. Debugging & Tracing
*   **`dumpGfxInfo()`**: Aggregates rendering performance data from all `ViewRootImpl`s for `dumpsys`.
*   **`trimMemory()`**: Signals all hardware renderers to release caches.

## Java-to-C++ Translation Guide
*   **Global State**: Use a singleton pattern.
*   **Thread Safety**: All access to the lists (`mViews`, etc.) is guarded by `mLock`. This must be replicated to prevent race conditions in a multi-threaded native UI toolkit.

## Implementation Risks
*   **Deadlock**: `WindowManagerGlobal` locks must not be held while calling into WMS (which might call back into the process).
*   **Leakage**: If a `ViewRootImpl` fails to die correctly (e.g., due to an exception), it must be forcibly removed from the lists.
