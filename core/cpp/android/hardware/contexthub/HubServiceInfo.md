# HubServiceInfo - Reverse Engineering Documentation

## Executive Summary
`HubServiceInfo` describes a service provided by a Context Hub endpoint. It defines the service's interface descriptor, format (e.g., AIDL, Pigweed RPC), and versioning.

## Architecture Overview
- **Type**: Parcelable Data Class.
- **Package**: `android.hardware.contexthub`.

## Detailed Functionality
- **Formats**:
    - `FORMAT_CUSTOM` (0)
    - `FORMAT_AIDL` (1)
    - `FORMAT_PW_RPC_PROTOBUF` (2)
- **Versioning**: Major/Minor versioning scheme.
- **Descriptor**: String identifier for the service interface.

## Data Model
- `mServiceDescriptor`: `String`
- `mFormat`: `int` (ServiceFormat)
- `mMajorVersion`: `int`
- `mMinorVersion`: `int`

## Java-to-C++ Translation Guide
### C++ Equivalent
```cpp
struct HubServiceInfo {
    std::string serviceDescriptor;
    int32_t format;
    int32_t majorVersion;
    int32_t minorVersion;
};
```
### Implementation Guidance
- Mirror the `ServiceFormat` constants as an enum.
- Ensure Parcel serialization order is preserved.
