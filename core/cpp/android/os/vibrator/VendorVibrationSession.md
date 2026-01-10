# VendorVibrationSession - Reverse Engineering Documentation

## Executive Summary
`VendorVibrationSession` provides a mechanism for vendor-specific applications (privileged) to gain temporary, direct, and potentially exclusive control over the vibrator hardware. This is likely used for specialized calibration tools, factory tests, or advanced OEM features that bypass standard framework scheduling/mixing policies.

## Architecture Overview
-   **Pattern**: Session/Proxy.
-   **Interfaces**: Wraps `IVibrationSession` (Binder).
-   **Lifecycle**: `vibrate()`, `cancel()`, `close()`. Implements `AutoCloseable`.
-   **Callbacks**: `VendorVibrationSession.Callback` handles `onStarted`, `onFinishing`, `onFinished`.

## Detailed Functionality
-   **Concurrency**: Bypasses standard framework synchronization? The Javadoc says "Vendor should control concurrency behavior at hardware level".
-   **Permission**: Requires `android.Manifest.permission.VIBRATE`.
-   **Status Codes**: Success, Ignored, Unsupported, Canceled, Unknown.

## API Reference
-   `vibrate(VibrationEffect, String reason)`: Sends vibration immediately.
-   `close()`: Ends session gracefully (waits for finish).
-   `cancel()`: Ends session abruptly.

## Java-to-C++ Translation Guide
-   **Binder**: This is a client-side wrapper for an AIDL interface. The C++ equivalent is the `BnVibrationSession` (Server) and `BpVibrationSession` (Client).
-   **Usage**: The native `VibratorService` likely implements `IVibrationSession`.

## Implementation Risks
-   **Resource Locking**: This session mechanism implies locking the vibrator resource. If the client dies without closing, the service must handle cleanup (Link-to-Death).
