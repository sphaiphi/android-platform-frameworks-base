# OnBackInvokedCallback - Reverse Engineering Documentation

## Executive Summary
`OnBackInvokedCallback` is the fundamental functional interface for handling the "Back" action in the modern Android navigation system. It replaces `onBackPressed`.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `interface`
*   **Role**: Callback.

## API Reference
*   `void onBackInvoked()`: Called when the back gesture is completed/committed.

## Java-to-C++ Translation Guide
*   **Interface**: `class OnBackInvokedCallback` with `virtual void onBackInvoked() = 0;`.
*   **Binder**: This usually wraps or is wrapped by `IOnBackInvokedCallback` (AIDL).

## Implementation Risks
*   None.
