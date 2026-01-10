# CertificateSource - Reverse Engineering Documentation

## Executive Summary
Interface for providing X.509 certificates to the Network Security Config system.

## API Reference
*   `getCertificates()`
*   `findBySubjectAndPublicKey`
*   `findByIssuerAndSignature`
*   `findAllByIssuerAndSignature`
*   `handleTrustStorageUpdate`

## Java-to-C++ Translation Guide
*   Abstract base class (interface).
*   Implementations: `SystemCertificateSource`, `UserCertificateSource`, `KeyStoreCertificateSource`.
