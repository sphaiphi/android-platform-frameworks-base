# WakeupStats.java - Reverse Engineering Documentation

## Executive Summary
`WakeupStats` aggregates `WakeupEvent`s for a specific interface. It counts wakeups by UID type (Root, System, App, Non-App) and tracks L2 types (Unicast/Multicast/Broadcast) and Ethertypes.

## Architecture Overview
- **Type**: Aggregator
- **Package**: `android.net.metrics`.

## Data Model
-   `totalWakeups`, `rootWakeups`, `systemWakeups`, `applicationWakeups`, etc.
-   `l2UnicastCount`, `l2MulticastCount`, `l2BroadcastCount`.
-   `ethertypes`, `ipNextHeaders` (`SparseIntArray` histograms).

## Java-to-C++ Translation Guide
Struct with `std::map` or similar for histograms.
