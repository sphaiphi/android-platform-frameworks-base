# AbstractEventLogger - Reverse Engineering Documentation

## Executive Summary
`AbstractEventLogger` is a base class used within the TTS (Text-to-Speech) framework to track and log performance metrics of synthesis requests. it measures latencies across different stages: request processing, engine data generation, and audio playback.

## Data Model

### Timestamps (long, elapsedRealtime)
- `mReceivedTime`: When the request was created.
- `mRequestProcessingStartTime`: When it was picked from the queue.
- `mEngineStartTime`: When the first chunk of data was received from the engine.
- `mEngineCompleteTime`: When the engine finished processing.
- `mPlaybackStartTime`: When the first chunk of audio was actually played.

### Metadata
- `mServiceApp`: Package name of the TTS engine service.
- `mCallerUid`: UID of the calling app.
- `mCallerPid`: PID of the calling app.

## Detailed Functionality

### Lifecycle Hooks
- `onRequestProcessingStart()`: Marks start of queue processing.
- `onEngineDataReceived()`: Marks when engine starts providing data (sets `mEngineStartTime` once).
- `onEngineComplete()`: Marks engine completion.
- `onAudioDataWritten()`: Marks start of playback (sets `mPlaybackStartTime` once).

### Completion Logging (`onCompleted`)
- Calculates:
    - `audioLatency`: `mPlaybackStartTime - mReceivedTime`.
    - `engineLatency`: `mEngineStartTime - mRequestProcessingStartTime`.
    - `engineTotal`: `mEngineCompleteTime - mRequestProcessingStartTime`.
- Calls abstract `logSuccess` or `logFailure`.
- Skips latency reporting if the request was stopped or failed early.

## Java-to-C++ Translation Guide

### Implementation
- Map to an abstract class `AbstractEventLogger`.
- Use `std::chrono::steady_clock` for timestamps.
- Use `std::atomic` or volatile for timestamps if accessed across threads (though the class notes usually a single thread for specific methods).

### Performance Note
- Measuring `elapsedRealtime` is zero-cost in modern systems (system call or VDSO).
