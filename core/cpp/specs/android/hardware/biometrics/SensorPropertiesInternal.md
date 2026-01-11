# SensorPropertiesInternal - Reverse Engineering Documentation

## Executive Summary
`SensorPropertiesInternal` is the internal Parcelable used to transmit sensor properties from the system service to clients. It is a superset of the public properties, including internal configuration flags.

## Detailed Functionality
- **Basic**: `sensorId`, `sensorStrength`.
- **Policy**: `maxEnrollmentsPerUser`.
- **Components**: List of `ComponentInfoInternal`.
- **Lockout**: `resetLockoutRequiresHardwareAuthToken`, `resetLockoutRequiresChallenge`.

## Java-to-C++ Translation Guide
- **Struct**: `struct SensorPropertiesInternal`.
- **Logic**: Use this struct to configure the framework's behavior regarding lockout reset policies.

## Implementation Risks
- Ensuring `resetLockoutRequires...` flags are respected during lockout reset operations to maintain security model.
