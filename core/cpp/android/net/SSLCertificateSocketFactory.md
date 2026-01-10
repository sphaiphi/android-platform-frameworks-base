# SSLCertificateSocketFactory.java - Reverse Engineering Documentation

## Executive Summary
`SSLCertificateSocketFactory` is an extension of `SSLSocketFactory` that provides additional features:
-   Configurable handshake timeouts.
-   Optional SSL session caching (`SSLSessionCache`).
-   "Insecure" mode to bypass certificate checks (for development).
-   NPN/ALPN protocol setting.
-   SNI (Server Name Indication) support.

## Architecture Overview
- **Type**: Factory Class
- **Package**: `android.net`
- **Extends**: `javax.net.ssl.SSLSocketFactory`.
- **Dependencies**: `com.android.org.conscrypt.OpenSSLSocketImpl` (Conscrypt).

## Detailed Functionality
It acts as a wrapper around the Conscrypt `SSLSocketFactory`.
-   **Insecure Mode**: Uses a custom `TrustManager` that trusts everything.
-   **Conscrypt Integration**: Casts sockets to `OpenSSLSocketImpl` to set non-standard properties like NPN/ALPN/SNI/SessionTickets which were not standard Java APIs at the time.

## Java-to-C++ Translation Guide
This logic is specific to the Java SSL layer (Conscrypt/OpenSSL wrapper). In C++, you would interact directly with OpenSSL/BoringSSL `SSL_CTX` and `SSL` objects.
-   **Timeout**: `SSL_set_timeout`.
-   **SNI**: `SSL_set_tlsext_host_name`.
-   **ALPN**: `SSL_set_alpn_protos`.
-   **Insecure**: `SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL)`.
