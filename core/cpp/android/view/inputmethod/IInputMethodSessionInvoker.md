# IInputMethodSessionInvoker - Reverse Engineering Documentation

## Executive Summary
Wrapper around `IInputMethodSession` (Binder interface) similar to `IAccessibilityInputMethodSessionInvoker`. Used by `InputMethodManager` to talk to the IME session.

## Java-to-C++ Translation Guide
*   **Binder Proxy**: Wrapper pattern.
