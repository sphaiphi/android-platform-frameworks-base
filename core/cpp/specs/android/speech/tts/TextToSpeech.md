# TextToSpeech - Reverse Engineering Documentation

## Executive Summary
`TextToSpeech` is the primary public API for synthesizing speech from text. It handles client-side lifecycle management, connecting to the TTS system service, and providing a simplified interface for applications to queue speech, play audio files, and manage voices/locales.

## Architecture Overview

### Connection Management
- Uses two connection strategies: `SystemConnection` (via `ITextToSpeechManager` proxy) or `DirectConnection` (standard service binding).
- Automatically handles fallback to default engines if the requested engine fails to initialize.
- `mInitListener` notifies the application when the engine is ready.

### Threading
- Most public methods are asynchronous and return immediately after queuing the request.
- `mStartLock` protects the connection and parameter state.

## Detailed Functionality

### API Batching
- `speak(CharSequence, int, Bundle, String)`: The main entry point. Converts text to speech.
- `playEarcon(...)`: Plays pre-registered sound effects.
- `playSilentUtterance(...)`: Queues silence.
- `synthesizeToFile(...)`: Renders speech to a WAV file.

### Settings & State
- `setLanguage(Locale)`: Updates the current language. Internally maps Locales to `Voice` objects.
- `setVoice(Voice)`: Selects a specific voice.
- `setSpeechRate(float)` / `setPitch(float)`: Adjusts synthesis parameters.
- `isSpeaking()`: Checks if the engine is currently active.

### Lifecycle
- `shutdown()`: Unbinds the service and releases all resources. Crucial for avoiding memory leaks and service process hanging.

## Java-to-C++ Translation Guide

### Class Mapping
- Map to `TextToSpeech` class.

### Connection Logic
- Requires a Binder implementation to find and bind to the TTS service.
- Must handle the "init" callback pattern using a listener or a future/promise.

### Parameter Handling
- Replicate the conversion logic between `Locale`, `Voice`, and the internal `Bundle` parameters.
- Ensure constant keys (`Engine.KEY_PARAM_...`) match the Java definitions exactly.
