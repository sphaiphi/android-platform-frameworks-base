# CrossWindowBlurListeners - Reverse Engineering Documentation

## Executive Summary
`CrossWindowBlurListeners` is a singleton manager that tracks listeners for changes in the system-wide cross-window blur state. Cross-window blur is a GPU-intensive effect where one window blurs the content of windows behind it. The state can change based on device capabilities, power saving modes, or user settings.

## Architecture Overview
*   **Role**: Global state observer for blur effects.
*   **Singleton**: Accessed via `getInstance()`.
*   **IPC**: Registers an `ICrossWindowBlurEnabledListener` with the `WindowManagerService` (WMS).

## Detailed Functionality

### 1. State Tracking
*   **`isCrossWindowBlurEnabled()`**: Returns the current status of blur support in the system.
*   **`CROSS_WINDOW_BLUR_SUPPORTED`**: A static constant derived from system properties (`ro.surface_flinger.supports_background_blur`).

### 2. Listener Management
*   **`addListener()`**: Adds a consumer to be notified of state changes. It immediately notifies the new listener of the current state.
*   **`removeListener()`**: Unregisters a consumer. If no listeners remain, it detaches the internal binder listener from WMS.

## Java-to-C++ Translation Guide
*   **Service Link**: Communicates with `IWindowManager`. In C++, use `sp<IWindowManager>`.
*   **Callback**: Implement the `BnCrossWindowBlurEnabledListener` AIDL interface.

## Implementation Risks
*   **Threading**: Callbacks from WMS arrive on a binder thread; the manager must ensure they are dispatched correctly to the user-provided `Executor`.
*   **GPU Overhead**: Apps should use the state from this manager to fall back to a non-blurred background if the feature is disabled, preventing rendering artifacts or performance drops.
