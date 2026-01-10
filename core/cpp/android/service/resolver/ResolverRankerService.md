# ResolverRankerService - Reverse Engineering Documentation

## Executive Summary
`ResolverRankerService` is a system service base class used to provide intelligent ranking for the system's intent resolver (the "Open with..." or Sharesheet dialog). It allows apps to use usage statistics or ML models to predict which target the user is most likely to select.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IResolverRankerService.Stub` (via `ResolverRankerServiceWrapper`).
*   **Threading**: Uses a dedicated `HandlerThread` ("RESOLVER_RANKER_SERVICE") to ensure that prediction and training logic do not block the system's binder threads or the UI.
*   **Permission**:
    *   Requires `android.permission.BIND_RESOLVER_RANKER_SERVICE` to be bound by the system.
    *   The service must hold `android.permission.PROVIDE_RESOLVER_RANKER_SERVICE`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Initializes the background thread and returns the binder interface.

### Core Operations
*   **`onPredictSharingProbabilities(List<ResolverTarget> targets)`**:
    *   **Goal**: Assign a probability score to each potential intent target.
    *   **Logic**: The service should modify the `selectProbability` field of each `ResolverTarget` in the list. Higher scores move targets to the front of the list.
*   **`onTrainRankingModel(List<ResolverTarget> targets, int selectedPosition)`**:
    *   **Goal**: Provide feedback to the ranking model.
    *   **Logic**: Called after the user has made a selection. The service can use this data to improve future predictions.

### Lifecycle
*   The system binds to the service when a resolver is shown.
*   `predict` calls are asynchronous and report results via `IResolverRankerResult`.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.resolver.ResolverRankerService"`

## Java-to-C++ Translation Guide

### Threading
*   **Java**: Uses `HandlerThread`.
*   **C++**: Should use a dedicated worker thread or a prioritized task queue to handle ML model inference.

### IPC
*   **AIDL**: `IResolverRankerService`, `IResolverRankerResult`.

### Data Model
*   `ResolverTarget` is a Parcelable that contains several float scores (usage, recency, probability).

## Implementation Risks
*   **Latency**: Predictions must be returned quickly. If the service takes too long, the system will fall back to default ranking.
*   **Accuracy**: Poor ranking degrades the user experience.
*   **Privacy**: Access to intent targets and user selections is sensitive. The service should handle this data locally and securely.
