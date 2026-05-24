# SoundModel - Reverse Engineering Documentation

## Executive Summary
`SoundModel` is the base class for binary patterns used by the `SoundTrigger` system to detect specific sounds. It contains unique identifiers, versioning information, and the opaque binary data that is loaded into the hardware DSP for real-time monitoring.

## Architecture Overview
- **Hierarchy**: Base class for `KeyphraseSoundModel` (voice triggers) and `GenericSoundModel` (non-voice patterns like glass breaking).
- **Storage**: Immutable data container.
- **Payload**: Contains a `byte[]` which is purely vendor-specific and not parsed by the Android framework.

## Detailed Functionality

### Identification
**Purpose**: To track models across processes and hardware sessions.
- `mUuid`: Globally unique ID for the specific sound model.
- `mVendorUuid`: Identifies the vendor/OEM providing the engine.

### Versioning
**Purpose**: To ensure the model is compatible with the loaded hardware driver.
- `mVersion`: Incremental version number.

## Data Model

### Members
- `mUuid` (`UUID`): Model ID.
- `mVendorUuid` (`UUID`): Vendor ID.
- `mType` (`int`): `TYPE_KEYPHRASE` (0) or `TYPE_GENERIC_SOUND` (1).
- `mData` (`byte[]`): The binary payload.

## API Reference

### Public Methods
- `UUID getUuid()`
- `UUID getVendorUuid()`
- `int getType()`
- `int getVersion()`
- `byte[] getData()`

## Java-to-C++ Translation Guide

### Data Representation
- **Java**: `java.util.UUID` and `byte[]`.
- **C++**: Use a standard UUID struct (128 bits) and `std::vector<uint8_t>`.

### Memory Management
- **Java**: Garbage collected.
- **C++**: Since model data can be large (KBs to MBs), use `std::shared_ptr<const SoundModel>` or move semantics to avoid copying the binary blob.

## Test Cases & Validation
1. **Binary Integrity**: Verify that creating a `SoundModel` and retrieving `getData()` returns an array identical to the input.
2. **Equality**: Ensure two models with the same UUID and data are considered equal.
3. **Null Handling**: Verify that a `null` data array is safely converted to an empty `byte[0]`.
