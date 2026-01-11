# CallLog - Reverse Engineering Documentation

## Executive Summary
`CallLog` provides the contract and utilities for accessing the call history (incoming, outgoing, missed calls). It exposes the `Calls` table and supports operations like adding calls and storing call composer pictures.

## Architecture Overview
- **Type**: Contract / Utility Class.
- **Authority**: `call_log`.
- **Inner Classes**:
    -   `Calls`: The main table definition.
    -   `AddCallParams`: Builder for adding a call.

## Detailed Functionality
-   **Add Call**: `Calls.addCall(...)` helper method inserts a row into the provider. It handles normalization, geocoding (if location provided), and updates data usage.
-   **Call Composer**: `storeCallComposerPicture` allows storing images associated with calls.
-   **Shadow Provider**: Handles encryption-aware storage (`call_log_shadow`) for user 0/system user.

## Data Model
-   **Calls Table**:
    -   `NUMBER`, `DATE`, `DURATION`, `TYPE` (Incoming, Outgoing, Missed, Voicemail, Blocked, etc.).
    -   `CACHED_NAME`, `CACHED_NUMBER_TYPE`: Denormalized contact info.
    -   `BLOCK_REASON`: Why a call was blocked.
    -   `MISSED_REASON`: Why a call was missed (short ring, DND, etc.).
    -   `COMPOSER_PHOTO_URI`: Link to call composer image.

## API Reference
-   `Calls.addCall(...)`: Main entry point for inserting calls.
-   `storeCallComposerPicture(...)`: Async image storage.

## Java-to-C++ Translation Guide
-   **Insertion Logic**: The `addCall` method contains significant business logic (checking presentation, updating contacts usage, handling shadow provider). If implementing a C++ client, this logic might need partial replication or invocation via JNI.
-   **URI**: `content://call_log/calls`.
