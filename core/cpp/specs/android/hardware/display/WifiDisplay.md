# WifiDisplay - Reverse Engineering Documentation

## Executive Summary
`WifiDisplay` represents a discovered or connected Wi-Fi Display (Miracast) device. It contains the device's identity (address, name) and status (available, remembered).

## Data Model
- `mDeviceAddress`: MAC address (String).
- `mDeviceName`: Friendly name.
- `mDeviceAlias`: User-assigned alias.
- `mIsAvailable`: Reachable?
- `mCanConnect`: Ready for connection?
- `mIsRemembered`: Saved in persistent storage?

## Java-to-C++ Translation Guide
- **Immutable Struct**: Simple mapping.
- **Equality**: Based on address/name/alias.
- **Identity**: `hasSameAddress` compares only MAC address.
