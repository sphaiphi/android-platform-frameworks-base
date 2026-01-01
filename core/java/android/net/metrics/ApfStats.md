# ApfStats.java - Reverse Engineering Documentation

## Executive Summary
`ApfStats` is a deprecated metrics event class that aggregates statistics about APF execution over a duration. It tracks dropped packets, parse errors, and program updates.

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`
- **Implements**: `IpConnectivityLog.Event`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `durationMs` | `long` | Time interval covered. |
| `receivedRas` | `int` | Total RAs received. |
| `matchingRas` | `int` | RAs matching a known pattern. |
| `droppedRas` | `int` | Ignored due to limit. |
| `zeroLifetimeRas` | `int` | RAs with 0 lifetime. |
| `parseErrors` | `int` | Parsing failures. |
| `programUpdates` | `int` | Updates due to RAs. |
| `programUpdatesAll` | `int` | Total updates. |
| `programUpdatesAllowingMulticast` | `int` | Updates allowing multicast. |
| `maxProgramSize` | `int` | Hardware limit. |

## Java-to-C++ Translation Guide
Simple struct.
