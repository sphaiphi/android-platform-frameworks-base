# Scrypt - Reverse Engineering Documentation

## Executive Summary
`Scrypt` is a Java wrapper class for the Scrypt password hashing algorithm (RFC 7914). It provides a mechanism to derive keys from passwords using memory-hard functions to resist brute-force attacks.

## Architecture Overview
*   **Package**: `android.security`
*   **Type**: Class (Public/Hidden)
*   **Dependencies**: Native JNI implementation.

## Detailed Functionality

### 1. Hashing
*   **Method**: `scrypt(byte[] password, byte[] salt, int n, int r, int p, int outLen)`
*   **Parameters**:
    *   `password`: Input key material.
    *   `salt`: Salt data.
    *   `n`: CPU/Memory cost parameter (must be a power of 2).
    *   `r`: Block size parameter.
    *   `p`: Parallelization parameter.
    *   `outLen`: Desired length of the output hash in bytes.
*   **Implementation**: Calls `nativeScrypt`.

## Java-to-C++ Translation Guide
*   **Native Mapping**: This class is a thin wrapper. The C++ implementation likely already exists (e.g., in `libcrypto` or `boringssl`). The Android framework C++ layer can call the underlying Scrypt implementation directly.
*   **Dependencies**: Ensure `libcrypto` (BoringSSL) is linked.

## Questions for C++ Team
*   Is this wrapper needed in the C++ framework layer, or should consumers just call BoringSSL's `EVP_PBE_scrypt` directly? (Likely the latter).
