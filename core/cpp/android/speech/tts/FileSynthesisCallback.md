# FileSynthesisCallback - Reverse Engineering Documentation

## Executive Summary
`FileSynthesisCallback` implements the `SynthesisCallback` interface to save synthesized speech data directly to a WAV file. It manages the creation of the WAV header and the writing of PCM audio chunks to a `FileChannel`.

## Architecture Overview

### WAV Format
- Supports PCM 8-bit, 16-bit, and Float.
- Writes a 44-byte WAV header.
- Header fields are written in Little Endian.

## Detailed Functionality

### Lifecycle
1.  `start(...)`: Writes a blank 44-byte placeholder for the WAV header to the start of the file.
2.  `audioAvailable(...)`: Wraps the provided byte array and writes it to the `FileChannel`.
3.  `done()`:
    - Calculates the total data length (`file_size - 44`).
    - Seeks to position 0.
    - Overwrites the placeholder with a valid WAV header containing correct length and format info.
    - Dispatches `onSuccess`.

### Error Handling
- If `stop()` or `error()` is called, it cleans up (nulls the channel) and reports the state.

## Java-to-C++ Translation Guide

### File I/O
- Use `std::ofstream` or POSIX `write()` with a file descriptor.
- Ensure Little Endian byte order for the WAV header (use `<endian.h>` or manual bit shifting).

### Serialization
- The WAV header structure:
    - "RIFF" chunk descriptor.
    - Chunk size.
    - "WAVE" format.
    - "fmt " sub-chunk.
    - Audio format (PCM = 1).
    - Channels, Sample Rate, Byte Rate, Block Align, Bits Per Sample.
    - "data" sub-chunk.
    - Data size.
