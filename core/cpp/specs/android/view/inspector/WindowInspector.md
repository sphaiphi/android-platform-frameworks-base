# WindowInspector - Reverse Engineering Documentation

## Executive Summary
Provides access to global window views attached to the process.

## Key Methods
*   **`getGlobalWindowViews`**: Delegates to `WindowManagerGlobal.getInstance().getWindowViews()`.

## Java-to-C++ Translation Guide
*   **Static Wrapper**: Simple wrapper around another singleton.
