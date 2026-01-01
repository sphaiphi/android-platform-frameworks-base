# HdmiRecordListener - Reverse Engineering Documentation

## Executive Summary
`HdmiRecordListener` is an abstract class for receiving callbacks related to HDMI recording features (One Touch Record, Timer Recording).

## Architecture Overview
- **Role**: Client Listener Interface.
- **System API**: `@SystemApi`.

## Detailed Functionality

### Methods
- `onOneTouchRecordSourceRequested(int recorderAddress)`: Abstract. TV asks client for a `RecordSource` to start recording.
- `onOneTouchRecordResult(int recorderAddress, int result)`: Reports start/failure of one touch record.
- `onTimerRecordingResult(int recorderAddress, TimerStatusData data)`: Reports timer recording result.
- `onClearTimerRecordingResult(int recorderAddress, int result)`: Reports result of clearing a timer.

### Inner Class: TimerStatusData
- **Purpose**: Parses the 4-byte [Timer Status Data] operand.
- **Fields**:
    - `mOverlapped`: Timer overlap warning.
    - `mMediaInfo`: Media presence/protection.
    - `mProgrammed`: Programmed indicator.
    - `mProgrammedInfo` / `mNotProgrammedError`: Status codes.
    - `mDurationHour`, `mDurationMinute`: Available space estimate.
    - `mExtraError`: Framework specific error.
- **Parsing**: Bit manipulation to extract fields from the integer representation.

## Java-to-C++ Translation Guide
- **Pattern**: Abstract C++ class or interface with virtual methods.
- **Bit Parsing**: `TimerStatusData.parseFrom` contains bitwise logic (shifting/masking) that must be replicated exactly in C++.

## Implementation Risks
- **Bit Manipulation**: Ensure endianness and bit positions match the Java implementation (and CEC spec).

