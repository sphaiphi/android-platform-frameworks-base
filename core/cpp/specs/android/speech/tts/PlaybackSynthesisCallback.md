# PlaybackSynthesisCallback - Reverse Engineering Documentation

## Executive Summary
`PlaybackSynthesisCallback` is a `SynthesisCallback` implementation that streams synthesized audio data to an `AudioPlaybackHandler` for immediate playback. It acts as a producer for the `SynthesisPlaybackQueueItem`.

## Architecture Overview

### Components
- `mAudioTrackHandler`: The handler that manages the playback thread.
- `mItem`: A `SynthesisPlaybackQueueItem` created when `start()` is called.

## Detailed Functionality

### Streaming Logic
- `start(...)`: Creates a new `SynthesisPlaybackQueueItem` and enqueues it in the `mAudioTrackHandler`.
- `audioAvailable(...)`: Copies the incoming buffer and calls `mItem.put(buffer)`. This may block if the playback queue is full (to apply back-pressure to the TTS engine).
- `done()`: Calls `mItem.done()` to signal the end of the stream.

### Lifecycle
- Handles premature `stop()` or `error()` calls by notifying both the dispatcher and the logger.

## Java-to-C++ Translation Guide

### Back-pressure
- The `put()` call in Java blocks if the consumer is slow. In C++, implement this using a bounded queue with a condition variable.
- Ensure that `stop()` can unblock a thread stuck in `put()`.
