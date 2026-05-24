# FontRequest - Reverse Engineering Documentation

## Executive Summary
`FontRequest` represents a request for a downloadable font. It encapsulates the provider authority, package, query string, and verification certificates.

**Note**: Deprecated in favor of `androidx.core.provider.FontRequest`.

## Architecture Overview
- **Type**: Data Class.
- **Components**: Authority, Package, Query, Certificates.

## Java-to-C++ Translation Guide
-   **Struct**: Simple data structure holding strings and lists of byte arrays (certs).
