# FingerprintCallback - Reverse Engineering Documentation

## Executive Summary
`FingerprintCallback` encapsulates various client callbacks (`AuthenticationCallback`, `EnrollmentCallback`, `RemovalCallback`, etc.) and acts as a dispatcher for events coming from the Fingerprint Service.

## Architecture Overview
- **Role**: Callback Dispatcher / Holder.
- **Usage**: Used by `FingerprintManager` to route events from `FingerprintServiceReceiver` (AIDL) to client callbacks.

## Detailed Functionality
- **Constructors**: For Authentication, Detection, Enrollment, Challenge, and Removal.
- **Dispatch Methods**: `sendEnrollResult`, `sendRemovedResult`, `sendAuthenticatedSucceeded`, `sendAcquiredResult`, `sendErrorResult`, etc.
- **Logic**:
    - **Acquired Info Mapping**: Maps framework/vendor acquired info to client codes.
    - **Error Info Mapping**: Maps framework/vendor error codes to client codes.
    - **Removal Logic**: Handles single vs all removal logic (`REMOVE_SINGLE` vs `REMOVE_ALL`), checking against `mRemoveFingerprint`.

## Data Model
- **Callbacks**: Nullable references to client callbacks.
- **State**: `CryptoObject`, `RemoveRequest` type (`REMOVE_SINGLE` / `REMOVE_ALL`), `Fingerprint` target for removal.

## Java-to-C++ Translation Guide
- **Purpose**: Client-side helper. C++ equivalent would handle dispatching from `IFingerprintServiceReceiver` stub to application logic.
- **Constants**: Map `REMOVE_SINGLE` / `REMOVE_ALL`.
- **Mapping Logic**: Replicate `sendAcquiredResult` and `sendErrorResult` logic if direct HAL/Service interaction is needed in C++.

