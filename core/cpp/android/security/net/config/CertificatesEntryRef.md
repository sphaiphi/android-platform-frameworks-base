# CertificatesEntryRef - Reverse Engineering Documentation

## Executive Summary
`CertificatesEntryRef` represents a reference to a `CertificateSource` within a `NetworkSecurityConfig`. It adds configuration context like whether to override pins or disable CT.

## Data Model
*   `mSource`: The `CertificateSource`.
*   `mOverridesPins`: Boolean.
*   `mDisableCT`: Boolean.

## Java-to-C++ Translation Guide
*   Wrapper/Adapter class.
