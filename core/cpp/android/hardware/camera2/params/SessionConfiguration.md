# SessionConfiguration - Reverse Engineering Documentation

## Executive Summary
`SessionConfiguration` is a container class that aggregates all parameters required to initialize a `CameraCaptureSession`. It replaces the older, multi-argument session creation methods with a single, extensible configuration object. It supports regular, high-speed, and shared session types.

## Architecture Overview
- **Aggregation**: Combines output configurations, input configurations (for reprocessing), state callbacks, and session-wide parameters.
- **Type-Safety**: Enforces session modes (Regular vs. High Speed).
- **Extensibility**: Includes `sessionParameters` (`CaptureRequest`) which allow the HAL to optimize itself based on expected future requests.

## Detailed Functionality

### Session Modes
**Purpose**: To optimize camera hardware for specific workflows.
- **SESSION_REGULAR**: Normal operation (Preview, Video, Burst).
- **SESSION_HIGH_SPEED**: Optimized for high-frame-rate capture (e.g., 120/240 fps). Restricted to specific resolutions and restricted output counts.

### Session Parameters
**Purpose**: To provide "hints" to the camera HAL during initialization.
**Algorithm**:
1. Application builds a `CaptureRequest` containing session-wide settings (e.g., stabilization mode, zoom).
2. Sets this request via `setSessionParameters()`.
3. The HAL uses these to pre-configure internal buffers and tuning state, reducing latency when the actual capture starts.

## Data Model

### Members
- `mSessionType` (`int`): Regular or High Speed.
- `mOutputConfigurations` (`List<OutputConfiguration>`): List of destinations.
- `mInputConfig` (`InputConfiguration`): Configuration for reprocessing (optional).
- `mStateCallback` (`CameraCaptureSession.StateCallback`): Listener for session events.
- `mExecutor` (`Executor`): Threading context for the callback.
- `mSessionParameters` (`CaptureRequest`): Optimization hints.

## API Reference

### Public Methods
- `int getSessionType()`: Get mode.
- `List<OutputConfiguration> getOutputConfigurations()`: Get targets.
- `void setSessionParameters(CaptureRequest params)`: Set optimization hints.
- `void setInputConfiguration(InputConfiguration input)`: Enable reprocessing.
- `void setStateCallback(Executor executor, StateCallback cb)`: Configure event handling.

## Java-to-C++ Translation Guide

### Callback Execution
- **Java**: Uses `Executor`.
- **C++**: Use a callback dispatcher that can post events to a `Looper` or a thread pool.

### Reprocessing Support
- **Java**: `InputConfiguration` specifies the width, height, and format of the buffers the application will feed *back* into the camera.
- **C++**: Map this to a native input stream configuration.

### Synchronization
- **Java**: Immutable list of outputs.
- **C++**: Ensure the `std::vector` of configurations is copied or shared via `std::shared_ptr` to avoid race conditions during session startup.

## Test Cases & Validation
1. **Regular Session**: Verify that a session with multiple YUV and JPEG outputs can be initialized.
2. **High Speed Constraints**: Verify that creating a `SESSION_HIGH_SPEED` with more than 2 outputs (or unsupported sizes) fails as per API rules.
3. **Parameter Application**: Verify that keys set in `sessionParameters` are reflected in the first `CaptureResult` received from the session.

## Implementation Risks
- **IPC Payload**: `SessionConfiguration` can become large if it contains many `OutputConfiguration` objects and complex session parameters. The C++ implementation must handle Binder transaction limits.
- **HAL Compatibility**: Not all HAL versions support all session types or session parameters. The implementation must query `CameraCharacteristics` to validate the configuration before sending it to the service.
