# X509TrustManagerExtensions.java - Reverse Engineering Documentation

## Executive Summary
`X509TrustManagerExtensions` is a wrapper around `X509TrustManager` (specifically Android's `TrustManagerImpl` from Conscrypt) to expose extended verification capabilities not available in the standard Java API, such as hostname verification during certificate checks and Certificate Transparency (CT) verification.

## Architecture Overview
- **Type**: Wrapper / Extension
- **Package**: `android.net.http`
- **Target**: `javax.net.ssl.X509TrustManager`.
- **Backend**: `com.android.org.conscrypt.TrustManagerImpl`.

## Detailed Functionality

### Construction
-   Checks if the passed `tm` is an instance of `TrustManagerImpl`.
-   If not, attempts to use reflection to find methods like `checkServerTrusted` with extra arguments (hostname, OCSP data, etc.). This supports "duck typing" for custom TrustManagers that implement the Android interface pattern without extending the internal class.

### Extended Verification (`checkServerTrusted`)
1.  **Hostname Aware**: `checkServerTrusted(chain, authType, host)`.
    -   Standard `X509TrustManager` doesn't take a hostname, making it impossible to check for Subject Alternative Name (SAN) matches during the trust check itself. This extension adds that.
2.  **CT/OCSP Aware**: `checkServerTrusted(chain, ocsp, sct, authType, host)`.
    -   Passes OCSP (Online Certificate Status Protocol) responses and SCT (Signed Certificate Timestamp) data to the underlying trust manager for revocation checks and CT verification.

### Helper Methods
-   `isUserAddedCertificate(cert)`: Checks if a cert is in the user-installed CA store (vs system store).
-   `isSameTrustConfiguration(...)`: Checks if the trust manager configuration is identical for two hostnames (optimization for connection pooling).

## Java-to-C++ Translation Guide
-   This class bridges Java Standard API gaps using Android internals.
-   In C++ (OpenSSL/BoringSSL):
    -   **Hostname**: Use `X509_VERIFY_PARAM_set1_host`.
    -   **CT/OCSP**: Use specialized callbacks or verification flags provided by the library.
    -   **User Certs**: This is specific to Android's `UserCertificateSource`. C++ would need to query the specific keystore/directory where user CA certs are stored (`/data/misc/user/...`).
