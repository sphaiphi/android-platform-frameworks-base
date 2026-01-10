# WindowContainerTransactionCallback - Reverse Engineering Documentation

## Executive Summary
`WindowContainerTransactionCallback` is an abstract base class for receiving notifications when a `WindowContainerTransaction` has been successfully applied and its corresponding `SurfaceControl.Transaction` is ready.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `abstract class`
*   **Role**: Async Completion Callback.

## Detailed Functionality
*   **`onTransactionReady(int id, Transaction t)`**: Abstract method.
*   **`mInterface`**: A binder stub (`BnWindowContainerTransactionCallback`) that delegates calls to the abstract method.

## Java-to-C++ Translation Guide
*   **BN**: `BnWindowContainerTransactionCallback` in C++.
*   **Usage**: Usually provided by the Shell to sync hierarchy changes with frame rendering.

## Implementation Risks
*   None.
