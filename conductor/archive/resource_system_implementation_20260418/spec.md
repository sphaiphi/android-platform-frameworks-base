# Specification - Resource System Implementation (android.content.res)

## Overview
This track focuses on implementing the foundational classes for Android's resource management system in modern C++. This system provides the infrastructure needed to decouple application data (strings, dimensions, colors) from logic, enabling configuration-aware resource resolution (e.g., different layouts for landscape vs. portrait).

## Functional Requirements
- **Asset Access**:
    - `AssetManager`: Provide low-level access to raw data files stored within the application's assets directory.
- **Resource Resolution**:
    - `Resources`: The high-level API for retrieving resolved values based on unique IDs.
    - Support for core resource types: `String`, `Dimension` (dp, sp, px), `Color`, and `Integer`.
- **Configuration Management**:
    - `Configuration`: Encapsulate device settings like orientation, screen size, and UI mode.
    - `DisplayMetrics`: Store physical display properties (density, scaling factors) for unit conversion.
- **Data Containers**:
    - `TypedValue`: A container for dynamically typed data retrieved from resources.
- **Manual Table Support**:
    - Initial implementation will support manual registration of resource IDs to values (mocking the `.arsc` binary table loading for now).

## Non-Functional Requirements
- **C++23 Modernity**: Use `std::expected` for error-prone resource lookups and `std::span` for efficient memory handling in `AssetManager`.
- **Performance**: Minimize lookup overhead through efficient ID-to-value mapping.
- **API Parity**: Closely follow the `android.content.res` SDK naming and behavioral conventions.

## Acceptance Criteria
1. `AssetManager` successfully reads raw data from the filesystem.
2. `Resources` correctly resolves a dimension ID into pixels using `DisplayMetrics` (e.g., 16dp -> 32px on xhdpi).
3. `Configuration` changes trigger appropriate resource re-resolution (simulated).
4. `TypedValue` correctly identifies and converts data types.
5. Unit tests in `core/cpp/tests/` verify the resolution and conversion logic.

## Out of Scope
- Full binary XML parsing (`LayoutInflater` is a separate track).
- Complex resource qualifiers (e.g., MCC/MNC, language/region) beyond orientation and density.
- Theme/Style resolution (will be added in a follow-up track).
