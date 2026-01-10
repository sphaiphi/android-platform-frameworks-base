# HotwordDetectionService - Reverse Engineering Documentation

## Executive Summary
`HotwordDetectionService` is a security-hardened, sandboxed service used for private hotword detection. It runs in an isolated process with no internet access and limited system access to ensure that raw microphone audio used for "always-on" listening is never leaked to the assistant or external servers until the user speaks the trigger phrase.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **Sandboxing**: MUST be declared with `android:isolatedProcess="true"` in the manifest. It has no access to the filesystem (except provided models) or the network.
*   **IPC**: Implements `ISandboxedDetectionService.Stub`.
*   **Lifecycle**: Managed by the `VoiceInteractionManagerService`. It is started when a `HotwordDetector` is initialized and stopped when detection ends.

## Detailed Functionality

### Core Detection Methods
*   **`onDetect(AlwaysOnHotwordDetector.EventPayload, ...)`**:
    *   **Goal**: Perform "second-stage" validation of a hardware trigger (DSP).
    *   **Logic**: The DSP provides a trigger; this service verifies the trigger is accurate before alerting the main `VoiceInteractionService`.
*   **`onDetect(Callback)`**:
    *   **Goal**: Perform software-based detection on audio from the device microphone.
*   **`onDetect(ParcelFileDescriptor, AudioFormat, ...)`**:
    *   **Goal**: Perform detection on an external audio stream (e.g., from a Bluetooth headset).

### State Management
*   **`onUpdateState(PersistableBundle, SharedMemory, ...)`**: Receives configuration and model data (e.g., neural network weights) from the main assistant process.

### Callbacks
*   **`Callback.onDetected(HotwordDetectedResult)`**: Signal that the hotword was successfully found.
*   **`Callback.onRejected(HotwordRejectedResult)`**: Signal that the audio did not contain the hotword.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.voice.HotwordDetectionService"`

## Java-to-C++ Translation Guide

### Security Enforcement
*   **Java**: Enforced by the Android Framework via process isolation and SELinux.
*   **C++**: The actual audio processing logic (signal processing, ML inference) is almost always in C++. It typically involves using a small footprint inference engine like TFLite Micro.

### Data Handling
*   `HotwordDetectedResult` is a Parcelable that can contain small metadata (confidence scores, etc.).
*   `SharedMemory` is used to pass large model files into the isolated process without copying.

## Implementation Risks
*   **Isolated Process Limits**: The service cannot make most system calls. It can only use provided `SystemService` wrappers (like `ContentCaptureManager` or `RecognitionServiceManager`).
*   **Resource Constraints**: Since it may be always running, it must have a very small memory and CPU footprint.
*   **Binder Limits**: Results must be small; `HotwordDetectedResult` has a strict maximum bundle size.
