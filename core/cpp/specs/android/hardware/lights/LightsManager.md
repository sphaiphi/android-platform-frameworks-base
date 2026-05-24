# LightsManager - Reverse Engineering Documentation

## Executive Summary
`LightsManager` is the abstract base class and public API for controlling device lights. It defines the contract for querying available lights (`Light`) and managing their states (`LightState`) through sessions (`LightsSession`). The actual implementation is provided by `SystemLightsManager`.

## Architecture Overview
- **Pattern**: Abstract Base Class / Service Interface.
- **Role**: Public API surface.
- **Components**:
  - `LightsSession` (Inner Class): Represents a transactional scope for light requests, handling priority and lifecycle (AutoCloseable).
  - `LightsRequest`: (Used in method signatures) Encapsulates the desired state changes.

## Detailed Functionality

### Core Methods
- `getLights()`: Returns list of available `Light` objects.
- `getLightState(Light)`: Returns current `LightState` for a specific light.
- `openSession(int priority)`: Starts a new control session. Higher priority sessions override lower ones.

### LightsSession
**Purpose**: Manages a set of light overrides.
- **Token**: Uses a `Binder` token (`mToken`) to uniquely identify the session to the system service (for death reception and cleanup).
- **Methods**:
  - `requestLights(LightsRequest)`: Applies a batch of state changes.
  - `close()`: Ends the session.

## Data Model
No state is stored in `LightsManager` itself (it's abstract).
`LightsSession` holds:
- `mToken`: `IBinder` (identity token).

## API Reference
See code for full signatures. Key contracts:
- `@NonNull` return types for lists.
- `AutoCloseable` implementation on `LightsSession` requires `close()` to be called (try-with-resources compatible).

## Java-to-C++ Translation Guide

### Architecture Mapping
- **Java**: `LightsManager` (Abstract) -> `SystemLightsManager` (Impl).
- **C++**: Likely a single class `LightsManager` wrapping the Binder interface.

### Translation Strategy
1.  **Abstract Class**: In C++, this layer might be skipped, directly implementing the logic in a concrete class, or using an abstract interface `ILightsManager` (pure virtual) if dependency injection is needed.
2.  **Inner Classes**: `LightsSession` can be a nested class or a separate `LightsSession` class in C++.
3.  **Binder Token**: `mToken = new Binder()` in Java creates a local Binder object. In C++, use `sp<BBinder> token = new BBinder();` to create a local binder identity.

### Concurrency
- The API implies thread safety requirements for the underlying implementation, though the abstract base doesn't enforce it.

## Questions for C++ Team
- Do we need the abstract base class pattern in C++, or just a concrete client?
