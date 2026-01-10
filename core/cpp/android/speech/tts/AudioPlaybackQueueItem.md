# AudioPlaybackQueueItem - Reverse Engineering Documentation

## Executive Summary
`AudioPlaybackQueueItem` is a specific implementation of `PlaybackQueueItem` that plays an audio resource (via a URI) using Android's `MediaPlayer`.

## Detailed Functionality

### Core Logic (`run`)
1.  Dispatches `onStart` to the `UtteranceProgressDispatcher`.
2.  Creates a `MediaPlayer` instance for the given URI.
3.  Sets up `AudioAttributes` and session ID from `mAudioParams`.
4.  Configures volume and panning (balance).
5.  Sets listeners for errors and completion.
6.  Calls `MediaPlayer.start()` and blocks on a `ConditionVariable` until completion or error.
7.  Releases the player.
8.  Dispatches `onSuccess`, `onStop`, or `onError` based on final state.

### Volume Scaling (`setupVolume`)
- Clips volume to [0.0, 1.0].
- Clips panning to [-1.0, 1.0].
- Calculates left/right volume based on panning:
    - If pan > 0 (right): `volLeft *= (1.0 - pan)`.
    - If pan < 0 (left): `volRight *= (1.0 + pan)`.

## Java-to-C++ Translation Guide

### Implementation
- Requires a `MediaPlayer` equivalent. In the NDK, this might be `AMediaPlayer` or OpenSL ES / AAudio.
- Volume logic should be replicated exactly.
- Use a synchronization primitive (e.g., `std::condition_variable`) to wait for playback completion.
