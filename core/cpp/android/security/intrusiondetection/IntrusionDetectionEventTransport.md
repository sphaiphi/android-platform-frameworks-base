# IntrusionDetectionEventTransport - Reverse Engineering Documentation

## Executive Summary
`IntrusionDetectionEventTransport` acts as a bridge for sending intrusion detection events to a transport destination (like a file or network). It wraps the AIDL interface `IIntrusionDetectionEventTransport`.

## Architecture Overview
*   **Package**: `android.security.intrusiondetection`
*   **Type**: Class (System API)
*   **Role**: Base class/API for transport implementations.

## Detailed Functionality
*   **Methods**: `initialize`, `addData`, `release`.
*   **Mechanism**:
    *   Inner class `TransportImpl` extends `IIntrusionDetectionEventTransport.Stub`.
    *   This inner class delegates AIDL calls to the public methods of `IntrusionDetectionEventTransport` (which are overridden by subclasses).
    *   Uses `AndroidFuture` for asynchronous results.

## Java-to-C++ Translation Guide
*   This pattern (AIDL Stub wrapping a C++ virtual class) is standard for Binder services in C++ (`BnIntrusionDetectionEventTransport`).
