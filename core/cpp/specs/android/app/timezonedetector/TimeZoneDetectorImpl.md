# TimeZoneDetectorImpl - Reverse Engineering Documentation

## Executive Summary
`TimeZoneDetectorImpl` is the concrete client implementation of `TimeZoneDetector`. It proxies calls to the `ITimeZoneDetectorService` Binder interface.

## Architecture Overview
- **Class**: `TimeZoneDetectorImpl`
- **Implements**: `TimeZoneDetector`
- **Dependencies**: `ITimeZoneDetectorService` (Binder), `ServiceManager`.

## Detailed Functionality

### Initialization
- Fetches `time_zone_detector` service from `ServiceManager`.
- Wraps it in the AIDL stub `ITimeZoneDetectorService.Stub.asInterface`.

### Method implementations
- **`suggestManualTimeZone`**: Proxies to service. Catches `RemoteException`, rethrows as `RuntimeException`.
- **`suggestTelephonyTimeZone`**: Proxies to service. Catches `RemoteException`.

## Java-to-C++ Translation Guide

### Binder Proxy
- **Java**: `ITimeZoneDetectorService.Stub.asInterface`.
- **C++**: `interface_cast<ITimeZoneDetectorService>(service)`.

### Exception Handling
- Standard Binder error handling applies.

## Implementation Risks
- **Service Dependency**: The service must be up.
