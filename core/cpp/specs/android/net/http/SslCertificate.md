# SslCertificate.java - Reverse Engineering Documentation

## Executive Summary
`SslCertificate` represents an X.509 certificate and provides helper methods to extract and format its fields (Subject, Issuer, Validity Period) for UI display or debugging. It also supports saving/restoring its state via a `Bundle`.

## Architecture Overview
- **Type**: Data / Utility Class
- **Package**: `android.net.http`
- **Dependencies**: `java.security.cert.X509Certificate`.

## Data Model

### DName (Inner Class)
Helper for Distinguished Names (DN).
-   `mDName`: Full string (e.g., "CN=foo, O=bar").
-   `mCName` (Common Name), `mOName` (Organization), `mUName` (Organizational Unit).
-   **Parsing**: Uses `com.android.internal.org.bouncycastle.asn1.x509.X509Name` to parse the DN string and extract components.

### SslCertificate Fields
-   `mIssuedTo`: `DName` of subject.
-   `mIssuedBy`: `DName` of issuer.
-   `mValidNotBefore`: `Date`.
-   `mValidNotAfter`: `Date`.
-   `mX509Certificate`: Underlying `X509Certificate` object.

## Functionality
-   **Parsing**: Extracts fields from `X509Certificate`.
-   **Serialization**: `saveState`/`restoreState` converts to/from `Bundle` (keys: "issued-to", "x509-certificate", etc.).
-   **Formatting**: `formatDate` uses `DateFormat.getMediumDateFormat`.
-   **Fingerprinting**: `getDigest` computes SHA1/SHA256 hashes formatted as hex strings (e.g., "AA:BB:...").

## Java-to-C++ Translation Guide
-   **Library**: OpenSSL or BoringSSL (`X509*` struct).
-   **DN Parsing**: Use `X509_get_subject_name`, `X509_NAME_get_entry`, `X509_NAME_ENTRY_get_data`.
-   **Date Parsing**: Convert `ASN1_TIME` to `tm` struct or time_t.
-   **Fingerprint**: `X509_digest`.
