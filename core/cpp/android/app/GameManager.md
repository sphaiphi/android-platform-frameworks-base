# GameManager - Reverse Engineering Documentation

## Executive Summary
`GameManager` provides the API for game-related features, such as querying/setting game modes (Standard, Performance, Battery) and managing game state.

## Architecture Overview
*   **Pattern**: Service Wrapper.
*   **Service**: `IGameManagerService`.

## Detailed Functionality
*   **Game Modes**: `getGameMode`, `setGameMode`.
*   **Game State**: `setGameState(GameState)`.
*   **Intervention**: `updateCustomGameModeConfiguration`.
*   **Graphics**: `notifyGraphicsEnvironmentSetup`.

## Java-to-C++ Translation Guide
*   Binder proxy.

## Implementation Risks
*   None.
