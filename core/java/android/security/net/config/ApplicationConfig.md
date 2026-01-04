# ApplicationConfig - Reverse Engineering Documentation

## Executive Summary
`ApplicationConfig` is the central container for an application's Network Security Configuration. It holds the configuration source, trust manager, and domain-specific configs.

## Architecture Overview
*   **Package**: `android.security.net.config`
*   **Type**: Class (Public/Hidden)
*   **Key Components**:
    *   `mDefaultConfig`: Fallback configuration.
    *   `mConfigs`: Set of domain-specific configurations.
    *   `mTrustManager`: The `RootTrustManager` handling this config.

## Detailed Functionality

### 1. Hostname Matching
*   **Method**: `getConfigForHostname(String hostname)`
*   **Logic**:
    1.  Normalizes hostname (lowercase, remove trailing dot).
    2.  Iterates through `mConfigs` (domain rules).
    3.  Finds the best match (exact match or longest matching suffix if subdomains included).
    4.  Returns default config if no match found.

### 2. Policy Queries
*   **Methods**: `isCleartextTrafficPermitted`, `isCertificateTransparencyVerificationRequired`.
*   **Logic**: Checks if *all* configs (or specific host configs) allow/require the feature.

## Java-to-C++ Translation Guide
*   Core logic for Network Security Config.
*   Needs efficient domain matching (trie or hash map) in C++ if implemented there.
