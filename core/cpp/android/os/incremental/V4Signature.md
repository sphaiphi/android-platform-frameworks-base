# V4Signature - Reverse Engineering Documentation

## Executive Summary
`V4Signature` implements the parsing and validation logic for Android's APK Signature Scheme v4. This scheme is designed for Incremental FS, separating the signature from the APK itself (stored in a `.idsig` file). It allows verifying the APK's integrity (via Merkle tree root hash) without reading the entire file.

## Architecture Overview
-   **Role**: Parser / Validator / Data Object.
-   **Format**: Binary format defined by APK Signature Scheme v4.
-   **Key Components**:
    -   `HashingInfo`: Algorithm, block size, salt, root hash.
    -   `SigningInfo`: APK digest, certificate, additional data, public key, signature.
    -   `SigningInfos`: Wrapper for the main signing info and optional blocks.

## Data Model

### Binary Structure (Serialization)
1.  **Version** (int LE)
2.  **Hashing Info**:
    -   Algorithm (int)
    -   Log2 Block Size (byte)
    -   Salt (Length-prefixed bytes)
    -   Raw Root Hash (Length-prefixed bytes)
3.  **Signing Info**:
    -   APK Digest (Length-prefixed bytes)
    -   Certificate (Length-prefixed bytes)
    -   Additional Data (Length-prefixed bytes)
    -   Public Key (Length-prefixed bytes)
    -   Signature Algorithm ID (int)
    -   Signature (Length-prefixed bytes)

## API Reference
-   `readFrom(InputStream | byte[] | ParcelFileDescriptor)`: Deserializes the signature.
-   `toByteArray()`: Serializes back to bytes.
-   `getSignedData(...)`: Constructs the blob that is actually signed (used for verification).
-   `isVersionSupported()`: Checks if version is 2.

## Java-to-C++ Translation Guide
-   **Existing C++ Impl**: There is almost certainly an existing C++ implementation in `system/security` or `libincfs`. Use that instead of rewriting.
-   **Endianness**: All integers are **Little Endian**.
-   **Constants**:
    -   `INCFS_MAX_SIGNATURE_SIZE = 8096`
    -   `HASHING_ALGORITHM_SHA256 = 1`
    -   `LOG2_BLOCK_SIZE_4096_BYTES = 12`

## Implementation Risks
-   **Security**: Incorrect parsing or validation bypasses app integrity checks.
-   **Buffer Overflows**: When parsing length-prefixed bytes manually in C++, ensure bounds checks (Java code does this via `readBytes` with `maxSize`).