# AdbManager - Reverse Engineering Documentation

## Executive Summary
`AdbManager` provides a system API for managing Android Debug Bridge (ADB) functionality, specifically focusing on Wireless ADB features introduced in Android 11+. It acts as a client-side wrapper around the `IAdbManager` system service.

## Architecture Overview
- **Service Name**: `Context.ADB_SERVICE` ("adb").
- **Pattern**: Manager/Service pattern. `AdbManager` communicates with `IAdbManager` (Binder IPC) running in `SystemServer`.
- **Key Capability**: Managing Wireless Debugging (pairing, enabling, disabling, listing devices).

## Detailed Functionality

### `isAdbWifiSupported`
**Purpose**: Checks if the device hardware/software supports ADB over Wi-Fi.
**Mechanism**: RPC call to `mService.isAdbWifiSupported()`.

### `isAdbWifiQrSupported`
**Purpose**: Checks if the device supports QR-code-based pairing for ADB over Wi-Fi.
**Mechanism**: RPC call to `mService.isAdbWifiQrSupported()`.

## Data Model

### Constants / Intent Actions
- **`WIRELESS_DEBUG_STATE_CHANGED_ACTION`**: Broadcast when wireless debugging is enabled/disabled.
- **`WIRELESS_DEBUG_PAIRED_DEVICES_ACTION`**: Broadcast when the list of paired devices changes.
- **`WIRELESS_DEBUG_PAIRING_RESULT_ACTION`**: Broadcast with the result of a pairing attempt.

### Constants / Extras
- **`WIRELESS_STATUS_EXTRA`**: Int status code (Success, Fail, Cancelled, Connected, Disconnected).
- **`WIRELESS_PAIRING_CODE_EXTRA`**: String containing the 6-digit pairing code.
- **`WIRELESS_DEBUG_PORT_EXTRA`**: Int port number.

## Java-to-C++ Translation Guide
- **IPC**: This class wraps Binder calls. In C++, you would interact directly with the `IAdbManager` Bp (Binder Proxy) class generated from AIDL.
- **Permissions**: Calls require `android.Manifest.permission.MANAGE_DEBUGGING`.

## API Reference
| Method | Returns | Description |
|--------|---------|-------------|
| `isAdbWifiSupported()` | `boolean` | Returns true if Wireless ADB is supported. |
| `isAdbWifiQrSupported()` | `boolean` | Returns true if QR pairing is supported. |
