# PendingInsetsController - Reverse Engineering Documentation

## Executive Summary
`PendingInsetsController` is a temporary implementation of the `WindowInsetsController` interface. It is used during the early stages of activity startup (before the view is attached to a window) to buffer requests to show or hide system bars. Once the view hierarchy is fully established, it "replays" these requests onto the real `InsetsController`.

## Architecture Overview
*   **Role**: Early-initialization buffer for insets.
*   **State**: Records a list of `PendingRequest` objects.
*   **Transition**: `replayAndAttach()` transfers all buffered state to a target `InsetsController`.

## Detailed Functionality

### 1. Request Buffering
*   **`show()` / `hide()`**: Adds a `ShowRequest` or `HideRequest` to an internal list instead of executing it.
*   **`setSystemBarsAppearance()`**: Records the desired appearance bitmask and mask.

### 2. State Simulation
*   **`getState()`**: Returns a dummy `InsetsState` since the real one is not yet available from the server.
*   **`getRequestedVisibleTypes()`**: Returns the locally buffered visibility state.

## Java-to-C++ Translation Guide
*   **Pattern**: Memento / Command Pattern.
*   **Lifecycle**: In C++, this component should exist only until the `RootView` is attached.

## Implementation Risks
*   **Sync Errors**: If the replay happens after the window has already performed its first layout, the user may see a brief flicker of system bars before they are hidden.
