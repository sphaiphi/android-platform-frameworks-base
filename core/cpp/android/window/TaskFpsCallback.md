# TaskFpsCallback - Reverse Engineering Documentation

## Executive Summary
`TaskFpsCallback` allows system components to receive FPS updates for a specific task. It wraps an AIDL interface `ITaskFpsCallback`.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `abstract class`
*   **Role**: Listener.

## Detailed Functionality
*   **`onFpsReported(float fps)`**: Abstract method to be implemented by client.
*   **`dispatchOnFpsReported`**: Static binder thread dispatcher.

## Java-to-C++ Translation Guide
*   **Interface**: `class ITaskFpsCallback`.
*   **Binder**: `BnTaskFpsCallback`.

## Implementation Risks
*   None.
