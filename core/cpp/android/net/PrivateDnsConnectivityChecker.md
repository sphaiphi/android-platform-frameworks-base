# PrivateDnsConnectivityChecker.java - Reverse Engineering Documentation

## Executive Summary
`PrivateDnsConnectivityChecker` is a utility class to verify connectivity to a Private DNS (DNS-over-TLS) server. It attempts a TLS handshake on port 853.

## Architecture Overview
- **Type**: Utility Class
- **Package**: `android.net`
- **Dependencies**: `javax.net.ssl.SSLSocket`.

## Algorithm
1.  **Creation**: Creates an `SSLSocket` using default factory.
2.  **Configuration**: Sets timeout (5000ms).
3.  **Connection**: Connects to `hostname:853`.
4.  **Handshake**: Calls `startHandshake()`.
5.  **Result**: Returns `true` if successful, `false` on `IOException`.

## Java-to-C++ Translation Guide
Requires OpenSSL/BoringSSL.
-   `SSL_new`, `SSL_set_fd`.
-   `connect` (TCP).
-   `SSL_connect` (TLS Handshake).
