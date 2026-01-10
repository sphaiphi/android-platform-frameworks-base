# NetworkSecurityTrustManager - Reverse Engineering Documentation

## Executive Summary
`X509ExtendedTrustManager` implementation that enforces the policy of a *single* `NetworkSecurityConfig`.

## Architecture
*   **Delegate**: Wraps `Com.android.org.conscrypt.TrustManagerImpl`.
*   **Pinning**: Implements `checkPins` logic after the delegate verifies the chain.

## Detailed Functionality
*   **Check Server Trusted**: Calls delegate, then calls `checkPins(trustedChain)`.
*   **Check Pins**: Calculates SPKI hashes of the chain and compares against `PinSet`.

## Java-to-C++ Translation Guide
*   This logic (chain building + pin verification) needs to be implemented in the C++ TLS stack (BoringSSL callbacks).
