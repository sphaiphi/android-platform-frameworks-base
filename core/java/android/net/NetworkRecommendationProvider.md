# NetworkRecommendationProvider.java - Reverse Engineering Documentation

## Executive Summary
`NetworkRecommendationProvider` is a base class for applications implementing a network recommendation service. It exposes an AIDL interface `INetworkRecommendationProvider` to the system, allowing the system to request network scores.

## Architecture Overview
- **Type**: Abstract Service Base Class
- **Package**: `android.net`
- **Extends**: None (Wrapper around `INetworkRecommendationProvider.Stub`).
- **Context**: Used by "Network Scorer" apps (deprecated mechanism).

## Detailed Functionality
-   **ServiceWrapper**: An inner class extending `INetworkRecommendationProvider.Stub` that handles IPC calls.
-   **Threading**: Dispatches `requestScores` calls to a provided `Executor` or `Handler`.
-   **Permission Check**: Enforces `android.permission.REQUEST_NETWORK_SCORES`.

## Java-to-C++ Translation Guide
This is a server-side component for Java apps. C++ translation is only relevant if implementing a native recommendation service, which is unlikely given this is an app-facing API.
