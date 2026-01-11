# FileIntegrityManager - Reverse Engineering Documentation

## Executive Summary
`FileIntegrityManager` provides access to file integrity features, specifically fs-verity. It allows applications to enable fs-verity on files and retrieve their digests.

## Architecture Overview
*   **Package**: `android.security`
*   **Type**: Class (Public, System Service)
*   **Service Name**: `Context.FILE_INTEGRITY_SERVICE` ("file_integrity")
*   **Dependencies**:
    *   `IFileIntegrityService` (AIDL interface to system server)
    *   `com.android.internal.security.VerityUtils`
    *   `android.os.ParcelFileDescriptor`

## Detailed Functionality

### 1. Support Check
*   **Method**: `isApkVeritySupported()`
*   **Logic**: Delegates to `VerityUtils.isFsVeritySupported()`. Checks if the underlying kernel/file system supports the feature.

### 2. Enable Fs-Verity
*   **Method**: `setupFsVerity(File file)`
*   **Constraints**:
    *   File must be an **absolute path**.
    *   Throws `IllegalArgumentException` if relative.
*   **Mechanism**:
    1.  Opens the file via `ParcelFileDescriptor` (Read/Write).
    2.  Calls `mService.createAuthToken(authFd)` to get an `IFsveritySetupAuthToken`. This likely ensures the caller has write access.
    3.  Calls `mService.setupFsverity(authToken, filePath, packageName)`.
    4.  Handles `RemoteException` and `ErrnoException`.
*   **Configuration**: Uses default SHA-256 digest, 4K block size, no salt (implied by API documentation).

### 3. Get Digest
*   **Method**: `getFsVerityDigest(File file)`
*   **Logic**: Delegates to `VerityUtils.getFsverityDigest(file.getPath())`. Returns `byte[]` or `null`.

### 4. Legacy API
*   **Method**: `isAppSourceCertificateTrusted(X509Certificate certificate)`
*   **Status**: Deprecated. Always returns `false`.

## API Reference
*   `boolean isApkVeritySupported()`
*   `void setupFsVerity(@NonNull File file) throws IOException`
*   `@Nullable byte[] getFsVerityDigest(@NonNull File file) throws IOException`

## Java-to-C++ Translation Guide
*   **File Descriptors**: `ParcelFileDescriptor` maps to standard file descriptors (`int fd`) in C++.
*   **Path Handling**: Ensure absolute path validation mimics Java's `File.isAbsolute()`.
*   **IPC**: Uses `IFileIntegrityService` Binder interface.
*   **Exceptions**: Map `ErrnoException` to standard C++ error handling (e.g., `std::error_code` or `errno`).

## Implementation Risks
*   **File Ownership**: The API implies specific ownership/write permission checks (`createAuthToken`). C++ implementation must ensure it respects the security model where the service verifies the caller's access to the file.
