# VoicemailContract - Reverse Engineering Documentation

## Executive Summary
`VoicemailContract` defines the contract for visual voicemail. It allows voicemail source apps to insert voicemail records and status updates into the CallLog provider.

## Architecture Overview
- **Authority**: `com.android.voicemail`.
- **Tables**: `Voicemails`, `Status`.

## Detailed Functionality
-   **Voicemails**: Stores metadata (`number`, `date`, `duration`) and content (via `_data` file).
-   **Status**: Configuration state (`CONFIGURATION_STATE_OK`, etc.) and channel states (data/notification) for the visual voicemail source.
-   **Intents**: `ACTION_NEW_VOICEMAIL`, `ACTION_SYNC_VOICEMAIL`.

## Data Model
-   **Voicemails**: `source_package`, `mime_type`, `transcription`, `has_content`.
-   **Status**: `source_package`, `configuration_state`, `data_channel_state`.

## Java-to-C++ Translation Guide
-   **URI**: `content://com.android.voicemail/voicemail`.
-   **File Access**: Reading the audio content involves opening the file descriptor associated with the content URI.
