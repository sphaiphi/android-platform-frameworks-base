# SpellChecker - Reverse Engineering Documentation

## Executive Summary
`SpellChecker` is a helper class for `TextView` that bridges user input with the system's `TextServicesManager`. It manages a spell checker session, parses text into words/sentences, requests suggestions from the service, and applies `SpellCheckSpan`s or `SuggestionSpan`s to the text.

## Architecture Overview
*   **Role**: Text Analysis Controller.
*   **Host**: `TextView`.
*   **System Service**: `TextServicesManager` -> `SpellCheckerSession`.
*   **Workers**: `SpellParser` (extracts words), `SentenceIteratorWrapper`.

## Detailed Functionality

### 1. Session Management
*   **`resetSession`**: Initializes a `SpellCheckerSession` with the current locale and user dictionary settings.
*   **Lifecycle**: Managed by the TextView (attachment/detachment).

### 2. Parsing (`SpellParser`)
*   Iterates through text using `BreakIterator` (sentence analysis).
*   Extracts ranges of text that need checking.
*   **Optimization**: Batches requests (`MAX_NUMBER_OF_WORDS`) to avoid blocking the UI thread. Uses `SpellCheckerSession.getSentenceSuggestions` for async results.

### 3. Span Management
*   **`SpellCheckSpan`**: Temporary span marking text in progress or valid.
*   **`SuggestionSpan`**: Permanent span marking errors (typos/grammar).
*   **Recycling**: Pools `SpellCheckSpan` objects to reduce GC pressure.

### 4. Logic
*   **`spellCheck(start, end)`**: Entry point. Checks cache, creates parser.
*   **`onGetSuggestions`**: Callback from system. Updates spans based on results (looks like typo -> add red underline).

## Java-to-C++ Translation Guide
*   **Text Analysis**: Requires a robust `BreakIterator` equivalent (ICU).
*   **Async Service**: The spell checker is an async IPC call. C++ implementation needs a callback mechanism.
*   **Spans**: Heavily dependent on the `Spannable` interface.

## Implementation Risks
*   **Concurrency**: `onGetSuggestions` comes from a binder thread; modifying the `TextView` (UI) requires dispatching to the main thread.
*   **Performance**: Text parsing on the main thread must be strictly time-boxed.
