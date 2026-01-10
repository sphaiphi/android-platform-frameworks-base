# DirectoryCertificateSource - Reverse Engineering Documentation

## Executive Summary
Abstract `CertificateSource` implementation that reads certificates from a directory (like `/system/etc/security/cacerts`).

## Functionality
*   **Lookup**: Uses OpenSSL-style hash naming (`<hash>.<index>`) to quickly find certificates by subject.
*   **Caching**: Caches loaded certificates (lazy loading).

## Java-to-C++ Translation Guide
*   Replicates standard OpenSSL/BoringSSL directory lookup logic (`X509_LOOKUP_hash_dir`).
