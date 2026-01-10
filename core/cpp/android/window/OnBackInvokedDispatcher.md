# OnBackInvokedDispatcher - Reverse Engineering Documentation

## Executive Summary
`OnBackInvokedDispatcher` is the public interface for registering `OnBackInvokedCallback`s. It defines priority constants and methods to manage the callback list.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `interface`
*   **Role**: Dispatcher Contract.

## Constants
*   `PRIORITY_OVERLAY` (1000000)
*   `PRIORITY_DEFAULT` (0)
*   `PRIORITY_SYSTEM` (-1)
*   `PRIORITY_SYSTEM_NAVIGATION_OBSERVER` (-2)

## API Reference
*   `registerOnBackInvokedCallback(int priority, OnBackInvokedCallback callback)`
*   `unregisterOnBackInvokedCallback(OnBackInvokedCallback callback)`
*   `registerSystemOnBackInvokedCallback` (Default: no-op)
*   `setImeOnBackInvokedDispatcher` (Default: no-op)

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual class.
*   **Constants**: `static const` or `enum`.

## Implementation Risks
*   None.
