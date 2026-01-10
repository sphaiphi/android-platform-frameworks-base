# WindowTokenClientController - Reverse Engineering Documentation

## Executive Summary
`WindowTokenClientController` is a client-side singleton that manages the global set of `WindowTokenClient` instances within a process. it facilitates their initial attachment to the WindowManager and routes incoming IPC configuration updates to the appropriate client token.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Singleton)
*   **Role**: Global Client Manager.

## Detailed Functionality

### Registry
*   `mWindowTokenClients`: `ArraySet<WindowTokenClient>`. Tracks all active tokens.

### Attachment APIs
*   `attachToDisplayArea(...)`: Calls `IWindowManager.attachWindowContextToDisplayArea`.
*   `attachToDisplayContent(...)`: Calls `IWindowManager.attachWindowContextToDisplayContent`.
*   `attachToWindowToken(...)`: Calls `IWindowManager.attachWindowContextToWindowToken`.

### Dispatching
*   `onWindowConfigurationChanged(...)`: Receives a configuration update for a specific `IBinder` client token. Finds the `WindowTokenClient` in the registry and invokes `onConfigurationChanged`. Ensures the call happens on the main thread.

## Java-to-C++ Translation Guide

### Singleton
*   Standard C++ singleton.

### Threading
*   Uses `mHandler` (Main thread handler). C++ needs to post tasks to the process's main looper.

## Implementation Risks
*   **Memory Management**: Holds an `ArraySet` of tokens. Ensure tokens are removed (`detachIfNeeded`) to avoid leaks.
