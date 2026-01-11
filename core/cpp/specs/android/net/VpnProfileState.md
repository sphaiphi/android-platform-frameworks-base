# VpnProfileState.java - Reverse Engineering Documentation

## Executive Summary
`VpnProfileState` is a snapshot of the current state of a VPN profile (Disconnected, Connecting, Connected, Failed). It also includes the session ID, always-on status, and lockdown status.

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `mState` | `int` | State Enum (0-3). |
| `mSessionKey` | `String` | Unique session ID. |
| `mAlwaysOn` | `boolean` | Is Always-On enabled. |
| `mLockdown` | `boolean` | Is Lockdown enabled. |

## Java-to-C++ Translation Guide
Simple struct.
