# HdmiControlServiceWrapper - Reverse Engineering Documentation

## Executive Summary
`HdmiControlServiceWrapper` is a test helper class. It provides a wrapper around `IHdmiControlService` that allows clients to create an `HdmiControlManager` backed by a mock or intercepted service.

## Architecture Overview
- **Role**: Test Wrapper / Mocking Point.
- **Test API**: `@TestApi`.

## Detailed Functionality
- **Service Stub**: Implements `IHdmiControlService.Stub` (the `mInterface` field) forwarding calls to methods in `HdmiControlServiceWrapper` itself.
- **Mocking**: Methods like `setPortInfo` and `setDeviceTypes` allow setting return values for the service methods.
- **Factory**: `createHdmiControlManager()` returns a manager instance using the internal stub.

## Data Model
- `mInfoList`: List of `HdmiPortInfo`.
- `mTypes`: Array of supported device types.

## Java-to-C++ Translation Guide
- **Relevance**: Likely not needed for the core production C++ implementation, unless a similar C++ testing framework is required.
- **Mocking**: In C++, standard mocking frameworks (gmock) would typically be used instead of a dedicated wrapper class like this.

