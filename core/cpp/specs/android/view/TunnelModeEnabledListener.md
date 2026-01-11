# TunnelModeEnabledListener - Reverse Engineering Documentation

## Executive Summary
`TunnelModeEnabledListener` is a system-level observer that monitors when "Tunnel Mode" (a direct, low-latency path for hardware video decoding) is enabled or disabled in the compositor. it allows applications or system services to react to changes in the multimedia rendering path.

## Architecture Overview
*   **Role**: Global multimedia path monitor.
*   **Source**: Receives events from SurfaceFlinger.
*   **Threading**: Callbacks are executed on a user-provided `Executor`.

## Detailed Functionality
*   **`onTunnelModeEnabledChanged()`**: The primary callback reporting the current status.
*   **`register()`** / **`unregister()`**: Manages the native binder connection.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::gui::ITunnelModeEnabledListener` (AIDL).
*   **Lifecycle**: Managed via `NativeAllocationRegistry`.

## Implementation Risks
*   **Sync**: When tunnel mode is enabled, standard screen composition rules (like transparency or overlays) might change; listeners must be prepared for this transition.
