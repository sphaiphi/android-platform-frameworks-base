# DnsEvent.java - Reverse Engineering Documentation

## Executive Summary
`DnsEvent` aggregates a batch of DNS lookup results. It stores parallel arrays of query types, return codes, and latencies.

## Architecture Overview
- **Type**: Metrics Aggregator
- **Package**: `android.net.metrics`.

## Data Model
-   `netId` / `transports`.
-   `eventTypes`: `byte[]` (query type).
-   `returnCodes`: `byte[]` (success/failure code).
-   `latenciesMs`: `int[]`.
-   `eventCount`, `successCount`.

## Limits
-   `SIZE_LIMIT`: 20,000 events.
-   Dynamically resizes arrays.

## Java-to-C++ Translation Guide
-   Structure-of-Arrays (SoA) layout.
-   `std::vector<uint8_t>` for types/codes, `std::vector<int>` for latencies.
