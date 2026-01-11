# StrictJarVerifier - Reverse Engineering Documentation

## Executive Summary
Manages the verification of signed JARs (V1 signature). It verifies `.SF` (Signature File) files against the APK's `.RSA`/`.DSA` signature block and then verifies the Manifest digest against the `.SF` file.

## Logic
*   **`verifyBytes`**: Verifies the PKCS7 block using the public key info.
*   **`verifyCertificate`**:
    *   Verifies the `.SF` file signature.
    *   Verifies the Manifest's main attributes digest against the `.SF` file.
    *   Verifies individual entry digests in the `.SF` file against the Manifest entries.
*   **`initEntry`**: Prepares a `VerifierEntry` (stream) to calculate the digest of a specific JAR entry as it is read.
*   **Digest Algorithms**: Tries SHA-512, SHA-384, SHA-256, SHA1 in order.

## Java-to-C++ Translation Guide
*   **PKCS7**: Critical dependency. Requires a crypto library capable of parsing and verifying CMS/PKCS7 structures.
*   **Digest**: Standard message digest operations.
