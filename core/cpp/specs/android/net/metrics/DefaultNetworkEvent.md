# DefaultNetworkEvent.java - Reverse Engineering Documentation

## Executive Summary
`DefaultNetworkEvent` records a change in the system's default network. It captures the network ID, transports, IP support (v4/v6), and validation duration.

## Architecture Overview
- **Type**: Metrics Event
- **Package**: `android.net.metrics`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `creationTimeMs` | `long` | Start timestamp. |
| `netId` | `int` | Network ID. |
| `transports` | `int` | Transport bitmask. |
| `ipv4`/`ipv6` | `boolean` | Connectivity flags. |
| `durationMs` | `long` | Time spent as default. |
| `validatedMs` | `long` | Time validated. |

## Java-to-C++ Translation Guide
Simple struct.
