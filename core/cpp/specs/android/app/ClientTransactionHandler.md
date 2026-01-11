# ClientTransactionHandler - Reverse Engineering Documentation

## Executive Summary
`ClientTransactionHandler` is an abstract base class that defines the contract for processing `ClientTransaction`s (lifecycle callbacks sent from system server). `ActivityThread` is the primary implementation.

## Architecture Overview
*   **Role**: Abstract Processor.
*   **Subclasses**: `ActivityThread`.
*   **Usage**: Used by `ClientTransaction` items to execute operations (`handleResumeActivity`, `handleStopActivity`, etc.) on the client.

## Detailed Functionality
*   **Scheduling**: `scheduleTransaction` (posts to handler).
*   **Execution**: `getTransactionExecutor().execute(transaction)`.
*   **Abstract Methods**: `handleLaunchActivity`, `handleResumeActivity`, `handleDestroyActivity`, `updateProcessState`.

## Java-to-C++ Translation Guide
*   **Virtual Base Class**: Define as abstract class with pure virtual methods for lifecycle handlers.
*   **Executor**: Integrates with a `TransactionExecutor` (command pattern).

## Implementation Risks
*   **Lifecycle State Machine**: Must strictly match the server's expectation of state transitions.
