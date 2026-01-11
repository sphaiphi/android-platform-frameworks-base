# BlockingAudioTrack - Reverse Engineering Documentation

## Executive Summary
`BlockingAudioTrack` is a wrapper around the Android `AudioTrack` class. It provides a simplified interface for streaming PCM audio data and adds a critical "blocking" feature: it can wait until all written audio data has actually been played by the hardware before releasing the resource.

## Architecture Overview

### Internal State
- `mAudioTrack`: The underlying `android.media.AudioTrack` instance.
- `mAudioBufferSize`: Size of the internal buffer.
- `mBytesWritten`: Counter for total bytes pushed to the track.
- `mIsShortUtterance`: Flag for utterances smaller than the buffer size.

## Detailed Functionality

### Write Logic
- Restarts playback if the track isn't in `PLAYSTATE_PLAYING`.
- Loop writes the entire buffer, handling partial writes.

### Blocking Logic (`waitAndRelease`)
- For small utterances (bytes < buffer size): Calls `AudioTrack.stop()` to force-flush the buffer to the mixer, then sleeps for the estimated duration of the audio.
- For normal utterances:
    - Loops while `getPlaybackHeadPosition()` < `lengthInFrames`.
    - Calculates `sleepTimeMs` based on remaining frames and sample rate.
    - Includes a safety `MAX_PROGRESS_WAIT_MS` (2.5s) to avoid hanging if the media server crashes.

### Timing Calculation (`getAudioLengthMs`)
- Converts byte count to frames using `mBytesPerFrame`.
- Divides by `mSampleRateInHz` to get milliseconds.

## Java-to-C++ Translation Guide

### Audio API
- Map to `AAudio` or `OpenSL ES` in C++.
- Both APIs provide mechanisms to query current playback position (frame timestamp).

### Blocking Wait
- Replicate the loop checking the playback position against the total frames written.
- Ensure the safety timeout is implemented to prevent deadlocks in audio service failure scenarios.
- Handle "short utterance" flushing specifically if the underlying C++ API doesn't guarantee immediate playback of small buffers.
