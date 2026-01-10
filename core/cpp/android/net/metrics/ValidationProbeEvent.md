# ValidationProbeEvent.java - Reverse Engineering Documentation

## Executive Summary
`ValidationProbeEvent` logs specific probes sent during network validation (e.g., DNS, HTTP, HTTPS probes) and their results.

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`.

## Data Model
-   `probeType`: Encodes type (DNS, HTTP...) and stage (First validation vs Revalidation).
-   `returnCode`: Success/Failure.
-   `durationMs`.

## Java-to-C++ Translation Guide
Simple struct with bitmask logic for `probeType`.
