# SerialManager - Reverse Engineering Documentation

## Executive Summary
`SerialManager` provides a mechanism to interact with serial ports on devices that support them. It allows listing available ports and opening them for bidirectional communication.

## Architecture Overview
This is a `SystemService` (`SERIAL_SERVICE`). It acts as a client to `ISerialManager`, which handles the low-level serial device management in the system server.

## Detailed Functionality

### Port Management
- `getSerialPorts()`: Returns a list of strings representing available serial device nodes (e.g., `/dev/ttyS0`).
- `openSerialPort(name, speed)`: Opens a port at a specific baud rate.

### Communication
- Returns a `SerialPort` object which provides the actual read/write interface.

## Data Model
- **Baud Rates**: Supports standard rates from 50 to 4,000,000.

## Java-to-C++ Translation Guide
- **Service Proxy**: `ISerialManager` -> AIDL generated C++ client.
- **IO**: `ParcelFileDescriptor` -> `android::base::unique_fd` or `int`.

## Implementation Risks
- Permissions: Requires `android.permission.SERIAL_PORT`.
- Hardware Support: Very few standard Android devices expose serial ports to applications.
