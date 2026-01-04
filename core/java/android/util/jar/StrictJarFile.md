# StrictJarFile - Reverse Engineering Documentation

## Executive Summary
A subset of `JarFile` API implemented securely. Used for verifying JAR/APK V1 signatures. It is stricter than `java.util.jar.JarFile` regarding zip structure and signature verification.

## Architecture
*   **Native wrapper**: Wraps `libziparchive` (via `nativeOpenJarFile`).
*   **Manifest**: Parses `META-INF/MANIFEST.MF` using `StrictJarManifest`.
*   **Verifier**: Uses `StrictJarVerifier` to check `.SF` and `.RSA` files.

## Key Algorithms
*   **Iteration**: Iterates via native handle.
*   **Verification**:
    *   Parses signature files.
    *   Verifies PKCS7 block (`StrictJarVerifier.verifyBytes`).
    *   Matches digests in `.SF` file against Manifest.
    *   Matches digests in Manifest against actual file contents (when `getInputStream` is read).

## Java-to-C++ Translation Guide
*   **Libziparchive**: This class already wraps a C++ library (`libziparchive`). The logic is partially in Java (Manifest parsing, crypto verification) and partially native (ZIP iteration/extraction).
*   **PKCS7**: Uses `sun.security.pkcs.PKCS7`. C++ would need a crypto lib.
