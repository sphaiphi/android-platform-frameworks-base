# AttestationProfile - Reverse Engineering Documentation

## Executive Summary
`AttestationProfile` defines the security requirements for verifying an attestation. It can represent a system-defined profile (like "Peer Device") or an app-defined profile.

## Architecture Overview
*   **Package**: `android.security.attestationverification`
*   **Type**: Class (Parcelable)
*   **Components**:
    *   `mAttestationProfileId`: ID of the profile.
    *   `mPackageName`, `mProfileName`: For app-defined profiles.

## Data Model
*   **Ids**:
    *   `PROFILE_UNKNOWN` (0)
    *   `PROFILE_APP_DEFINED` (1)
    *   `PROFILE_SELF_TRUSTED` (2)
    *   `PROFILE_PEER_DEVICE` (3)

## Java-to-C++ Translation Guide
*   Map to a struct.
*   Note the validation logic in constructors (e.g., preventing `APP_DEFINED` usage in the int-only constructor).
