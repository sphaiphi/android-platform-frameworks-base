# ScoredNetwork.java - Reverse Engineering Documentation

## Executive Summary
`ScoredNetwork` represents a network (identified by `NetworkKey`) along with its quality score (represented by `RssiCurve`) and other attributes (metered hint, captive portal hint).

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`
- **Dependencies**: `NetworkKey`, `RssiCurve`, `Bundle`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `networkKey` | `NetworkKey` | ID. |
| `rssiCurve` | `RssiCurve` | Score curve. |
| `meteredHint` | `boolean` | Metered status hint. |
| `attributes` | `Bundle` | Extra data (Badging curve, ranking offset, etc.). |

## Logic
-   `calculateRankingScore(rssi)`: Computes a score using the curve, shifts it left 8 bits, and adds a ranking offset from attributes.

## Java-to-C++ Translation Guide
Struct with logic. `Bundle` translation requires `PersistableBundle` or similar key-value store in C++.
