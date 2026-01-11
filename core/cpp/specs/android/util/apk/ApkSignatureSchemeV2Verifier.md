# ApkSignatureSchemeV2Verifier - Reverse Engineering Documentation

## Executive Summary
Verifies APKs signed with the APK Signature Scheme v2. This scheme signs the binary contents of the APK (excluding the signing block itself), protecting against modification of ZIP metadata.

## Logic
1.  **Find Signature**: Uses `ApkSigningBlockUtils` to locate the APK Signing Block and the specific V2 Block ID (`0x7109871a`).
2.  **Verify**:
    *   Reads signers.
    *   For each signer, reads signatures, public key, and digests.
    *   Verifies the signature against the `signedData` blob using the public key.
    *   Verifies the content digests (computed over the APK contents) match the digests in `signedData`.
    *   Verifies the certificate matches the public key.

## Java-to-C++ Translation Guide
*   **Crypto**: Heavily relies on Java Cryptography Architecture (JCA) `Signature` and `MessageDigest`. C++ needs OpenSSL or BoringSSL.
*   **Structs**: The signing block format is a sequence of length-prefixed values.