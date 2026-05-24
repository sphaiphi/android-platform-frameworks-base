# TextToSpeechService - Reverse Engineering Documentation

## Executive Summary
`TextToSpeechService` is the abstract base class for implementing a TTS engine. It manages the complex threading, queuing, and audio playback logic required for a high-quality TTS experience, allowing developers to focus on the core synthesis algorithms.

## Architecture Overview

### Threading Model
- **Main Thread**: Standard Service lifecycle.
- **Synthesis Thread** (`SynthThread`): A dedicated thread for generating audio data from text. Ensures that CPU-intensive synthesis doesn't block the UI or IPC.
- **Audio Playback Thread** (`AudioPlaybackThread`): Handled by `AudioPlaybackHandler`.

### Queuing System
- `SynthHandler`: Manages the queue of `SpeechItem` objects.
- Supports `QUEUE_FLUSH` (interrupt current and clear queue) and `QUEUE_ADD` (append to end).

## Detailed Functionality

### Abstract Methods (Engine Implementation)
- `onIsLanguageAvailable(lang, country, variant)`
- `onLoadLanguage(lang, country, variant)`
- `onSynthesizeText(SynthesisRequest, SynthesisCallback)`: The core method. Implementation must block until synthesis is finished.
- `onStop()`: Abort current synthesis.

### Internal Request Processing
1.  Binder call `speak()` / `synthesizeToFileDescriptor()` lands in `mBinder`.
2.  Creates a `SpeechItem` (e.g., `SynthesisSpeechItem`).
3.  Enqueues the item in `mSynthHandler`.
4.  `SynthHandler` executes the item on the `SynthThread`.
5.  `playImpl()` calls `onSynthesizeText(...)`.
6.  Audio data is delivered via the callback to the `AudioPlaybackHandler`.

## Java-to-C++ Translation Guide

### Service Implementation
- Map to a Binder service implementation (`BnTextToSpeechService`).
- Replicate the three-thread architecture (IPC, Synthesis, Playback) to maintain performance and responsiveness.

### Queuing Logic
- Implement a thread-safe queue for `SpeechItem` objects.
- Use a priority or message-based dispatch system to handle the different queue modes correctly.

### IPC
- Implement the `ITextToSpeechService` AIDL interface.
