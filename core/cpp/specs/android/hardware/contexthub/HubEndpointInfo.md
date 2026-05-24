# HubEndpointInfo - Reverse Engineering Documentation

## Executive Summary
`HubEndpointInfo` is a Parcelable class that provides a detailed description of an endpoint in the ContextHub ecosystem. It uniquely identifies an endpoint and describes its properties such as type, name, version, required permissions, and provided services.

## Architecture Overview
- **Type**: Parcelable Data Class.
- **Package**: `android.hardware.contexthub`.
- **Identity**: Defines `HubEndpointIdentifier` (Hub ID + Endpoint ID).

## Detailed Functionality

### Identification
- **HubEndpointIdentifier**: A composite key (Hub ID + Endpoint ID).
- **Types**: `FRAMEWORK`, `APP`, `NATIVE`, `NANOAPP`, `HUB_ENDPOINT`.

### Properties
- **Name**: Human-readable name.
- **Tag**: Submodule identifier (useful when multiple endpoints share a name).
- **Version**: Implementation version (context-dependent format).
- **Permissions**: List of Android permissions required to interact with this endpoint.
- **Services**: List of `HubServiceInfo` exposed by this endpoint.

## Data Model
- `mId`: `HubEndpointIdentifier`
- `mType`: `int` (EndpointType)
- `mName`: `String`
- `mVersion`: `int`
- `mTag`: `String` (Nullable)
- `mRequiredPermissions`: `List<String>`
- `mHubServiceInfos`: `List<HubServiceInfo>`

## API Reference
- `getIdentifier()`
- `getType()`, `getName()`, `getVersion()`, `getTag()`
- `getRequiredPermissions()`, `getServiceInfoCollection()`

## Java-to-C++ Translation Guide
### C++ Equivalent
```cpp
struct HubEndpointInfo {
    struct Identifier {
        int64_t hubId;
        int64_t endpointId;
    } id;
    int32_t type;
    std::string name;
    int32_t version;
    std::optional<std::string> tag;
    std::vector<std::string> requiredPermissions;
    std::vector<HubServiceInfo> services;
};
```
### Implementation Guidance
- Ensure strict parity with the Parcel read/write order for Binder communication.
