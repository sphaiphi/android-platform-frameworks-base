# SystemOverrideOnBackInvokedCallback - Reverse Engineering Documentation

## Executive Summary
`SystemOverrideOnBackInvokedCallback` is a specialized callback interface that allows declaring a specific override behavior (`overrideBehavior()`) that the system can recognize and optimize for (e.g., by playing a specific animation).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `interface` extends `OnBackInvokedCallback`
*   **Role**: Typed Callback.

## API Reference
*   `overrideBehavior()`: Returns int.
    *   `OVERRIDE_UNDEFINED` (0)
    *   `OVERRIDE_MOVE_TASK_TO_BACK` (1)
    *   `OVERRIDE_FINISH_AND_REMOVE_TASK` (2)

## Java-to-C++ Translation Guide
*   **Interface**: Virtual method `getOverrideBehavior()`.

## Implementation Risks
*   None.
