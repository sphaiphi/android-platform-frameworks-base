# GameModeInfo - Reverse Engineering Documentation

## Executive Summary
`GameModeInfo` provides information about the available and active game modes for a specific package.

## Architecture Overview
*   **Type**: Data Class.
*   **Fields**:
    *   `mActiveGameMode`: Current mode.
    *   `mAvailableGameModes`: Array of supported modes.
    *   `mOverriddenGameModes`: Array of modes overridden by developer config.
    *   `mConfigMap`: Map of Mode -> Configuration.

## Java-to-C++ Translation Guide
*   Struct/Class.

## Implementation Risks
*   None.
