# HubDiscoveryInfo - Reverse Engineering Documentation

## Executive Summary
`HubDiscoveryInfo` is a container class that encapsulates the result of a hub endpoint discovery operation. It pairs a `HubEndpointInfo` (the endpoint found) with an optional `HubServiceInfo` (the specific service on that endpoint, if queried). It is returned by `ContextHubManager#findEndpoints`.

## Architecture Overview
- **Type**: Immutable Data Container.
- **Package**: `android.hardware.contexthub`.
- **Visibility**: `@SystemApi`.
- **API Surface**: Flagged with `Flags.FLAG_OFFLOAD_API`.

## Detailed Functionality
- **Endpoint Association**: Always contains a valid `HubEndpointInfo` representing the discovered entity.
- **Service Association**: Optionally contains `HubServiceInfo` if the discovery was filtered or matched by a specific service.

## Data Model
- `mEndpointInfo`: `HubEndpointInfo` (NonNull)
- `mServiceInfo`: `HubServiceInfo` (Nullable)

## API Reference
- `getHubEndpointInfo()`: Returns the endpoint details.
- `getHubServiceInfo()`: Returns the service details (if any).

## Java-to-C++ Translation Guide
### C++ Equivalent
```cpp
struct HubDiscoveryInfo {
    HubEndpointInfo endpointInfo;
    std::optional<HubServiceInfo> serviceInfo;
};
```
### Implementation Guidance
- This is a simple struct-like class.
- Ensure the C++ `HubEndpointInfo` and `HubServiceInfo` are properly defined before using this.
