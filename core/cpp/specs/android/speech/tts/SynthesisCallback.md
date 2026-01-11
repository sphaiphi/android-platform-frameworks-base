# SynthesisCallback - Reverse Engineering Documentation

## Executive Summary
`SynthesisCallback` is the interface provided to TTS engines to deliver synthesized audio data. It supports streaming audio, allowing the engine to provide chunks of data as they are generated.

## API Reference

### Configuration
- `int getMaxBufferSize()`: Returns the max buffer size allowed for `audioAvailable`.

### Lifecycle
- `int start(sampleRate, audioFormat, channelCount)`: Called when synthesis begins.
- `int audioAvailable(buffer, offset, length)`: Called to provide a chunk of audio.
- `int done()`: Called when synthesis is complete.
- `void error()` / `void error(int errorCode)`: Called on failure.

### Metadata
- `void rangeStart(markerInFrames, start, end)`: Optional. Provides timing information linking audio frames to text offsets.

### Status
- `boolean hasStarted()`
- `boolean hasFinished()`

## Java-to-C++ Translation Guide
- Map to a pure virtual interface in C++.
- Ensure the methods match the AIDL/JNI requirements for the specific platform implementation.
