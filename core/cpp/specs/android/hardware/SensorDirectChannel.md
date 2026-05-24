# SensorDirectChannel - Reverse Engineering Documentation

## Executive Summary
`SensorDirectChannel` represents a high-performance communication channel that allows sensors to write data directly into shared memory (`MemoryFile` or `HardwareBuffer`) without CPU intervention. This is intended for low-latency applications like VR/AR.

## Architecture Overview
The class implements the `java.nio.channels.Channel` interface. It is created via `SensorManager` and wraps a native handle. It uses `CloseGuard` for lifecycle tracking.

## Detailed Functionality

### Configuration
- `configure(Sensor, rateLevel)`: Starts or stops delivery of sensor events into the channel.
- **Rate Levels**: `STOP` (0), `NORMAL` (50Hz), `FAST` (200Hz), `VERY_FAST` (800Hz).

### Data Structure
Each event in the shared memory queue is **104 bytes** (little-endian):
- `0x0000` (4 bytes): Size (always 104).
- `0x0004` (4 bytes): Sensor report token.
- `0x0008` (4 bytes): Type.
- `0x000C` (4 bytes): Atomic counter (increments per event).
- `0x0010` (8 bytes): Timestamp.
- `0x0018` (64 bytes): Data (float[16] or int64[8]).
- `0x0058` (16 bytes): Reserved.

### Queue Management
There are no head/tail pointers. The consumer must poll the atomic counter to find new events. The buffer is circular.

## Data Model
- **MemoryType**: `TYPE_MEMORY_FILE` (1), `TYPE_HARDWARE_BUFFER` (2).

## Java-to-C++ Translation Guide
- **Atomic Counter**: Must use atomic operations compatible with the hardware's memory model to ensure no partial writes are read.
- **Memory Layout**: Use a packed `struct` in C++ to match the 104-byte layout exactly.
- **JNI**: `encodeData` handles FD extraction from `MemoryFile`.

## Implementation Risks
- Memory corruption if multiple writers or readers access the buffer without proper synchronization (though the design minimizes this via the atomic counter).
- Power consumption at `RATE_VERY_FAST`.
