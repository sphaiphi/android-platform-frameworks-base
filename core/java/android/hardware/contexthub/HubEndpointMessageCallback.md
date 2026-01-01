# HubEndpointMessageCallback - Reverse Engineering Documentation

## Executive Summary
`HubEndpointMessageCallback` is an interface for receiving data messages within an established `HubEndpointSession`.

## Architecture Overview
- **Type**: Callback Interface.
- **Package**: `android.hardware.contexthub`.

## Detailed Functionality
- **`onMessageReceived`**: Delivers a `HubMessage` associated with a specific `HubEndpointSession`.

## Java-to-C++ Translation Guide
- Map to a C++ pure virtual interface.
- `virtual void onMessageReceived(std::shared_ptr<HubEndpointSession> session, const HubMessage& message) = 0;`
