# SELinux - Reverse Engineering Documentation

## Executive Summary
`SELinux` provides Java bindings for the `libselinux` library. It allows checking context, setting file contexts, and checking permissions (AVC) from Java.

## Architecture Overview
-   **Role**: Security Context Manager.
-   **Native**: JNI wrappers around `libselinux`.

## API Reference
-   `isSELinuxEnabled()`, `isSELinuxEnforced()`.
-   `getFileContext(String/FileDescriptor)`.
-   `checkSELinuxAccess(scon, tcon, class, perm)`: Checks if a source context can access a target context.
-   `restorecon(String/File)`: Restores default security context for a file (based on `file_contexts`).

## Java-to-C++ Translation Guide
-   **Equivalent**: `selinux/selinux.h` and `selinux/android.h`.
-   **Functions**: `is_selinux_enabled`, `getfilecon`, `selinux_check_access`, `selinux_android_restorecon`.

## Implementation Risks
-   **Blocking**: `restorecon` can be slow and block I/O.
-   **Security**: Incorrect usage can lead to permission denials or security holes (if contexts are set too broadly).
