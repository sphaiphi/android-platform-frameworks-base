# TextClassification - Reverse Engineering Documentation

## Executive Summary
Represents the result of classifying a specific piece of text. Contains the classified entity types, confidence scores, and suggested actions (RemoteActions like "Add to Contacts", "Map", "Call").

## Data Model
*   **Text**: `mText`.
*   **Entities**: `mEntityConfidence`.
*   **Actions**: `mActions` (List of `RemoteAction`).
*   **Legacy**: Icons/Labels/Intents (deprecated).

## Nested Classes
*   **Request**: Arguments for `classifyText` (text, start/end indices, locales).
*   **Builder**: Builder for `TextClassification`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
