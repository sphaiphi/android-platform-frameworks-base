# NetworkScoreManager.java - Reverse Engineering Documentation

## Executive Summary
`NetworkScoreManager` is the system service manager for the deprecated Network Scoring architecture. It allows "Active Scorer" applications to push scores for networks and allows the system/apps to request scores.

## Architecture Overview
- **Type**: System Service Manager
- **Package**: `android.net`
- **Deprecated**: Since API 33 (Tiramisu). Replaced by Wi-Fi Suggestion API.

## Key APIs
-   `updateScores(ScoredNetwork[])`: Push new scores.
-   `clearScores()`: Clear all scores.
-   `requestScores(NetworkKey[])`: Request update for specific networks.
-   `registerNetworkScoreCache(...)`: Registers a callback/cache for score updates.

## Java-to-C++ Translation Guide
Client wrapper around `INetworkScoreService`.
