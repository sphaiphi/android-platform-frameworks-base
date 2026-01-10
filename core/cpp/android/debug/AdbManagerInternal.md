# AdbManagerInternal - Reverse Engineering Documentation

## Executive Summary
`AdbManagerInternal` is an abstract class defining the local system service interface for ADB management. It allows other system services (running within the same `SystemServer` process) to interact with the ADB service without going through Binder IPC.

## Architecture Overview
- **Pattern**: Local Service Pattern (`LocalServices.getService(AdbManagerInternal.class)`).
- **Scope**: Internal to the System Server. Not exposed to apps.
- **Role**: Bridges the ADB service with other system components (like USB Manager or Wi-Fi Manager).

## Detailed Functionality

### Transport Management
- `registerTransport(IAdbTransport)`: Registers a new ADB transport (e.g., USB, Wi-Fi).
- `unregisterTransport(IAdbTransport)`: Removes a transport.
- `startAdbdForTransport(byte type)`: Signals `adbd` to start listening on a specific transport.
- `stopAdbdForTransport(byte type)`: Signals `adbd` to stop listening.

### Key Management
- `getAdbKeysFile()`: Returns the persistent `adb_keys` file path (usually `/data/misc/adb/adb_keys`).
- `getAdbTempKeysFile()`: Returns the temporary keys file path.
- `notifyKeyFilesUpdated()`: Tells the service to reload keys (e.g., after a user manually authorizes a key).

### State
- `isAdbEnabled(byte transportType)`: Checks if a specific ADB transport is currently active.

## Java-to-C++ Translation Guide
- **Implementation**: This is a Java interface definition. The implementation resides in `com.android.server.adb.AdbService`.
- **C++ Equivalent**: If porting the System Server logic, this represents the internal API surface of the ADB Controller.

## Data Structures
- **Transport Types**: Defined in `AdbTransportType` (USB=0, WIFI=1).
