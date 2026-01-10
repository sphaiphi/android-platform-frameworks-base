# VibrationEffect - Reverse Engineering Documentation

## Executive Summary
`VibrationEffect` is an abstract Parcelable base class for defining haptic feedback patterns. It supports multiple implementations: `OneShot` (single pulse), `Waveform` (amplitude/timing pairs), `Prebaked` (hardware effects), and `Composed` (sequences of primitives).

## Architecture Overview
-   **Pattern**: Abstract Factory / Composition.
-   **Subclasses** (Internal/Nested):
    -   `Composed`: A list of `VibrationEffectSegment`s.
    -   `VendorEffect`: Vendor-specific payload.
-   **Segments**: The building blocks (`StepSegment`, `RampSegment`, `PrimitiveSegment`, `PrebakedSegment`).

## Data Model

### Constants
-   `DEFAULT_AMPLITUDE` (-1): Let system decide.
-   `MAX_AMPLITUDE` (255).
-   `EFFECT_CLICK`, `EFFECT_TICK`, etc.: Predefined effect IDs.

### Composition
-   **Composition Class**: Helper builder to create a `Composed` effect by adding primitives (`PRIMITIVE_CLICK`, `PRIMITIVE_TICK`, etc.) with scaling and delays.

## API Reference
-   `createOneShot(long millis, int amplitude)`
-   `createWaveform(long[] timings, int[] amplitudes, int repeat)`
-   `createPredefined(int effectId)`
-   `startComposition()`: Returns a `Composition` builder.

## Java-to-C++ Translation Guide
-   **Polymorphism**: C++ `VibrationEffect` should be a base struct/class with a type enum (`Type::ONE_SHOT`, `Type::WAVEFORM`, `Type::COMPOSITION`).
-   **Union**: Use `std::variant` or a union to hold the specific data for each type (duration+amp for one-shot, vectors for waveform, vector of primitives for composition).
-   **Parceling**: Serialization logic must handle the polymorphic types. Java writes a token (e.g. `PARCEL_TOKEN_COMPOSED`) to identify the subclass. C++ must match this.

## Implementation Risks
-   **Validation**: Java performs extensive validation (positive durations, amplitudes 0-255). C++ *must* replicate this to prevent passing invalid data to the HAL.
-   **Complexity**: The `Composed` effect allows mixing different segment types. The HAL might only support specific combinations (e.g., only primitives). The framework layer (Java) usually handles flattening or rejecting unsupported combos.
