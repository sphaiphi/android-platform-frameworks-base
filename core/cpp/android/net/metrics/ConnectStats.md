# ConnectStats.java - Reverse Engineering Documentation

## Executive Summary
`ConnectStats` aggregates statistics for TCP `connect()` calls. It tracks success/failure counts, error codes (errno), latencies, and IPv6 usage. It supports token-bucket rate limiting for latency recording.

## Architecture Overview
- **Type**: Metrics Aggregator
- **Package**: `android.net.metrics`
- **Dependencies**: `android.util.SparseIntArray`, `android.util.IntArray`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `netId` | `int` | Network ID. |
| `transports` | `long` | Bitmask. |
| `errnos` | `SparseIntArray` | Map of `errno` -> count. |
| `latencies` | `IntArray` | List of latency values (ms). |
| `eventCount` | `int` | Total events. |
| `connectCount` | `int` | Successful connects. |
| `connectBlockingCount` | `int` | Blocking connects. |
| `ipv6ConnectCount` | `int` | IPv6 connects. |

## Logic
-   **Blocking vs Non-Blocking**: Uses `EINPROGRESS` or `EALREADY` to detect non-blocking sockets. Non-blocking connects are counted as success but latency is skipped (as `connect` returns immediately).
-   **Rate Limiting**: Uses `TokenBucket` to avoid storing too many latency samples.

## Java-to-C++ Translation Guide
-   Logic for `isNonBlocking` (checking `EINPROGRESS`/`EALREADY`) is standard POSIX.
-   `SparseIntArray` maps to `std::map<int, int>` or `std::vector<std::pair<int, int>>` (flat map).
