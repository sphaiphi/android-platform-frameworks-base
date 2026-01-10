# Helper - Reverse Engineering Documentation

## Executive Summary
A static utility class containing configuration constants and debug flags for the Translation framework.

## Data Model
*   `sDebug`, `sVerbose`: Static boolean flags for logging, set when service binds.
*   `ANIMATION_DURATION_MILLIS`: Constant (250ms) for UI translation animations.

## Java-to-C++ Translation Guide
*   **Constants**: Map to `constexpr` or static members.
*   **Flags**: Global atomic booleans or similar mechanism in C++.
