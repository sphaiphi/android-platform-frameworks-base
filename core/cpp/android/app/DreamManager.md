# DreamManager - Reverse Engineering Documentation

## Executive Summary
`DreamManager` provides access to the Dream (screensaver) system service (`IDreamManager`). It allows querying/setting dream state, active dream components, and starting/stopping dreams.

## Architecture Overview
*   **Pattern**: Service Wrapper.
*   **Dependencies**: `IDreamManager` (Binder).

## Detailed Functionality
*   `startDream()` / `stopDream()`: Control dreaming state.
*   `setActiveDream(ComponentName)`: Sets the user's preferred dream.
*   `isDreaming()`: Check status.
*   `setDreamIsObscured`: Notify if dream is covered (e.g., by keyguard).

## Java-to-C++ Translation Guide
*   Binder proxy wrapper.

## Implementation Risks
*   None.
