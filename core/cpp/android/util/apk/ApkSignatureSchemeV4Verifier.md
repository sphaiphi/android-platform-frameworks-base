# ApkSignatureSchemeV4Verifier - Reverse Engineering Documentation

## Executive Summary
Verifies APK Signature Scheme v4. This scheme is designed for **Incremental FS** (streaming installation). It uses a separate `.idsig` file or a V4 block within the APK. It relies on a Merkle Tree (fs-verity) for integrity.

## Key Algorithms
*   **Merkle Tree**: Verifies the `rootHash` of the APK matches the signed data.
*   **Input**: Can read from a separate `.idsig` file or from IncFS metadata.
*   **Consistency**: Checks if the v4 signature matches the v2/v3 digest to ensure the detached signature actually belongs to the APK.

## Java-to-C++ Translation Guide
*   **fs-verity**: The V4 format is closely tied to the Linux kernel's `fs-verity` feature.
*   **Serialization**: Uses a specific binary format (`V4Signature` class, likely defined elsewhere or serialized manually).