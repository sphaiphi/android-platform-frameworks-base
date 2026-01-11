# ApfProgramEvent.java - Reverse Engineering Documentation

## Executive Summary
`ApfProgramEvent` is a deprecated metrics event class that logs details about Android Packet Filter (APF) program updates. It captures information such as program lifetime, filtering effectiveness (RAs filtered vs total), and program size.

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`
- **Implements**: `IpConnectivityLog.Event`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `lifetime` | `long` | Maximum computed lifetime (seconds). |
| `actualLifetime` | `long` | Effective lifetime (seconds). |
| `filteredRas` | `int` | Count of Router Advertisements filtered. |
| `currentRas` | `int` | Total RAs at generation time. |
| `programLength` | `int` | Size of APF bytecode (bytes). |
| `flags` | `int` | Bitfield (`FLAG_MULTICAST_FILTER_ON`, `FLAG_HAS_IPV4_ADDRESS`). |

## Java-to-C++ Translation Guide
Simple struct.
