# IpReachabilityEvent.java - Reverse Engineering Documentation

## Executive Summary
`IpReachabilityEvent` logs NUD (Neighbor Unreachability Detection) events, such as probes and failures.

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`.

## Constants
-   `PROBE` (forced probe).
-   `NUD_FAILED`, `PROVISIONING_LOST`.
-   `NUD_FAILED_ORGANIC` (kernel notification).

## Java-to-C++ Translation Guide
Simple struct + Enum.
