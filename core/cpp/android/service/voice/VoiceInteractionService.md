# VoiceInteractionService - Reverse Engineering Documentation

## Executive Summary
`VoiceInteractionService` is the top-level, always-running service for the current system-wide voice assistant (e.g., Google Assistant). It manages hotword detection hardware, initiates voice interaction sessions, and provides the background presence necessary for the assistant to respond to "hands-free" triggers.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **Role**: Acts as the assistant's background "ear." It should be extremely lightweight as it is kept running by the system at all times.
*   **IPC**: Implements `IVoiceInteractionService.Stub`. It communicates with the `VoiceInteractionManagerService` in the system server.
*   **Component Model**: Works in tandem with `VoiceInteractionSessionService` (which creates the UI session) and `HotwordDetectionService` (a sandboxed service for private hotword validation).
*   **Permission**: Requires `android.permission.BIND_VOICE_INTERACTION`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IVoiceInteractionService` binder interface.

### Detector Management
*   **`createAlwaysOnHotwordDetector`**: Creates a detector that leverages hardware (DSP) for low-power hotword detection.
*   **`createHotwordDetector`**: Creates a software-based detector (uses the microphone directly).
*   **`createVisualQueryDetector`**: Creates a detector for visual triggers (looking at the device).
*   **Sandboxing**: Modern detectors use a `HotwordDetectionService` running in an isolated process to ensure the assistant cannot listen to the microphone until the hotword is confirmed.

### Session Control
*   **`showSession(Bundle, int)`**: Requests the system to start a `VoiceInteractionSession` and show the assistant UI.
*   **`onPrepareToShowSession`**: Lifecycle hook called when the system is about to show the assistant UI.

### System Callbacks
*   **`onReady()`**: Called when the system service connection is established.
*   **`onLaunchVoiceAssistFromKeyguard()`**: Called when the user triggers the assistant while the device is locked.
*   **`onSoundModelsChangedInternal()`**: Notifies the service when the registered hotword sound models (voice enrollment) have changed.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.voice.VoiceInteractionService"`
*   `SERVICE_META_DATA`: `"android.voice_interaction"` - Points to an XML file describing capabilities (e.g., `supportsAssist`).

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IVoiceInteractionService.Stub`.
*   **C++**: `BnVoiceInteractionService`.
*   **Manager Proxy**: Uses `IVoiceInteractionManagerService` to request sessions or manage sound models.

### State Tracking
*   The service must track active `HotwordDetector` instances and ensure they are destroyed properly to avoid resource leaks (microphone usage).

## Implementation Risks
*   **Battery Impact**: Mismanaging detectors can lead to "vampire" microphone usage.
*   **Privacy**: As an always-on service, security is paramount. The use of the sandboxed `HotwordDetectionService` is a mandatory security control for modern assistants.
*   **System Stability**: Since it's always running, any memory leak or crash will be visible to the user and can degrade system performance.
