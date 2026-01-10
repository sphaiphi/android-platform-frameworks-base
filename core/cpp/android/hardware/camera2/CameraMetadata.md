# CameraMetadata - Reverse Engineering Documentation

## Executive Summary
`CameraMetadata` is the abstract base class for all metadata containers in the Camera2 API (`CameraCharacteristics`, `CaptureRequest`, and `CaptureResult`). It defines the core key-value structure and provides constants for many metadata values used across the API.

## Architecture Overview
- **Structure**: An abstract class that manages a set of tags (keys) and their corresponding values.
- **Key Implementation**: Defines a nested `Key` class for type-safe metadata access.
- **Value Constants**: Contains thousands of static integer constants representing various modes, states, and capability flags (e.g., `CONTROL_AF_MODE_CONTINUOUS_PICTURE`).
- **Templating**: Uses Java generics to ensure that the type of the value retrieved matches the key's defined type.

## Detailed Functionality

### Type-Safe Key Access
**Purpose**: To prevent runtime type errors when accessing metadata.
**Implementation**:
- `Key<T>` stores the `Class<T>` or `TypeReference<T>`.
- The `get(Key<T> key)` method uses this information to cast the raw metadata value to the correct type.

### Capability Discovery
**Purpose**: Defines constants for `REQUEST_AVAILABLE_CAPABILITIES` (e.g., `BACKWARD_COMPATIBLE`, `MANUAL_SENSOR`, `RAW`, `LOGICAL_MULTI_CAMERA`).
**Algorithm**: Applications query `CameraCharacteristics` for the list of supported capability IDs and compare them against these constants.

## Data Model

### Key Hierarchy
- **CameraCharacteristics**: Static metadata (Hardware).
- **CaptureRequest**: Configuration metadata (Software).
- **CaptureResult**: Dynamic metadata (Hardware + Software).

### Common Tags
- `CONTROL_*`: Auto-algorithms and high-level triggers.
- `LENS_*`: Physical lens properties and control.
- `SENSOR_*`: Image sensor properties and raw control.
- `STATISTICS_*`: Analysis output like face detection.

## API Reference

### Public Methods
- `List<TKey> getKeys()`: Abstract method to return the list of keys supported by the specific metadata object.

### Constants (Partial List)
- **Control Modes**: `CONTROL_MODE_OFF`, `AUTO`, `USE_SCENE_MODE`.
- **AF Modes**: `CONTROL_AF_MODE_OFF`, `AUTO`, `MACRO`, `CONTINUOUS_VIDEO`, `CONTINUOUS_PICTURE`.
- **Hardware Levels**: `INFO_SUPPORTED_HARDWARE_LEVEL_LEGACY`, `LIMITED`, `FULL`, `LEVEL_3`, `EXTERNAL`.

## Java-to-C++ Translation Guide

### Abstract Base Class
- **Java**: `public abstract class CameraMetadata<TKey>`
- **C++**: `template<typename TKey> class CameraMetadata`. Consider using a non-templated base class for common functionality like tag ID management.

### Key Implementation
- **Java**: `public static class Key<T>`
- **C++**: `template<typename T> struct Key { const char* name; int tag_id; };`. Using tag IDs (integers) instead of string names for lookups is much more efficient in C++.

### Constant Management
- **Java**: Thousands of `public static final int` constants.
- **C++**: Use `enum class` grouped by category (e.g., `namespace camera { enum class AfMode { ... }; }`). This significantly improves type safety compared to raw integers.

## Test Cases & Validation
1. **Key Uniqueness**: Ensure that no two keys share the same name within the same metadata type.
2. **Type Preservation**: Verify that `get` returns a value of the exact type specified by the key's `T` parameter.

## Implementation Risks
- **Maintenance**: The number of constants is massive and grows with every Android release. Automating the generation of these constants from metadata definitions (AIDL/XML) is highly recommended.
- **Memory Layout**: In C++, `android::CameraMetadata` uses a specific packed binary format for efficiency. The translation must remain compatible with this format for interaction with the camera service.
- **Generic Type Erasure**: Java's `TypeReference` is a workaround for type erasure. C++ can use templates and `std::type_index` to maintain type information more naturally.
