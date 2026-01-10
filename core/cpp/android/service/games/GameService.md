# GameService - Reverse Engineering Documentation

## Executive Summary
`GameService` is the top-level service for the Android Game Service framework. It acts as a lightweight, always-running observer that detects when games are started and initiates game sessions (overlays/dashboards).

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IGameService.Stub`. Receives an `IGameServiceController` from the system server upon connection.
*   **Separation of Concerns**: `GameService` is intended to be lightweight. Heavyweight operations (UI) should be moved to a `GameSession` created via a `GameSessionService`.
*   **Permission**: Requires `android.permission.BIND_GAME_SERVICE`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IGameService` binder interface if the action is `ACTION_GAME_SERVICE`.

### Core Lifecycle Methods
*   **`onConnected()`**: Called when the system is ready. The service receives an `IGameServiceController` which it uses to trigger session creation.
*   **`onGameStarted(GameStartedEvent)`**: Called by the system when a game task enters the foreground. The service can use the `taskId` from the event to call `createGameSession`.
*   **`onDisconnected()`**: Called when the service is being shut down.

### Operations
*   **`createGameSession(int taskId)`**: Requests the system to start a new game session for the specified task. This will typically trigger the `GameSessionService` to create a `GameSession`.

## API Reference

### Constants
*   `ACTION_GAME_SERVICE`: `"android.service.games.action.GAME_SERVICE"`
*   `SERVICE_META_DATA`: `"android.game_service"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IGameService.Stub`.
*   **C++**: `BnGameService`.
*   **Controller**: Uses `IGameServiceController` (proxy to system server).

### Threading
*   **Java**: Uses `Handler.getMain()` to execute logic on the main thread.
*   **C++**: Ensure thread-safe access to the controller and handle asynchronous events from the system server.

## Implementation Risks
*   **Resource Usage**: Since it's always running, it must consume minimal memory/CPU.
*   **Binder Death**: Links to the death of the system `GameManagerService` to ensure clean shutdown.
