# ComponentInfoInternal - Reverse Engineering Documentation

## Executive Summary
`ComponentInfoInternal` is a Parcelable class used to store detailed information about a subsystem of a biometric sensor (e.g., matching engine, sensor hardware). It allows passing version and serial number information across IPC.

## Architecture Overview
A simple data transfer object (DTO) used within `SensorProperties`.

## Detailed Functionality

### Fields
- `componentId`: String identifier.
- `hardwareVersion`: HW revision.
- `firmwareVersion`: FW version.
- `serialNumber`: Unique serial.
- `softwareVersion`: SW version.

## Java-to-C++ Translation Guide
- **Struct**: `struct ComponentInfo`.
- **Types**: `std::string` for all fields.
- **Parceling**: Standard read/write string.

## Implementation Risks
- None.
