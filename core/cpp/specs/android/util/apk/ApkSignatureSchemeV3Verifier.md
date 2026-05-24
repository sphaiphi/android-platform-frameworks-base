# ApkSignatureSchemeV3Verifier - Reverse Engineering Documentation

## Executive Summary
Verifies APK Signature Scheme v3 (and v3.1). V3 builds on V2 but adds support for **Key Rotation** via a "Proof-of-Rotation" struct.

## Differences from V2
*   **Block ID**: `0xf05368c0` (V3) and `0x1b93ad61` (V3.1).
*   **Proof of Rotation**: The signing block contains a singly-linked list of certificates, where each certificate signs the next one in the chain. This allows the APK to be signed by a new key while proving trust from the old key.
*   **SDK Versioning**: Supports `minSdkVersion` and `maxSdkVersion` attributes to allow different signatures for different platform versions.

## Java-to-C++ Translation Guide
*   **Recursion**: Proof of rotation verification involves walking the certificate chain.
*   **Attributes**: Parsing of additional attributes in the signing block is critical.