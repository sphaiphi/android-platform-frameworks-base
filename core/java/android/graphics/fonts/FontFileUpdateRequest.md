# FontFileUpdateRequest - Reverse Engineering Documentation

## Executive Summary
`FontFileUpdateRequest` represents a request to introduce a new font file to the system. It pairs a file descriptor with a cryptographic signature for verification.

## Architecture Overview
-   **Data Carrier**: Holds a `ParcelFileDescriptor` and a `byte[]` signature.
-   **Security**: The signature is a PKCS#7 detached signature used by the system to verify the font file's integrity and authenticity.

## Detailed Functionality
-   **Constructor**: Takes `ParcelFileDescriptor` and `byte[] signature`.
-   **Getters**: Accessors for the FD and signature.

## Java-to-C++ Translation Guide
-   **File Descriptor**: `ParcelFileDescriptor` maps to a native file descriptor (`int fd`).
-   **Signature**: `std::vector<uint8_t>` or similar binary container.

## Source Reference
Defined in `FontFileUpdateRequest.java`.
