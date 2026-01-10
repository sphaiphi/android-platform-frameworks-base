# IntrusionDetectionEvent - Reverse Engineering Documentation

## Executive Summary
Represents a single intrusion detection event, which can be a security event, DNS event, or connection event.

## Architecture Overview
*   **Package**: `android.security.intrusiondetection`
*   **Type**: Class (Parcelable, System API)
*   **Union-like Structure**: Holds one of `SecurityEvent`, `DnsEvent`, or `ConnectEvent`.

## Data Model
*   `mType`: Integer discriminator (`SECURITY_EVENT`, `NETWORK_EVENT_DNS`, `NETWORK_EVENT_CONNECT`).
*   `mSecurityEvent`: `android.app.admin.SecurityLog.SecurityEvent`.
*   `mNetworkEventDns`: `android.app.admin.DnsEvent`.
*   `mNetworkEventConnect`: `android.app.admin.ConnectEvent`.

## Java-to-C++ Translation Guide
*   Use `std::variant` or a tagged union in C++ to represent the mutually exclusive event types.
*   Ensure proper serialization/deserialization logic matches the Java side (int type followed by the specific object).
