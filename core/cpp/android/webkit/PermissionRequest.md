# PermissionRequest - Reverse Engineering Documentation

## Executive Summary
`PermissionRequest` represents a request from web content to access protected resources (Camera, Microphone, MIDI, Protected Media ID). Passed to `WebChromeClient#onPermissionRequest`.

## Detailed Functionality
*   **Resources**: `RESOURCE_VIDEO_CAPTURE`, `RESOURCE_AUDIO_CAPTURE`, `RESOURCE_MIDI_SYSEX`, etc.
*   **Methods**:
    *   `getOrigin()`: Who is asking.
    *   `getResources()`: What they are asking for.
    *   `grant(resources)`: Grant access.
    *   `deny()`: Deny access.

## Java-to-C++ Translation Guide
*   **Permissions API**: Maps to the Permission API in the browser engine. The grant/deny call must propagate back to the media stream manager or relevant subsystem.
