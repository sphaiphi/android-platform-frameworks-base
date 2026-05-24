# ApkSignatureVerifier - Reverse Engineering Documentation

## Executive Summary
This class serves as the facade for verifying APK signatures. It attempts to verify the APK using the highest supported signature scheme version found (V4 down to V1) and falls back to older schemes if newer ones are not present, provided the minimum required scheme version is met.

## Architecture Overview
*   **Facade Pattern**: Abstracts the complexity of V1, V2, V3, and V4 verifiers.
*   **Result**: Returns `SigningDetails` containing certificates and schema version.

## Key Algorithms
*   **`verify`**:
    1.  Checks `minSignatureSchemeVersion`.
    2.  Attempts V4 (`verifyV4Signature`).
    3.  If V4 missing/fails, attempts V3 (`verifyV3Signature`).
    4.  If V3 missing/fails, attempts V2 (`verifyV2Signature`).
    5.  If V2 missing/fails, attempts V1 (JAR signing) via `verifyV1Signature`.
*   **`verifyV1Signature`**: Uses `StrictJarFile` to verify the JAR signature (MANIFEST.MF, .SF, .RSA/.DSA).

## Java-to-C++ Translation Guide
*   **Logic**: The fallback logic is a simple state machine.
*   **Dependencies**: Requires implementations of the specific scheme verifiers.