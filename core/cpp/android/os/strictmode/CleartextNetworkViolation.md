# CleartextNetworkViolation - Reverse Engineering Documentation

## Executive Summary
`CleartextNetworkViolation` is a StrictMode violation raised when an application transmits data over the network using unencrypted (cleartext) protocols (e.g., HTTP instead of HTTPS) while unencrypted traffic is disallowed by the security policy.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Policy**: Associated with `VmPolicy`.

## Java-to-C++ Translation Guide
-   **Native Integration**: Detection of cleartext traffic often happens in the native networking stack (`libcore`, `netd`, or `cronet`). This violation class is the Java-side representation of that event.
