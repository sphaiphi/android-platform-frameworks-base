# ConsumerIrManager - Reverse Engineering Documentation

## Executive Summary
`ConsumerIrManager` provides an interface for applications to interact with the device's infrared (IR) emitter. It allows querying for the presence of an IR emitter, retrieving supported carrier frequencies, and transmitting IR patterns.

## Architecture Overview
The class is a `SystemService` associated with `Context.CONSUMER_IR_SERVICE`. It acts as a proxy to `IConsumerIrService`, which runs in the system server. It follows the standard Android manager pattern, where the manager handles IPC and permission enforcement is done at the service level.

## Detailed Functionality

### `hasIrEmitter()`
**Purpose**: Checks if the hardware contains an IR transmitter.
**Algorithm**: Calls `mService.hasIrEmitter()`. Returns false if the service is missing.

### `transmit(int carrierFrequency, int[] pattern)`
**Purpose**: Transmits an alternating on/off pattern at a specific frequency.
**Algorithm**:
1. Validates the pattern length (typically must be < 2 seconds).
2. Forwards the request to the system service: `mService.transmit(mPackageName, carrierFrequency, pattern)`.
**Java-Specific Notes**: Pattern is an array of microseconds. Synchronous call.

### `getCarrierFrequencies()`
**Purpose**: Returns the ranges of frequencies supported by the emitter.
**Algorithm**:
1. Calls `mService.getCarrierFrequencies()`, which returns a flat `int[]`.
2. Parses the flat array into an array of `CarrierFrequencyRange` objects (pairs of min/max).

## Data Model
- **CarrierFrequencyRange**:
    - `mMinFrequency` (int)
    - `mMaxFrequency` (int)

## API Reference
- `public boolean hasIrEmitter()`
- `public void transmit(int carrierFrequency, int[] pattern)`
- `public CarrierFrequencyRange[] getCarrierFrequencies()`

## Java-to-C++ Translation Guide
- **Manager**: `class ConsumerIrManager` -> `class ConsumerIrManager`.
- **Service Interface**: `IConsumerIrService` -> AIDL generated C++ client.
- **Patterns**: `int[]` -> `std::vector<int32_t>`.
- **Error Handling**: Java rethrows `RemoteException` via `rethrowFromSystemServer()`. C++ should use `binder::Status` or `std::expected`.

## Test Cases & Validation
- Verify `hasIrEmitter` accurately reflects hardware capability.
- Test `transmit` with various frequencies (e.g., 38kHz for standard TV remotes).
- Ensure `getCarrierFrequencies` returns at least one valid range if hardware is present.

## Implementation Risks
- Strict timing requirements for IR patterns might be affected by system load if not handled carefully in the HAL.
- Permission `TRANSMIT_IR` must be enforced.
