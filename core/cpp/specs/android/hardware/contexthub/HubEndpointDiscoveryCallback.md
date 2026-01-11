# HubEndpointDiscoveryCallback - Reverse Engineering Documentation

## Executive Summary
`HubEndpointDiscoveryCallback` is an interface used by clients to receive updates about the availability of Hub Endpoints. It notifies when endpoints start or stop.

## Architecture Overview
- **Type**: Callback Interface.
- **Package**: `android.hardware.contexthub`.
- **System API**: Yes.

## Detailed Functionality
- **`onEndpointsStarted`**: Invoked with a list of `HubDiscoveryInfo` when new endpoints are found/started.
- **`onEndpointsStopped`**: Invoked when endpoints are no longer available, providing a reason (from `HubEndpoint.Reason`).

## Java-to-C++ Translation Guide
- Implement as an abstract base class or listener interface in C++.
- `virtual void onEndpointsStarted(const std::vector<HubDiscoveryInfo>& info) = 0;`
