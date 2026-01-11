# IntrusionDetectionManager - Reverse Engineering Documentation

## Executive Summary
`IntrusionDetectionManager` manages intrusion detection on the device. It allows enabling/disabling the feature and monitoring its state.

## Architecture Overview
*   **Package**: `android.security.intrusiondetection`
*   **Type**: Class (System Service, System API)
*   **Service Name**: `Context.INTRUSION_DETECTION_SERVICE`
*   **Dependencies**: `IIntrusionDetectionService`.

## Detailed Functionality

### 1. State Monitoring
*   **Method**: `addStateCallback` / `removeStateCallback`.
*   **Mechanism**: Registers an `IIntrusionDetectionServiceStateCallback` stub that delegates to the user-provided `Consumer<Integer>` on an `Executor`.

### 2. Control
*   **Method**: `enable` / `disable`.
*   **Mechanism**: Calls service methods with a `CommandCallback` (via `IIntrusionDetectionServiceCommandCallback`).

## Data Model
*   **States**: `UNKNOWN`, `DISABLED`, `ENABLED`.
*   **Errors**: `PERMISSION_DENIED`, `TRANSPORT_UNAVAILABLE`, etc.

## Java-to-C++ Translation Guide
*   Standard Manager/Service pattern.
*   Callback management requires thread-safe maps (`ConcurrentHashMap` in Java, `std::map` with `std::mutex` in C++).
