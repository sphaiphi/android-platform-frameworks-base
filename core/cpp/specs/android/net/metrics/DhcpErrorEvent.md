# DhcpErrorEvent.java - Reverse Engineering Documentation

## Executive Summary
`DhcpErrorEvent` logs specific parsing or protocol errors during DHCP address acquisition. It uses a custom error code format encoding type (L2, L3, L4, DHCP, Misc) and subtype.

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`.

## Error Codes
Encoded as 32-bit int: `(Type << 24) | (SubType << 16)`.
-   **Types**: L2 (1), L3 (2), L4 (3), DHCP (4), MISC (5).
-   **Subtypes**: Specific errors like `BUFFER_UNDERFLOW`, `DHCP_NO_COOKIE`.

## Java-to-C++ Translation Guide
Define constants in a header.
