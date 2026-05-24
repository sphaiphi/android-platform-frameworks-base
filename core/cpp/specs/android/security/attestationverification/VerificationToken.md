# VerificationToken - Reverse Engineering Documentation

## Executive Summary
`VerificationToken` is a proof of successful attestation verification. It allows passing the result of a verification between components without re-verifying (which is expensive).

## Architecture Overview
*   **Package**: `android.security.attestationverification`
*   **Type**: Class (Parcelable)
*   **Security**: Includes an HMAC to prevent tampering.

## Data Model
*   `mAttestationProfile`: The profile used.
*   `mLocalBindingType`: The binding type.
*   `mRequirements`: The requirements bundle.
*   `mVerificationResult`: The result flags.
*   `mVerificationTime`: Timestamp.
*   `mHmac`: HMAC of the token contents (keyed by system server).
*   `mUid`: UID of the creator (for scoping).

## Java-to-C++ Translation Guide
*   Structure mapping is straightforward.
*   **HMAC verification**: The C++ side (in system server) will need to generate/verify the HMAC. The Java side just transports it.
