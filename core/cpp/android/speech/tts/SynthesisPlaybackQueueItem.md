# SynthesisPlaybackQueueItem - Reverse Engineering Documentation

## Executive Summary
`SynthesisPlaybackQueueItem` manages the consumption of audio buffers produced by a TTS engine and their playback via a `BlockingAudioTrack`. It acts as a thread-safe bridge between the synthesis thread (producer) and the audio playback thread (consumer).

## Architecture Overview

### Back-pressure Mechanism
- `MAX_UNCONSUMED_AUDIO_MS` (500ms): Limits the amount of audio data queued but not yet sent to the audio hardware.
- `put(byte[])`: Blocks the producer if the amount of unconsumed data exceeds the limit.

### Sync Primitives
- `mListLock` (`ReentrantLock`): Protects the buffer list and byte counter.
- `mReadReady`: Condition signaled when new data is available for playback.
- `mNotFull`: Condition signaled when data is consumed, potentially allowing the producer to resume.

## Detailed Functionality

### Core Logic (`run`)
1.  Initializes `mAudioTrack`.
2.  Dispatches `onStart`.
3.  Enters a loop calling `take()` to get buffers.
4.  Writes buffers to `mAudioTrack`.
5.  Updates performance markers.
6.  Once `take()` returns null (signaling `done` or `stop`), calls `waitAndRelease()` on the track.
7.  Dispatches final status.

### Lifecycle
- `done()`: Sets `mDone = true` and signals `mReadReady`.
- `stop(statusCode)`: Sets `mStopped = true`, signals both conditions, and stops the `mAudioTrack`.

### Marker Support
- `rangeStart(...)`: Adds a `ProgressMarker` to a concurrent queue.
- `onMarkerReached(...)`: Callback from `AudioTrack`. Polls the marker queue and dispatches `onRangeStart` to the client.

## Java-to-C++ Translation Guide

### Data Structures
- Use `std::deque<std::vector<uint8_t>>` for the buffer list.
- Use `std::mutex` and `std::condition_variable` for the producer-consumer sync.

### Logic
- Replicate the frame-to-millisecond calculation for back-pressure.
- Ensure the `run()` loop handles the `null` return from `take()` correctly to exit.
