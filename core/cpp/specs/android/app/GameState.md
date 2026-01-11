# GameState - Reverse Engineering Documentation

## Executive Summary
`GameState` is a Parcelable class used by games to report their current state (Loading, Gameplay, etc.) to the system. This allows the system to optimize resources (e.g., power boost during loading).

## Architecture Overview
*   **Type**: Data Class.
*   **Fields**:
    *   `mIsLoading`: Boolean.
    *   `mMode`: `MODE_UNKNOWN`, `MODE_GAMEPLAY_INTERRUPTIBLE`, etc.
    *   `mLabel`, `mQuality`: Developer defined integers.

## Java-to-C++ Translation Guide
*   Struct/Class.

## Implementation Risks
*   None.
