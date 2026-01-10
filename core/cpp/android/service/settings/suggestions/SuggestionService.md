# SuggestionService - Reverse Engineering Documentation

## Executive Summary
`SuggestionService` is an abstract base class for providing contextual suggestions to the user within the Android Settings app. These suggestions typically appear at the top of the Settings home screen to guide users through initial setup or highlight useful features.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ISuggestionService.Stub` (internal anonymous class).
*   **Role**: A data provider for the Settings "intelligence" engine.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `ISuggestionService` binder.

### Core Abstract Methods
*   **`onGetSuggestions()`**:
    *   **Goal**: Return a list of all currently available `Suggestion` objects for the user.
*   **`onSuggestionDismissed(Suggestion)`**:
    *   **Goal**: Notify the service that the user has manually swiped away or dismissed a suggestion. The service should track this to avoid showing it again.
*   **`onSuggestionLaunched(Suggestion)`**:
    *   **Goal**: Notify the service that the user clicked on the suggestion and the associated action was launched.

## API Reference

### Data Model
*   `Suggestion`: A Parcelable containing the title, summary, icon, and an `Intent` to launch when the suggestion is tapped.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ISuggestionService.Stub`.
*   **C++**: `BnSuggestionService`.

### Data Handling
*   `Suggestion` is a standard Parcelable.
*   List handling: `getSuggestions()` returns a `List<Suggestion>`, which in C++ maps to `std::vector<Suggestion>`.

## Implementation Risks
*   **User Fatigue**: Showing too many or irrelevant suggestions can annoy the user. The service should implement smart filtering.
*   **Staleness**: Suggestions should reflect the current device state (e.g., if a user already set up a feature, the suggestion to set it up should be removed).
