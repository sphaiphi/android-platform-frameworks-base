# FaceCallback - Reverse Engineering Documentation

## Executive Summary
`FaceCallback` is a wrapper class that encapsulates various callback interfaces defined in `FaceManager` (`AuthenticationCallback`, `EnrollmentCallback`, `RemovalCallback`, etc.) and client-specific information (like `CryptoObject`, `Face` for removal). It acts as a bridge between the `FaceServiceReceiver` (AIDL callback) and the client's actual callback implementations.

## Architecture Overview
- **Role**: Callback Dispatcher / Holder.
- **Usage**: Used by `FaceManager` to route service events (from `FaceServiceReceiver`) to the appropriate client callback on the provided `Handler`/`Executor`.

## Detailed Functionality
- **Constructors**: Multiple constructors for different operation types (Authentication, Detection, Enrollment, Challenge, Feature Set/Get, Removal).
- **Dispatch Methods**: Methods like `sendSetFeatureCompleted`, `sendFaceDetected`, `sendErrorResult`, `sendAuthenticatedSucceeded`, etc.
    - These methods check if the relevant callback is non-null.
    - They invoke the specific method on the client callback interface.
    - Logic for error code mapping (Vendor vs Framework) resides here (`sendErrorResult`).
    - Logic for Help Code mapping resides here (`getHelpCode`).

## Data Model
- **Callbacks**: References to `AuthenticationCallback`, `EnrollmentCallback`, etc. (Nullable).
- **State**: `CryptoObject` (for auth), `Face` (for removal target).

## Java-to-C++ Translation Guide
- **Concept**: This class is primarily a client-side (Java Framework) helper. In C++ client code (if interacting with FaceService directly), a similar mechanism or a direct implementation of `IFaceServiceReceiver` stub would be needed.
- **Logic Mapping**:
    - **Error Mapping**: `clientErrMsgId = errMsgId == FACE_ERROR_VENDOR ? (vendorCode + FACE_ERROR_VENDOR_BASE) : errMsgId;`
    - **Help Mapping**: `acquireInfo == FACE_ACQUIRED_VENDOR ? vendorCode + FACE_ACQUIRED_VENDOR_BASE : acquireInfo;`

## Implementation Risks
- **Null Checks**: The class extensively checks for null callbacks before invoking. C++ implementation should ensure validity of pointers/references.
- **Concurrency**: Methods are generally called from an `Executor` in `FaceManager`. Thread safety depends on the client's callback implementation.

