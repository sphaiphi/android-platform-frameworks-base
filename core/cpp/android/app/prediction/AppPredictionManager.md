# AppPredictionManager - Reverse Engineering Documentation

## Executive Summary
`AppPredictionManager` is the entry point for creating prediction sessions. It acts as a factory for `AppPredictor` instances.

## Architecture Overview
*   **Type**: Manager / Factory.
*   **Scope**: System API.
*   **Dependency**: `AppPredictor`, `AppPredictionContext`.

## Detailed Functionality

### Session Creation
**Method**: `createAppPredictionSession(AppPredictionContext)`
**Algorithm**:
1.  Takes an `AppPredictionContext`.
2.  Instantiates and returns a new `AppPredictor`, passing the `mContext` and the `predictionContext`.

## Data Model
*   `mContext`: Android Context (held to pass to Predictor).

## Java-to-C++ Translation Guide
*   This class is primarily a Java-side convenience wrapper. In C++, if exposing a similar API, it would likely be a function that returns a `shared_ptr<AppPredictor>`.

## Implementation Risks
*   None.
