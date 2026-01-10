# NanoAppBinary - Reverse Engineering Documentation

## Executive Summary
`NanoAppBinary` represents the executable binary of a nanoapp. It includes functionality to parse the proprietary header (defined in `context_hub.h`) to extract metadata like App ID, Version, and Flags without needing to fully decode the binary structure elsewhere.

## Architecture Overview
- **Pattern**: Byte Wrapper / Parser.
- **Inheritance**: Implements `android.os.Parcelable`.

## Detailed Functionality
- **Header Parsing**: Parses the first 40 bytes (`HEADER_SIZE_BYTES`) of the binary.
- **Validation**: Checks Magic value (`0x4F4E414E` - "NANO").
- **Fields extracted**: Header Version, App ID, App Version, Flags (Signed/Encrypted), Hub Type, CHRE API Version.

## Data Model
- `mNanoAppBinary`: `byte[]` (Full content).
- Parsed fields (`mNanoAppId`, `mFlags`, etc.).

## Java-to-C++ Translation Guide
- **C++ Equivalent**: This mimics the `nano_app_binary_t` struct layout in C. The C++ implementation likely already exists as a struct.
- **Byte Order**: Header is Little Endian.

## Questions for C++ Team
- None. This is a direct mapping of the C header structure.
