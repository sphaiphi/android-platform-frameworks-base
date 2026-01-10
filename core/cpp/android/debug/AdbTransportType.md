# AdbTransportType - Reverse Engineering Documentation

## Executive Summary
`AdbTransportType` defines the enumeration for supported ADB transport mechanisms.

## Data Model
- **Backing Type**: `byte`.

### Enum Values
- `USB` (0)
- `WIFI` (1)

## Java-to-C++ Translation Guide
- **AIDL to C++**: Maps directly to a C++ `enum class AdbTransportType : int8_t`.

## Source Reference
Defined in `AdbTransportType.aidl`.
