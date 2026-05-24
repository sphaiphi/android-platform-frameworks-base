# IAdbTransport - Reverse Engineering Documentation

## Executive Summary
`IAdbTransport` is an interface used by the system server to notify transport providers (like UsbDeviceManager) about ADB state changes.

## API Reference
| Method | Description |
|--------|-------------|
| `onAdbEnabled(boolean enabled, AdbTransportType type)` | Called when ADB is enabled/disabled for this transport. |

## Java-to-C++ Translation Guide
- **Usage**: Used internally within the system server framework.

## Source Reference
Defined in `IAdbTransport.aidl`.
