# NetworkEvent.java - Reverse Engineering Documentation

## Executive Summary
`NetworkEvent` logs high-level network state changes (Connected, Validated, Disconnected, Captive Portal Found).

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`.

## Constants
-   `NETWORK_CONNECTED`, `NETWORK_DISCONNECTED`.
-   `NETWORK_VALIDATED`, `NETWORK_VALIDATION_FAILED`.
-   `NETWORK_CAPTIVE_PORTAL_FOUND`.

## Java-to-C++ Translation Guide
Simple struct + Enum.
