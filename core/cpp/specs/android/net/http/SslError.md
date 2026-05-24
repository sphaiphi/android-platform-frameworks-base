# SslError.java - Reverse Engineering Documentation

## Executive Summary
`SslError` encapsulates an SSL error (e.g., expired cert, hostname mismatch) associated with a specific `SslCertificate` and URL. It supports multiple errors via a bitmask.

## Architecture Overview
- **Type**: Error Container
- **Package**: `android.net.http`
- **Dependencies**: `SslCertificate`.

## Constants (Error Types)
-   `SSL_NOTYETVALID` (0)
-   `SSL_EXPIRED` (1)
-   `SSL_IDMISMATCH` (2)
-   `SSL_UNTRUSTED` (3)
-   `SSL_DATE_INVALID` (4)
-   `SSL_INVALID` (5) - Generic.

## Data Model
-   `mErrors`: Bitmask. `1 << error_code`.
-   `mCertificate`: The failing certificate.
-   `mUrl`: The URL being accessed.

## Functionality
-   **`addError(int)`**: Sets the bit.
-   **`hasError(int)`**: Checks the bit.
-   **`getPrimaryError()`**: Returns the most severe error (highest index). Severity order: Invalid > Date Invalid > Untrusted > Mismatch > Expired > Not Yet Valid.
-   **`SslErrorFromChromiumErrorCode`**: Maps Chromium net errors (negative integers like -200) to these constants.

## Java-to-C++ Translation Guide
-   Use an `enum` for error codes.
-   Use `std::bitset` or a simple integer for the bitmask.
-   Logic is trivial state management.
