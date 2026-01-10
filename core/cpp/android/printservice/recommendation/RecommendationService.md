# RecommendationService - Reverse Engineering Documentation

## Executive Summary
`RecommendationService` is a base class for services that recommend print services to the user. It allows the system to bind to it and receive updates about potential print services based on discovered mDNS/network printers.

## Architecture Overview
- **Inheritance**: `RecommendationService` -> `Service`.
- **IPC**: Implements `IRecommendationService.Stub`.

## Detailed Functionality
-   **Lifecycle**: `onConnected`, `onDisconnected`.
-   **Updates**: `updateRecommendations(List<RecommendationInfo>)` sends new data to the system via the registered callback.

## API Reference
-   `onConnected()`, `onDisconnected()`.
-   `updateRecommendations(...)`.

## Java-to-C++ Translation Guide
-   **Callback Management**: Manages `IRecommendationServiceCallbacks`.
