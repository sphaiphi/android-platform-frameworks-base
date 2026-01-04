# UtteranceProgressListener - Reverse Engineering Documentation

## Executive Summary
`UtteranceProgressListener` is a client-side listener for monitoring the progress of a specific utterance through the TTS synthesis and playback pipeline. It provides fine-grained callbacks for starts, chunks of audio, errors, and completion.

## API Reference

### Lifecycle Callbacks
- `void onStart(String utteranceId)`: Playback or file writing has begun.
- `void onDone(String utteranceId)`: Successful completion.
- `void onError(String utteranceId, int errorCode)`: Failure occurred.
- `void onStop(String utteranceId, boolean interrupted)`: Aborted by client.

### Data & Timing Callbacks
- `void onBeginSynthesis(utteranceId, sampleRate, audioFormat, channels)`: Engine started generating audio.
- `void onAudioAvailable(utteranceId, byte[] audio)`: A chunk of synthesized audio is ready.
- `void onRangeStart(utteranceId, start, end, frame)`: The specified text range is about to be played.

## Java-to-C++ Translation Guide
- Map to an abstract class or interface in C++.
- Ensure that callbacks can be dispatched on any thread, as per the Java implementation notes.
