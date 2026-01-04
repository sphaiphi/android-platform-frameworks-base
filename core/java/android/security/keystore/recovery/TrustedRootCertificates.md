# TrustedRootCertificates - Reverse Engineering Documentation

## Executive Summary
`TrustedRootCertificates` provides the built-in trusted root CA certificates for the Recoverable KeyStore service (specifically Google's Cloud Key Vault Service root).

## Functionality
*   **Data**: Contains Base64 encoded X.509 certificate for Google Cloud Key Vault Service V1.
*   **Testing**: Contains a test-only insecure certificate.
*   **Methods**: `getRootCertificates()`, `getRootCertificate(alias)`.

## Java-to-C++ Translation Guide
*   Ideally, these certificates should be stored in a secure location or embedded in the C++ binary if hardcoded.
*   Parsing requires an X.509 parser (BoringSSL).
