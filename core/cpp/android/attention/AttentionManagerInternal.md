# AttentionManagerInternal - Reverse Engineering Documentation

## Executive Summary
`AttentionManagerInternal` is an abstract class defining the local system interface for the Attention Service. It allows system components to request attention checks (e.g., "is the user looking at the screen?") and proximity updates. This is typically used for features like "Screen Attention" (keeping screen on) or adaptive notification content.

## Functionality

### 1. Capabilities
- `isAttentionServiceSupported()`: Boolean check.
- `isProximitySupported()`: Boolean check.

### 2. Attention Checks
- `checkAttention(long timeoutMillis, AttentionCallbackInternal callback)`: Asynchronous request.
  - **Inputs**: Timeout budget.
  - **Callback**: `onSuccess(int result, long timestamp)` or `onFailure(int error)`.
- `cancelAttentionCheck(AttentionCallbackInternal callback)`: Cancels a pending request.

### 3. Proximity Updates
- `onStartProximityUpdates(ProximityUpdateCallbackInternal callback)`: Requests continuous distance updates.
  - **Callback**: `onProximityUpdate(double distance)`.
- `onStopProximityUpdates(ProximityUpdateCallbackInternal callback)`: Stops updates.

## Architecture
- **Service Pattern**: Local service interface (internal to system server).
- **Callbacks**: Uses abstract static inner classes/interfaces (`AttentionCallbackInternal`, `ProximityUpdateCallbackInternal`) for async results.

## Java-to-C++ Translation Guide
- **Interface**: Maps to a C++ abstract class with pure virtual methods.
- **Callbacks**: C++ can use `std::function` or listener interfaces.
- **Data Types**: `double` for distance, `long` for timestamps/timeouts.
