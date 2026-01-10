# TrustedCertificateStoreAdapter - Reverse Engineering Documentation

## Executive Summary
Adapts `NetworkSecurityConfig` to Conscrypt's `TrustedCertificateStore` interface.

## Purpose
Allows `TrustManagerImpl` (Conscrypt) to query trust anchors from our custom configuration.

## Java-to-C++ Translation Guide
*   Adapter pattern.
