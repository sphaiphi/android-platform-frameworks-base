# TextClassifierEvent - Reverse Engineering Documentation

## Executive Summary
Base class for events reported to the TextClassifier. It has subclasses for specific event categories (Selection, Linkify, Language Detection, Conversation Actions).

## Data Model
*   **Category**: `mEventCategory` (SELECTION, LINKIFY, etc.).
*   **Type**: `mEventType` (CLICKED, SHOWN, etc.).
*   **Context**: `mEventContext`.
*   **Scores**, **Indices**, **Result ID**.

## Subclasses
*   `TextSelectionEvent`
*   `TextLinkifyEvent`
*   `LanguageDetectionEvent`
*   `ConversationActionsEvent`

## Java-to-C++ Translation Guide
*   **Parcelable**: Efficient parceling based on event type token.
*   **Inheritance**: Polymorphic class hierarchy.
