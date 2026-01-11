# Scene - Reverse Engineering Documentation

## Executive Summary
A `Scene` represents a specific state of a view hierarchy. It wraps a root `ViewGroup` and either a layout resource ID or a view tree to be placed there.

## Data Model
-   **`mSceneRoot`** (`ViewGroup`): The container.
-   **`mLayoutId`** (`int`) / **`mLayout`** (`View`): The content.
-   **`mEnterAction`**, **`mExitAction`**: `Runnable` callbacks.

## API Reference
-   **`getSceneForLayout`**: Factory caching scenes by layout ID.
-   **`enter()`**: Removes all views from root, inflates/adds new layout, runs enter action.
-   **`exit()`**: Runs exit action.

## Java-to-C++ Translation Guide
-   **View Tree**: Corresponds to replacing a subtree in the UI graph.
-   **Inflation**: "Inflating" a layout resource is specific to Android's resource system. C++ UI might load a declarative UI file or instantiate a widget tree.
