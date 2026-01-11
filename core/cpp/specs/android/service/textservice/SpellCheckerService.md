# SpellCheckerService - Reverse Engineering Documentation

## Executive Summary
`SpellCheckerService` is an abstract base class for implementing a spell checker in the Android system. It provides an infrastructure for applications (like the system keyboard or text editors) to request spelling suggestions for words and sentences.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ISpellCheckerService.Stub`. It establishes `ISpellCheckerSession` objects for each active client.
*   **Threading**: Critical methods (`onGetSuggestions`, etc.) are executed on the binder thread pool. Implementers must ensure thread safety.
*   **Lifecycle**:
    *   `onBind()` returns the service binder.
    *   `createSession()` is a factory method to provide a `SpellCheckerService.Session` for a specific request.

## Detailed Functionality

### `SpellCheckerService.Session` (Abstract Inner Class)
This class represents a single active spell-checking context (usually tied to a specific `Locale`).
*   **`onCreate()`**: Initialization hook after the locale and bundle are available.
*   **`onGetSuggestions(TextInfo, int)`**:
    *   **Goal**: Provide spelling suggestions for a single word.
    *   **Returns**: `SuggestionsInfo`.
*   **`onGetSuggestionsMultiple(TextInfo[], int, boolean)`**:
    *   **Goal**: Batch process multiple words for efficiency.
*   **`onGetSentenceSuggestionsMultiple(TextInfo[], int)`**:
    *   **Goal**: Provide suggestions for whole sentences.
    *   **Logic**: The default implementation uses a `SentenceLevelAdapter` to split the sentence into individual words using a `WordIterator` and then queries `onGetSuggestionsMultiple`.

### Internal Mechanics
*   **`SpellCheckerServiceBinder`**: Handles the initial `getISpellCheckerSession` request from the system.
*   **`InternalISpellCheckerSession`**: An AIDL implementation that wraps the `Session` and manages process priorities (lowering priority to background during processing).
*   **`SentenceLevelAdapter`**: A utility that handles the complex mapping of word-level suggestions back into sentence-level offsets and lengths.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.textservice.SpellCheckerService"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ISpellCheckerService.Stub`, `ISpellCheckerSession.Stub`.
*   **C++**: `BnSpellCheckerService`, `BnSpellCheckerSession`.

### Data Model
*   `TextInfo`, `SuggestionsInfo`, `SentenceSuggestionsInfo` are Parcelables.
*   `SuggestionsInfo` contains an array of suggested strings and bitmask flags (e.g., `RESULT_ATTR_LOOKUP_NOT_FOUND`).

### Text Processing
*   **Java**: Uses `WordIterator` and `BreakIterator` for sentence splitting.
*   **C++**: Requires equivalent logic, likely using ICU (`icu::BreakIterator`) for robust multi-language support.

## Implementation Risks
*   **Performance**: Spell checking happens during user typing. High latency in `onGetSuggestions` will result in poor user experience.
*   **Memory**: Large dictionaries should be shared or mapped using `mmap` if possible.
*   **Concurrency**: Multiple sessions can be active simultaneously on different binder threads.
