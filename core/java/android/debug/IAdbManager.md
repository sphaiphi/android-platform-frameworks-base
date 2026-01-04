# IAdbManager - Reverse Engineering Documentation

## Executive Summary
`IAdbManager` is the core AIDL interface defining the remote API for the ADB system service. It controls authentication keys, wireless debugging pairing, and configuration.

## API Reference

### Key Management
- `allowDebugging(boolean alwaysAllow, String publicKey)`: Authorizes a host key.
- `denyDebugging()`: Rejects the current connection request.
- `clearDebuggingKeys()`: Revokes all authorized keys.

### Wireless Debugging
- `allowWirelessDebugging(boolean alwaysAllow, String bssid)`: Authorizes a network.
- `denyWirelessDebugging()`: Rejects a wireless connection.
- `getPairedDevices()`: Returns `FingerprintAndPairDevice[]`.
- `unpairDevice(String fingerprint)`: Revokes a specific device.
- `enablePairingByPairingCode()`: Starts pairing mode (Code).
- `enablePairingByQrCode(String serviceName, String password)`: Starts pairing mode (QR).
- `disablePairing()`: Stops pairing mode.
- `getAdbWirelessPort()`: Returns the listening port.

### Callbacks
- `registerCallback(IAdbCallback)`: adds a listener.
- `unregisterCallback(IAdbCallback)`: removes a listener.

## Java-to-C++ Translation Guide
- **Core Service**: This interface defines the boundary between client apps (Settings, SystemUI) and the system server.
- **Implementation**: Implemented in Java (`AdbService`), but interacts heavily with the native `adbd` daemon via properties or socket.

## Source Reference
Defined in `IAdbManager.aidl`.
