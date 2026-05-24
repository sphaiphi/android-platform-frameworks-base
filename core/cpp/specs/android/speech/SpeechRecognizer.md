# SpeechRecognizer - Reverse Engineering Documentation

## Executive Summary
`SpeechRecognizer` is the main entry point for applications to access speech recognition features in Android. It provides a high-level API to interact with the underlying `RecognitionService`. It manages service binding, listener dispatching, and supports both system-default and on-device recognizers.

## Architecture Overview

### Design Pattern: Proxy / Implementation
- `SpeechRecognizer` defines the public API.
- `SpeechRecognizerImpl` (internal) handles the actual logic of binding to the `IRecognitionServiceManager` and `IRecognitionService`.
- `SpeechRecognizerProxy` (internal) wraps the implementation to provide cleanup/lifecycle management (using `CloseGuard`).

### Lifecycle
- Created via factory methods: `createSpeechRecognizer()` or `createOnDeviceSpeechRecognizer()`.
- Must be destroyed by the caller via `destroy()`.
- Requires `RECORD_AUDIO` permission.

### IPC
- Communicates with `RecognitionServiceManager` to create a session.
- Communicates with the returned `IRecognitionService` for recognition commands.

## API Reference

### Factory Methods
- `static boolean isRecognitionAvailable(Context)`: Checks if any recognizer is available.
- `static boolean isOnDeviceRecognitionAvailable(Context)`: Checks if on-device recognition is supported.
- `static SpeechRecognizer createSpeechRecognizer(Context)`: Creates a system recognizer.
- `static SpeechRecognizer createSpeechRecognizer(Context, ComponentName)`: Creates a recognizer for a specific component.
- `static SpeechRecognizer createOnDeviceSpeechRecognizer(Context)`: Creates an on-device recognizer.

### Main API
- `setRecognitionListener(RecognitionListener)`: Sets the callback for recognition events.
- `startListening(Intent)`: Starts capturing audio and recognizing.
- `stopListening()`: Stops capturing audio, continues recognizing existing buffer.
- `cancel()`: Aborts recognition.
- `destroy()`: Cleans up resources and unbinds from service.

### Support & Download API
- `checkRecognitionSupport(Intent, Executor, RecognitionSupportCallback)`: Queries support level for an intent.
- `triggerModelDownload(Intent)`: Triggers model download.
- `triggerModelDownload(Intent, Executor, ModelDownloadListener)`: Triggers download with progress tracking.

### Constants (Bundle Keys)
- `RESULTS_RECOGNITION`: ArrayList\<String\> of results.
- `CONFIDENCE_SCORES`: float[] of confidence scores.
- `RESULTS_ALTERNATIVES`: ArrayList\<AlternativeSpans\>.
- `RECOGNITION_PARTS`: ArrayList\<RecognitionPart\>.
- `DETECTED_LANGUAGE`, `LANGUAGE_DETECTION_CONFIDENCE_LEVEL`, `TOP_LOCALE_ALTERNATIVES`, `LANGUAGE_SWITCH_RESULT`.

### Error Codes
- `ERROR_NETWORK_TIMEOUT` (1), `ERROR_NETWORK` (2), `ERROR_AUDIO` (3), `ERROR_SERVER` (4), `ERROR_CLIENT` (5), etc.

## Java-to-C++ Translation Guide

### Type
- Map to a class `SpeechRecognizer`.

### Implementation Details
- Requires a Binder-based implementation to talk to `IRecognitionServiceManager`.
- Needs to manage an asynchronous connection lifecycle (connecting to system service before sending commands).
- Must enforce calls from the main thread (or a consistent thread) to match Java behavior.

### Callback Management
- Map `RecognitionListener` to a C++ interface.
- Implement an internal `BnRecognitionListener` to receive Binder callbacks and marshal them to the application's listener.
