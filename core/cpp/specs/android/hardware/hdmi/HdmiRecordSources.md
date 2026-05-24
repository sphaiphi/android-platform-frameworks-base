# HdmiRecordSources - Reverse Engineering Documentation

## Executive Summary
`HdmiRecordSources` is a helper class to construct `RecordSource` objects used for One Touch Record commands. It supports various source types defined in CEC.

## Architecture Overview
- **Type**: Factory / Helper Class.
- **System API**: `@SystemApi`.

## Detailed Functionality

### Record Source Types
1.  **Own Source**: Current screen.
2.  **Digital Service**: Identified by ARIB, ATSC, DVB data, or Channel ID.
3.  **Analogue Service**: Broadcast type, Frequency, Broadcast system.
4.  **External Plug**: Plug number.
5.  **External Physical Address**: Physical address.

### Inner Classes
- `RecordSource` (Abstract Base): Handles common serialization.
- `OwnSource`
- `DigitalServiceSource`: Contains `DigitalServiceIdentification`.
    - `AribData`: Transport Stream ID, Service ID, Original Network ID.
    - `AtscData`: Transport Stream ID, Program Number.
    - `DvbData`: Transport Stream ID, Service ID, Original Network ID.
    - `DigitalChannelData`: Channel Number Format (1-part/2-part), Major/Minor numbers.
- `AnalogueServiceSource`: Broadcast Type (Cable/Sat/Terr), Frequency, System.
- `ExternalPlugData`
- `ExternalPhysicalAddress`

### Byte Serialization
- `toByteArray(boolean includeType, byte[] data, int index)`: Serializes the source into the byte array for the CEC message.
- Handles byte layout per CEC spec (e.g. `[Record Source Type] [Data...]`).

## Java-to-C++ Translation Guide
- **Polymorphism**: Use a base struct `RecordSource` and derived structs.
- **Serialization**: Implement `toByteArray` equivalent. Use `std::vector<uint8_t>` or raw buffers.
- **Validation**: Replicate input range checks (e.g. plug number 1-255).

