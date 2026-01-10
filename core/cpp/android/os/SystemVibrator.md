# SystemVibrator - Reverse Engineering Documentation

## Executive Summary
`SystemVibrator` is the concrete implementation of the abstract `Vibrator` class used by the system. It delegates operations to the `VibratorManager` to handle multi-vibrator coordination and communicates with the `IVibratorManagerService` to perform actual hardware operations.

## Architecture Overview
-   **Inheritance**: Extends `Vibrator`.
-   **Composition**: Holds a reference to `VibratorManager` (which typically wraps `SystemVibratorManager`).
-   **Context**: Initialized with an Application or Activity context to access resources and system services.

## Detailed Functionality

### Delegation
Almost all operations (`vibrate`, `cancel`, `hasAmplitudeControl`) are delegated to the `mVibratorManager`.
-   **Vibration**: Converts `VibrationEffect` into a `CombinedVibration` (Parallel combination) and calls `mVibratorManager.vibrate()`. This ensures that even "single" vibrations are treated uniformly in the multi-vibrator architecture.

### Info Caching
-   **`getInfo()`**: Lazily retrieves and caches `VibratorInfo` from the manager. If multiple vibrators exist, it aggregates their info (though `SystemVibrator` usually represents the *default* vibrator, the logic here seems to iterate all IDs).

### State Listeners
-   **`addVibratorStateListener`**: Registers a listener that aggregates state from *all* physical vibrators. It uses a `MultiVibratorStateListener` helper to merge "isVibrating" states (logical OR).

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: Likely a `VibratorClient` class that wraps the Binder interface to `VibratorService`.
-   **Logic**: The aggregation logic for multi-vibrator state listeners needs to be replicated if C++ clients need to know "is *any* vibrator running?".

## Implementation Risks
-   **Synchronization**: The listener registration involves multiple Binder calls (one per vibrator ID). The failure recovery logic (`tryUnregisterBrokenListeners`) handles partial failures, which is complex to implement correctly in C++ without exceptions.
