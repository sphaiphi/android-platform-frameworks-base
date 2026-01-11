# DeviceNotAssociatedException - Reverse Engineering Documentation

## Executive Summary
`DeviceNotAssociatedException` is a standard `RuntimeException` thrown when an application attempts to perform an operation on a companion device that has not been previously associated with the calling app.

## Architecture Overview
- **Inheritance**: Extends `java.lang.RuntimeException`.
- **Purpose**: To provide clear error reporting for unauthorized device access in the Companion Device Manager (CDM) framework.

## Detailed Functionality
- Automatically formats an error message including the device name (if provided).
- Used primarily in `CompanionDeviceManager` and `CompanionDeviceService` when verifying the existence of an association before starting transports or presence monitoring.

## Java-to-C++ Translation Guide
- **Error Handling**: Use `std::expected` or return a specific error code like `COMPANION_ERR_NOT_ASSOCIATED`.
- **RAII**: Ensure that any resources being initialized are cleaned up if this error state is detected early in a call sequence.

## Implementation Risks
- **Privacy**: The exception message includes the device name. Ensure this is not leaked to system logs in production if it contains PII (Personally Identifiable Information).
