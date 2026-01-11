# NetworkScorerAppData.java - Reverse Engineering Documentation

## Executive Summary
`NetworkScorerAppData` is a data class holding metadata about a discovered network scorer application (package name, UID, recommendation service component).

## Architecture Overview
- **Type**: Parcelable Data Object
- **Package**: `android.net`
- **Usage**: Used by Settings to list available scorer apps.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `packageUid` | `int` | UID of the app. |
| `mRecommendationService` | `ComponentName` | Service component. |
| `mRecommendationServiceLabel` | `String` | UI Label. |
| `mEnableUseOpenWifiActivity` | `ComponentName` | Config activity. |

## Java-to-C++ Translation Guide
Simple struct.
