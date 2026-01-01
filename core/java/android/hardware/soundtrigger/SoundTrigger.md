# SoundTrigger - Reverse Engineering Documentation

## Executive Summary
`SoundTrigger` provides access to the hardware-accelerated sound trigger system, typically used for low-power voice wake-up (e.g., "Hey Google"). It manages sound models (voice patterns), recognition modes, and the transition from low-power detection to full audio capture.

## Architecture Overview
- **System API**: Exposed primarily to system-level applications (voice assistants).
- **HAL Interaction**: Communicates with the Sound Trigger HAL via the `SoundTriggerMiddlewareService`.
- **Concurrency**: Asynchronous event-driven model using `StatusListener` and `Handler` for recognition callbacks.
- **Model Storage**: Uses specialized `SoundModel` objects (Keyphrase or Generic) containing vendor-specific binary data.

## Detailed Functionality

### Module Discovery
**Purpose**: To identify available sound trigger hardware.
**Algorithm**:
1. Call `listModulesAsOriginator()`.
2. Middleware service returns a list of `ModuleProperties`.
3. Properties describe capabilities like AEC (Echo Cancellation), Noise Suppression, and max supported models.

### Recognition Workflow
**Purpose**: To start/stop listening for a specific sound pattern.
1. **Enrollment**: Application trains a model and obtains binary data.
2. **Loading**: Model is loaded into hardware via `SoundTriggerModule.loadSoundModel()`.
3. **Starting**: Recognition is started with a `RecognitionConfig`.
4. **Triggering**: Hardware detects the pattern and fires a `RecognitionEvent`.
5. **Capture**: If `captureRequested` was true, an audio session ID is provided to start `AudioRecord` without losing the trigger utterance.

## Data Model

### SoundTrigger.ModuleProperties
- `mId`: Unique module ID.
- `mUuid`: Globally unique identifier for the engine.
- `mRecognitionModes`: Bitmask of supported modes (`VOICE_TRIGGER`, `USER_ID`, etc.).
- `mAudioCapabilities`: Bitmask of supported DSP features (`ECHO_CANCELLATION`, `NOISE_SUPPRESSION`).

### SoundTrigger.RecognitionConfig
- `captureRequested`: Whether to buffer audio for subsequent capture.
- `keyphrases`: Extra settings for specific phrases (e.g., thresholds).
- `data`: Opaque vendor-specific configuration data.

## API Reference

### Key Constants
- `RECOGNITION_MODE_VOICE_TRIGGER`: Trigger on pattern match.
- `RECOGNITION_MODE_USER_IDENTIFICATION`: Trigger only if a specific user is identified.
- `STATUS_OK`: 0.
- `STATUS_BUSY`: Transient resource exhaustion.

### Static Methods
- `handleException(Exception e)`: Maps system/IPC errors to `SoundTrigger` status codes.
- `attachModuleAsOriginator(...)`: Creates a `SoundTriggerModule` instance for hardware interaction.

## Java-to-C++ Translation Guide

### Error Handling
- **Java**: Uses integer status codes and an exception translator.
- **C++**: Return `android::status_t` or `std::expected<void, SoundTriggerError>`.

### Hardware Modules
- **Java**: `ArrayList<ModuleProperties>`.
- **C++**: Use a `std::vector<ModuleProperties>` populated via Binder from `ISoundTriggerMiddlewareService`.

## Test Cases & Validation
1. **Module Listing**: Ensure `listModules` returns at least one module on supported hardware.
2. **Model Loading**: Verify that loading a valid `KeyphraseSoundModel` returns `STATUS_OK` and a valid handle.
3. **Recognition Loop**: Start recognition, simulate a trigger via vendor tools, and verify that `onRecognition` is called with the correct `soundModelHandle`.

## Implementation Risks
- **Concurrency**: The middleware service can die; the implementation must handle `binderDied` and notify the client.
- **Resource Contention**: The DSP often has very limited slots for sound models. The C++ manager must handle `STATUS_BUSY` and prioritize models if necessary.
- **Binary Compatibility**: `SoundModel` data is opaque to the framework but must be delivered to the HAL bit-perfect.
