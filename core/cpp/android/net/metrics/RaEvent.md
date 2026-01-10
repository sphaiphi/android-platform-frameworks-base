# RaEvent.java - Reverse Engineering Documentation

## Executive Summary
`RaEvent` logs details about a received Router Advertisement (RA) packet, specifically the lifetimes of various options (Router, Prefix, Route Info, RDNSS, DNSSL).

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `routerLifetime` | `long` | Router lifetime. |
| `prefixValidLifetime` | `long` | Prefix valid lifetime. |
| `prefixPreferredLifetime` | `long` | Prefix preferred lifetime. |
| `rdnssLifetime` | `long` | DNS server lifetime. |

## Java-to-C++ Translation Guide
Simple struct.
