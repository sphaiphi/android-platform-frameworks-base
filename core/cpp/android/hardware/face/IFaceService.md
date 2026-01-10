# IFaceService - Reverse Engineering Documentation

## Executive Summary
`IFaceService` is the main AIDL interface for the Face Service. It defines the operations that clients (like `FaceManager`) can invoke on the system server.

## Architecture Overview
- **Type**: AIDL Interface.
- **Permissions**: Annotations like `@EnforcePermission("USE_BIOMETRIC_INTERNAL")` and `MANAGE_BIOMETRIC` indicate security requirements.

## API Reference (Key Methods)
- `createTestSession`
- `dumpSensorServiceStateProto`
- `getSensorPropertiesInternal` / `getSensorProperties`
- `authenticate` / `detectFace` / `cancelAuthentication`
- `prepareForAuthentication` / `startPreparedClient`
- `enroll` / `enrollRemotely` / `cancelEnrollment`
- `remove` / `removeAll`
- `getEnrolledFaces` / `hasEnrolledFaces`
- `isHardwareDetected`
- `generateChallenge` / `revokeChallenge`
- `resetLockout`
- `setFeature` / `getFeature`
- `registerAuthenticators` / `addAuthenticatorsRegisteredCallback`
- `registerAuthenticationStateListener` / `registerBiometricStateListener`

## Java-to-C++ Translation Guide
- **Binder**: This defines the IPC contract. C++ implementation will be generated.
- **Signatures**: Methods take `IBinder token`, `IFaceServiceReceiver receiver`, options/configs as Parcelables.

