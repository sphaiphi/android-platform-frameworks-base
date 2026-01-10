# WakeupEvent.java - Reverse Engineering Documentation

## Executive Summary
`WakeupEvent` logs a system wakeup caused by network traffic (NFLOG). It captures packet details (src/dst IP, ports, MAC, ethertype) and the UID attributed to the wakeup.

## Architecture Overview
- **Type**: Data Class (Not Parcelable directly here, usually part of `WakeupStats` or logged individually).
- **Package**: `android.net.metrics`.

## Data Model
-   `iface`, `uid`, `ethertype`.
-   `srcIp`, `dstIp`, `ipNextHeader`, `srcPort`, `dstPort`.
-   `dstHwAddr` (Notes say "actually used to store a src mac address").

## Java-to-C++ Translation Guide
Struct.
