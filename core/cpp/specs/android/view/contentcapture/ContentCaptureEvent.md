# ContentCaptureEvent - Reverse Engineering Documentation

## Executive Summary
Represents a single event in the Content Capture system (view appeared, text changed, session lifecycle, etc.). It acts as a container for the event type and associated data (ViewNode, AutofillId, text).

## Data Model
*   **Type**: `TYPE_VIEW_APPEARED`, `TYPE_VIEW_TEXT_CHANGED`, etc.
*   **Payload**: `mNode` (ViewNode), `mId`/`mIds` (AutofillId), `mText` (CharSequence), `mInsets`, `mBounds`.
*   **Session**: `mSessionId`, `mParentSessionId`.
*   **Timing**: `mEventTime`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Efficient parceling logic (flags to avoid writing nulls).
*   **Union-like**: The class holds many optional fields depending on `mType`.
