# ConversationAction - Reverse Engineering Documentation

## Executive Summary
Represents an action suggested by a `TextClassifier` for a conversation context (e.g., in a messaging app). It contains an action type (like `TYPE_TEXT_REPLY`, `TYPE_VIEW_CALENDAR`), a confidence score, and potentially a `RemoteAction` or a text reply string.

## Data Model
*   **Type**: `mType` (String constant like `view_calendar`, `text_reply`).
*   **Action**: `mAction` (`RemoteAction`).
*   **Text Reply**: `mTextReply` (CharSequence).
*   **Score**: `mScore` (float 0.0 - 1.0).
*   **Extras**: `mExtras` (Bundle).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Builder Pattern**: Implements Builder.
