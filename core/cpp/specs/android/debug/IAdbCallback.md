# IAdbCallback - Reverse Engineering Documentation

## Executive Summary
`IAdbCallback` is a callback interface for listening to ADB debugging state changes.

## API Reference
| Method | Description |
|--------|-------------|
| `onDebuggingChanged(boolean enabled, AdbTransportType type)` | Called when debugging is enabled/disabled for a specific transport. |

## Java-to-C++ Translation Guide
- **IPC**: One-way AIDL interface.
- **C++**: `class BnAdbCallback` (Stub) and `class BpAdbCallback` (Proxy).

## Source Reference
Defined in `IAdbCallback.aidl`.
