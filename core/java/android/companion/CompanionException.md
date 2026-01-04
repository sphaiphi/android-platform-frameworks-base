# CompanionException - Reverse Engineering Documentation

## Executive Summary
`CompanionException` is a custom `RuntimeException` used within the Companion Device Framework to signal failures specifically during the system data transfer process between the host and companion devices.

## Architecture Overview
- **Inheritance**: Extends `java.lang.RuntimeException`.
- **Purpose**: To provide a specific exception type for errors encountered in `CompanionDeviceManager` operations, particularly those involving `OutcomeReceiver` and system data sync.

## Detailed Functionality
- Acts as a marker exception for high-level CDM failures.
- Primarily used in the `SystemDataTransferCallbackProxy` to report errors from the system server back to the calling app's `OutcomeReceiver`.

## Java-to-C++ Translation Guide
- **Error Handling**: Instead of an exception class, C++ should use `std::expected<T, E>` where `E` is an error code or a specific `CompanionError` struct.
- **Mapping**: Map the string message to a diagnostic log or a structured error reason.

## Implementation Risks
- **Loss of Granularity**: As currently implemented in Java, it only carries a string message. C++ implementations should consider adding structured error codes (enums) for better programmatic handling.
