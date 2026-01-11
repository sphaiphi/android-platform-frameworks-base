# TranslationService - Reverse Engineering Documentation

## Executive Summary
`TranslationService` is an abstract base class for providing on-device translation services to the Android platform. It enables applications to perform high-performance, private translations of text and other data formats without relying on external cloud APIs for every request.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC Model**:
    *   **Management Path**: Implements `ITranslationService.Stub` to receive control signals (connection, capability queries, session creation) from the system server.
    *   **Direct Path**: Implements `ITranslationDirectManager.Stub` (`mClientInterface`) which is passed directly to the client app upon session creation. This allows high-throughput translation requests to bypass the system server for better performance and privacy.
*   **Session Management**: Uses `TranslationContext` to define the parameters of a translation stream (e.g., source/target languages).
*   **Threading**: Dispatches all binder calls to the main thread via a `Handler`.
*   **Permission**: Requires `android.permission.BIND_TRANSLATION_SERVICE`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `ITranslationService` binder interface.

### Capability Discovery
*   **`onTranslationCapabilitiesRequest(sourceFormat, targetFormat, callback)`**:
    *   **Goal**: Return a set of `TranslationCapability` objects describing supported language pairs and their current availability (e.g., whether the model is downloaded).

### Session Lifecycle
*   **`onCreateTranslationSession(TranslationContext, sessionId, callback)`**:
    *   **Goal**: Initialize a translation context.
    *   **Result**: If successful, the system provides the client with a direct binder link to the service's `ITranslationDirectManager`.
*   **`onFinishTranslationSession(sessionId)`**: Called when the client destroys the translator.

### Translation Processing
*   **`onTranslationRequest(TranslationRequest, sessionId, CancellationSignal, Consumer<TranslationResponse>)`**:
    *   **Goal**: Perform the actual translation.
    *   **Partial Responses**: If requested, the service can call the consumer multiple times to provide incremental results.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.translation.TranslationService"`
*   `SERVICE_META_DATA`: `"android.translation_service"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ITranslationService.Stub`, `ITranslationDirectManager.Stub`.
*   **C++**: `BnTranslationService`, `BnTranslationDirectManager`.

### Data Model
*   `TranslationContext`, `TranslationRequest`, `TranslationResponse`, and `TranslationCapability` are Parcelables from `android.view.translation`.
*   C++ implementations usually integrate with a native NLU/Translation engine (e.g., TensorFlow Lite models).

### Performance
*   The "Direct Path" binder optimization is key. In C++, ensure the session objects are managed efficiently and thread-safely as requests will come in on the binder thread pool.

## Implementation Risks
*   **Privacy**: As a system-wide translation provider, the service has access to sensitive text across many apps. Strict local-only processing is expected.
*   **Resource Management**: Translation models are large. The service must handle model downloading, caching, and eviction to manage device storage and memory.
*   **Latency**: Real-time translation (e.g., while typing or reading) requires extremely low inference latency.
