# DexLoadReporter - Reverse Engineering Documentation

## Executive Summary
`DexLoadReporter` reports the loading of DEX files (executable code) to the system. This allows the system to track secondary dex files for optimization (dexopt) and profiling.

## Architecture Overview
*   **Pattern**: Singleton.
*   **Dependencies**: `BaseDexClassLoader`, `ActivityThread` (for PM).

## Detailed Functionality
*   **Reporting**: `report` method called by ClassLoaders.
*   **Mechanism**: Calls `PackageManager.notifyDexLoad`.
*   **Profiling**: Registers secondary dex files for profiling (creating `.prof` files in `oat` directory) via `VMRuntime.registerAppInfo`.

## Java-to-C++ Translation Guide
*   **Runtime Specific**: Highly specific to the ART runtime and how it handles OAT/DEX files.
*   **Skip**: Likely not needed unless implementing a Java bytecode runtime.

## Implementation Risks
*   None (if skipped).
