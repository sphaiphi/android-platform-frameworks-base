# ContextHubIntentEvent - Reverse Engineering Documentation

## Executive Summary
`ContextHubIntentEvent` is a helper class to decode and represent events received via `PendingIntent` from the Context Hub Service. It parses the extras from an `Intent` into a structured object containing the event type, hub info, nanoapp ID, and payload.

## Architecture Overview
- **Pattern**: Factory / Wrapper.
- **Role**: Helper for `PendingIntent` receivers.

## Detailed Functionality
- **Factory**: `fromIntent(Intent)` validates extras and constructs the object.
- **Event Types**: Handles `EVENT_NANOAPP_LOADED`, `MESSAGE`, `ABORTED`, `HUB_RESET`, `CLIENT_AUTHORIZATION`, etc.
- **Data extraction**: Extracts `ContextHubInfo` (Parcelable), `NanoAppMessage` (Parcelable), IDs, and codes.

## Data Model
- `mEventType`: `int` (Event constant).
- `mContextHubInfo`: `ContextHubInfo`.
- `mNanoAppId`: `long`.
- `mNanoAppMessage`: `NanoAppMessage` (Nullable).
- `mNanoAppAbortCode`: `int`.
- `mClientAuthorizationState`: `int`.

## Java-to-C++ Translation Guide
### Relevance
- **Low**: This class is specific to Android's `Intent` system. Unless the C++ layer interacts with Android Intents (e.g., via Binder to ActivityManager), this might not be needed.
- **Alternative**: If C++ needs to represent these events, a simple struct/variant handling the union of these fields would suffice.

## Questions for C++ Team
- Do we need to support Android Intents in the C++ layer?
