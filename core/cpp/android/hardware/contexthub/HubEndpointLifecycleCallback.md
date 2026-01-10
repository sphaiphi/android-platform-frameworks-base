# HubEndpointLifecycleCallback - Reverse Engineering Documentation

## Executive Summary
`HubEndpointLifecycleCallback` defines the contract for handling session lifecycle events. Implementers of this interface receive notifications about session requests, openings, and closures.

## Architecture Overview
- **Type**: Callback Interface.
- **Package**: `android.hardware.contexthub`.

## Detailed Functionality
- **`onSessionOpenRequest`**: Called when a remote endpoint wants to connect. Must return a `HubEndpointSessionResult` (accept/reject).
- **`onSessionOpened`**: Called when a session is fully established.
- **`onSessionClosed`**: Called when a session ends or a request was rejected.

## Java-to-C++ Translation Guide
- Map to a C++ pure virtual interface.
- Ensure `HubEndpointSessionResult` is available.
