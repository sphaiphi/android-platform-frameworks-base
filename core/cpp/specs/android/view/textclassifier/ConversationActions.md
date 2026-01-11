# ConversationActions - Reverse Engineering Documentation

## Executive Summary
A collection of `ConversationAction` objects, usually returned as a result of a `suggestConversationActions` request. Includes an optional ID.

## Data Model
*   **Actions**: `mConversationActions` (List).
*   **ID**: `mId` (String).

## Nested Classes
*   **Message**: Represents a single message in the conversation history used for generating suggestions. Contains `Person` (author), text, reference time.
*   **Request**: Represents the request to generate actions. Contains conversation history, entity config, max suggestions hint.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Inner Classes**: `Message` and `Request` are also Parcelable.
