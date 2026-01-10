# WifiKey.java - Reverse Engineering Documentation

## Executive Summary
`WifiKey` uniquely identifies a Wi-Fi network using its SSID and BSSID. Used by `NetworkKey`.

## Architecture Overview
- **Type**: Parcelable Identifier
- **Package**: `android.net`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `ssid` | `String` | SSID (quoted UTF-8 or hex). |
| `bssid` | `String` | MAC Address (XX:XX:XX:XX:XX:XX). |

## Validation
Regex validation for SSID (quotes or hex) and BSSID (MAC format).

## Java-to-C++ Translation Guide
Struct with string validation.
