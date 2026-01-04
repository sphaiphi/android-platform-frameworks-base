# PairDevice - Reverse Engineering Documentation

## Executive Summary
`PairDevice` is a data structure (Parcelable) representing a client device connected or paired via Wireless ADB.

## Data Model
- `String name`: Human-readable device name (e.g., "MacBook Pro").
- `String guid`: Unique identifier for the device.
- `boolean connected`: Connection state.

## Java-to-C++ Translation Guide
- **C++**: Struct with `std::string` name/guid and `bool`.

## Source Reference
Defined in `PairDevice.aidl`.
