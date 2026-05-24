# TextClassifierService - Reverse Engineering Documentation

## Executive Summary
`TextClassifierService` is an abstract base class for services that provide intelligent text analysis, including entity recognition (addresses, phone numbers, etc.), smart selection, language detection, and conversation action suggestions. It powers features like the "Smart Selection" tool in the Android text selection toolbar and "Smart Replies" in notifications.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ITextClassifierService.Stub`. Results are returned via `ITextClassifierCallback`.
*   **Threading**: dispatches binder calls to the main thread via a `Handler`. Some methods (like language detection) may use an internal `ExecutorService` if they are not explicitly overridden by subclasses.
*   **Permission**: Requires `android.permission.BIND_TEXTCLASSIFIER_SERVICE`.
*   **Deployment**: The system's default provider is configured via `config_defaultTextClassifierPackage`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `ITextClassifierService` binder interface.

### Core Analysis Methods
*   **`onSuggestSelection(TextClassificationSessionId, TextSelection.Request, ...)`**:
    *   **Goal**: Determine the logical boundaries of a text selection. For example, if a user selects a few digits of a phone number, it should suggest selecting the entire number.
*   **`onClassifyText(TextClassificationSessionId, TextClassification.Request, ...)`**:
    *   **Goal**: Identify what a piece of text represents (an entity) and provide relevant actions (e.g., a "Call" button for a phone number).
*   **`onGenerateLinks(TextClassificationSessionId, TextLinks.Request, ...)`**:
    *   **Goal**: Identify all entities in a large block of text and return metadata to create clickable links.
*   **`onDetectLanguage(TextClassificationSessionId, TextLanguage.Request, ...)`**:
    *   **Goal**: Identify the primary language(s) of the text.
*   **`onSuggestConversationActions(TextClassificationSessionId, ConversationActions.Request, ...)`**:
    *   **Goal**: Analyze a conversation (list of messages) and suggest smart replies or follow-up actions.

### Event Logging
*   **`onTextClassifierEvent(TextClassificationSessionId, TextClassifierEvent)`**: Tracks how users interact with the suggestions (e.g., whether they actually clicked the suggested "Call" button) to evaluate and improve model performance.

### Session Management
*   **`onCreateTextClassificationSession` / `onDestroyTextClassificationSession`**: Allows the service to maintain state for a particular interaction (e.g., while a user is editing a specific text field).

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.textclassifier.TextClassifierService"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ITextClassifierService.Stub`.
*   **C++**: `BnTextClassifierService`.

### Data Model
*   Uses a wide variety of complex Parcelables from `android.view.textclassifier`: `TextSelection`, `TextClassification`, `TextLinks`, `ConversationActions`, etc.
*   C++ implementation of the service usually delegates the actual ML inference to a native library (like `libtextclassifier`).

### Performance
*   Text classification is often triggered during user typing or selection. High performance and low latency are critical.
*   Model loading should be handled asynchronously or cached.

## Implementation Risks
*   **Latency**: Blocking the UI thread while waiting for an ML model can cause severe jank.
*   **Privacy**: This service processes raw text input from the user. It must ensure all processing is local and no user text is leaked.
*   **Model Management**: The service must handle model updates and potential compatibility issues between the framework and the underlying ML engine.
