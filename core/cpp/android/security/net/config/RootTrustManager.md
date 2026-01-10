# RootTrustManager - Reverse Engineering Documentation

## Executive Summary
The top-level `X509ExtendedTrustManager` that routes verification requests to the appropriate `NetworkSecurityConfig` based on the hostname.

## Detailed Functionality
*   **checkServerTrusted**:
    1.  Extracts hostname from `SSLSocket`/`SSLEngine`.
    2.  Calls `ApplicationConfig.getConfigForHostname(host)`.
    3.  Delegates to that config's `NetworkSecurityTrustManager`.

## Java-to-C++ Translation Guide
*   This routing logic is crucial for supporting per-domain configs.
