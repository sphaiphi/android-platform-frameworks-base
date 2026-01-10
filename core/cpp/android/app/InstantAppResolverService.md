# InstantAppResolverService - Reverse Engineering Documentation

## Executive Summary
`InstantAppResolverService` is an abstract base class for the system service responsible for resolving Instant App intents.

## Architecture Overview
*   **Inheritance**: `Service`.
*   **Binder**: `IInstantAppResolver.Stub`.

## Detailed Functionality
*   **Resolution**: `onGetInstantAppResolveInfo` / `onGetInstantAppIntentFilter`.
*   **Handler**: Uses a `ServiceHandler` to offload binder calls to the main thread.
*   **Callback**: `InstantAppResolutionCallback` sends results back via `IRemoteCallback`.

## Java-to-C++ Translation Guide
*   Service base class.
*   Binder implementation.

## Implementation Risks
*   None.
