# HdmiTimerRecordSources - Reverse Engineering Documentation

## Executive Summary
`HdmiTimerRecordSources` is a helper class for creating `TimerRecordSource` objects used in Timer Recording CEC commands.

## Architecture Overview
- **Type**: Factory / Helper Class.
- **System API**: `@SystemApi`.

## Detailed Functionality

### Components
1.  **TimerInfo**:
    - Day of Month, Month of Year.
    - Start Time (Hour, Minute).
    - Duration (Hour, Minute).
    - Recording Sequence (Days of week bitmask).
2.  **RecordSource**: Uses `HdmiRecordSources.RecordSource` (Digital, Analogue, External).

### Factory Methods
- `ofDigitalSource`, `ofAnalogueSource`, `ofExternalPlug`, `ofExternalPhysicalAddress`.
- Combines `TimerInfo` and the specific `RecordSource`.
- Wraps External sources in `ExternalSourceDecorator` to add the "External Source Specifier" byte.

### Serialization
- `TimerInfo.toByteArray`: Serializes time/date info.
- `TimerRecordSource.toByteArray`: Concatenates TimerInfo and RecordSource bytes.
- **BCD Encoding**: Time/Duration values are encoded in BCD (Binary Coded Decimal).

## Data Model
- `Time`, `Duration`: Helper classes holding hour/minute.
- `TimerInfo`: Holds all timing data.
- `TimerRecordSource`: Container for Info + Source.

## Java-to-C++ Translation Guide
- **BCD**: Implement BCD conversion utility (`toBcdByte`).
- **Structure**: Replicate the composition pattern (TimerInfo + RecordSource).
- **Serialization**: Ensure byte order and BCD encoding match CEC spec.

