# IFingerprintAuthenticatorsRegisteredCallback - Reverse Engineering Documentation

## Executive Summary
`IFingerprintAuthenticatorsRegisteredCallback` is an AIDL callback to notify `FingerprintManager` when authenticators are registered.

## API Reference
- `void onAllAuthenticatorsRegistered(in List<FingerprintSensorPropertiesInternal> sensors)`: Oneway.

## Java-to-C++ Translation Guide
- **AIDL**: Generated C++ code (`BnFingerprintAuthenticatorsRegisteredCallback`).

