# NetworkSecurityConfig - Reverse Engineering Documentation

## Executive Summary
Represents a single configuration node (base, domain, or debug). Contains rules for cleartext traffic, HSTS, pinning, and trust anchors.

## Data Model
*   `mCleartextTrafficPermitted`
*   `mHstsEnforced`
*   `mPins` (`PinSet`)
*   `mCertificatesEntryRefs` (Trust anchors)
*   `mTrustManager`

## Detailed Functionality
*   **Trust Anchors**: Aggregates anchors from all entry refs. Handles overrides (debug anchors overriding system).
*   **Pinning**: `getPins()` returns the pin set.

## Java-to-C++ Translation Guide
*   Core configuration object.
