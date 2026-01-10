# AttestationVerificationManager - Reverse Engineering Documentation

## Executive Summary
`AttestationVerificationManager` is the entry point for verifying remote attestations. It verifies that a remote environment meets specific security requirements defined by an `AttestationProfile`.

## Architecture Overview
*   **Package**: `android.security.attestationverification`
*   **Type**: Class (System Service)
*   **Service Name**: `Context.ATTESTATION_VERIFICATION_SERVICE`
*   **Dependencies**: `IAttestationVerificationManagerService`.

## Detailed Functionality

### 1. Verification
*   **Method**: `verifyAttestation`
*   **Process**:
    1.  Takes a profile, local binding type, requirements bundle, and the attestation blob.
    2.  Calls the system service asynchronously (`AndroidFuture`).
    3.  Returns a `VerificationToken` on success via callback.
*   **Local Binding**: Defines how the attestation is bound to the channel (e.g., Public Key, Challenge).

### 2. Token Verification
*   **Method**: `verifyToken`
*   **Process**:
    1.  Verifies a previously issued `VerificationToken`.
    2.  Checks if the token is valid and not expired (max age 1 hour).
    3.  Synchronous call to the service.

## Data Model
*   **LocalBindingType**: `UNKNOWN`, `APP_DEFINED`, `PUBLIC_KEY`, `CHALLENGE`.
*   **VerificationResult**: Bitmap flags indicating failure reasons (Certs, Local Binding, Profile, etc.).

## Java-to-C++ Translation Guide
*   **Async**: Java uses `AndroidFuture` and `Executor`. C++ should use `std::future` or callback interfaces.
*   **Bundles**: `requirements` is a `Bundle`. Map this to `PersistableBundle` or a map in C++.
