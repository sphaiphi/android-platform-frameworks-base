# LightsRequest - Reverse Engineering Documentation

## Executive Summary
`LightsRequest` encapsulates a batch request to modify the state of one or more lights. It is constructed via a Builder pattern and holds a map of `Light` to `LightState`.

## Architecture Overview
- **Pattern**: Builder Pattern / Command Object.
- **Role**: Payload for `LightsSession.requestLights()`.
- **Components**:
  - `Builder`: Helper for accumulating changes.

## Detailed Functionality
- **Internal Storage**: `Map<Light, LightState> mRequests`.
- **Derived Storage**: `List<Integer> mLightIds` and `List<LightState> mLightStates` are populated in the constructor for easy IPC transmission (parallel arrays).

## Data Model
- `mRequests`: `Map<Light, LightState>`
- `mLightIds`: `List<Integer>` (extracted IDs)
- `mLightStates`: `List<LightState>` (corresponding states)

## API Reference
- `getLights()`: Returns list of IDs.
- `getLightStates()`: Returns list of states.
- `getLightsAndStates()`: Returns the map.

## Java-to-C++ Translation Guide

### Data Structure
```cpp
struct LightsRequest {
    std::vector<int32_t> lightIds;
    std::vector<LightState> lightStates;
};
```
*Note: C++ APIs usually prefer parallel vectors or a vector of pairs for batch operations over Binder.*

### Builder
Implement a fluent builder in C++ if ergonomic construction is required, otherwise simple struct initialization suffices.

### Optimization
Java uses `HashMap` then flattens to `ArrayList`s in the constructor. C++ can build the vectors directly to avoid allocation overhead.

## Questions for C++ Team
- None. Straightforward DTO.
