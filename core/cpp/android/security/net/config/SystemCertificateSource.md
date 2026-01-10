# SystemCertificateSource - Reverse Engineering Documentation

## Executive Summary
`DirectoryCertificateSource` pointing to the system CA store.

## Configuration
*   **Path**:
    1.  `/apex/com.android.conscrypt/cacerts` (if exists).
    2.  `$ANDROID_ROOT/etc/security/cacerts` (fallback).
*   **Exclusions**: Checks `cacerts-removed` in user config to filter out system certs disabled by the user.

## Java-to-C++ Translation Guide
*   Standard system path configuration.
