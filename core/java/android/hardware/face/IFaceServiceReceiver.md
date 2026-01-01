# IFaceServiceReceiver - Reverse Engineering Documentation

## Executive Summary
`IFaceServiceReceiver` is the callback interface that clients must provide to `IFaceService` methods (like enroll, authenticate). The service calls these methods to deliver results asynchronously.

## Architecture Overview
- **Type**: AIDL Interface (oneway).

## API Reference
- `onEnrollResult(Face face, int remaining)`
- `onAcquired(int acquiredInfo, int vendorCode)`
- `onAuthenticationSucceeded(Face face, int userId, boolean isStrongBiometric)`
- `onFaceDetected(...)`
- `onAuthenticationFailed()`
- `onError(int error, int vendorCode)`
- `onRemoved(...)`
- `onFeatureSet(...)` / `onFeatureGet(...)`
- `onChallengeGenerated(...)`
- `onAuthenticationFrame(...)` / `onEnrollmentFrame(...)`

## Java-to-C++ Translation Guide
- **Callback Stub**: Clients implement the Stub (Bn) side. Service implements the Proxy (Bp) side.

