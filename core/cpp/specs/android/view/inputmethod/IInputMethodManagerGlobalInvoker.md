# IInputMethodManagerGlobalInvoker - Reverse Engineering Documentation

## Executive Summary
Global static helper to invoke methods on the `IInputMethodManager` binder. Manages the service instance cache (`sServiceCache`).

## Java-to-C++ Translation Guide
*   **Singleton**: Accessor for global service.
