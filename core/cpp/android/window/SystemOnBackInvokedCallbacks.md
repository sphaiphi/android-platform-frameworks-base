# SystemOnBackInvokedCallbacks - Reverse Engineering Documentation

## Executive Summary
`SystemOnBackInvokedCallbacks` provides factory methods for creating standard system back behaviors (like "Move Task to Back" or "Finish and Remove Task") that can be registered with `OnBackInvokedDispatcher`.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` (Utility)
*   **Role**: Factory.

## Detailed Functionality

### Factories
*   `MoveTaskToBackCallbackFactory`: Creates callback invoking `activity.moveTaskToBack(true)`. Returns `OVERRIDE_MOVE_TASK_TO_BACK`.
*   `FinishAndRemoveTaskCallbackFactory`: Creates callback invoking `activity.finishAndRemoveTask()`. Returns `OVERRIDE_FINISH_AND_REMOVE_TASK`.

### Caching
*   Uses `WeakReference` to cache the created callbacks mapped to the Activity instance to avoid duplicate creations.

## Java-to-C++ Translation Guide
*   This class mainly interacts with the `Activity` class. In C++, this would likely interact with the internal representation of an Activity (e.g., `ActivityRecord` on server side, or native activity glue).

## Implementation Risks
*   None.
