# IAccessibilityInputMethodSessionInvoker - Reverse Engineering Documentation

## Executive Summary
Wrapper around `IAccessibilityInputMethodSession` (Binder interface) that can optionally dispatch calls to a background handler to emulate async one-way calls for local instances.

## Java-to-C++ Translation Guide
*   **Binder Proxy**: Wrapper pattern.
