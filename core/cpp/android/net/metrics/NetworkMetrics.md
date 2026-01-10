# NetworkMetrics.java - Reverse Engineering Documentation

## Executive Summary
`NetworkMetrics` is a container that holds both `ConnectStats` and `DnsEvent` for a specific network, along with a `Summary` of running totals. It acts as the central aggregation point for a network's performance data.

## Architecture Overview
- **Type**: Aggregator
- **Package**: `android.net.metrics`
- **Components**: `ConnectStats`, `DnsEvent`, `Summary`.

## Data Model
-   **Pending**: `pendingSummary` accumulates recent events.
-   **Summary**: Holds long-term averages/sums (DNS latencies, Error rates, TCP loss/RTT).

## Java-to-C++ Translation Guide
-   Composite class containing the other stats classes.
-   Logic involves merging statistics (sum/count/max) from pending to summary.
