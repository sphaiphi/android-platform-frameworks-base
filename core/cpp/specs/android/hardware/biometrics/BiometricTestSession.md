# BiometricTestSession - Reverse Engineering Documentation

## Executive Summary
`BiometricTestSession` provides a testing interface for biometric APIs. It allows tests to inject mock signals (enrollment, authentication success/failure, errors) into the biometric system, bypassing real hardware.

## Architecture Overview
This class interacts with `IAuthService` to create an `ITestSession`. It manages test sessions for multiple sensors if necessary. It uses a "Test HAL" mode in the system service.

## Detailed Functionality

### Setup
- **Constructor**: Takes a `TestSessionProvider` (usually a lambda wrapping `IAuthService.createTestSession`).
- **Test HAL**: Calls `setTestHalEnabled(true)` to switch the system service to use a mock HAL.

### Operations
- `startEnroll(int userId)`: Simulates start of enrollment.
- `finishEnroll(int userId)`: Simulates completion.
- `acceptAuthentication(int userId)`: Simulates success (no HAT).
- `rejectAuthentication(int userId)`: Simulates rejection.
- `notifyAcquired(userId, acquireInfo)`: Injects acquired message.
- `notifyError(userId, errorCode)`: Injects error.
- `cleanupInternalState(userId)`: Synchronizes framework state with HAL state.

### Lifecycle
- Implements `AutoCloseable`. `close()` cleans up tested users and disables the test HAL.

## Java-to-C++ Translation Guide
- **Test Infrastructure**: This is primarily a client-side test utility. In C++, similar functionality would typically be achieved by calling the `ITestSession` AIDL interface directly.

## Implementation Risks
- Leaving the device in "Test HAL" mode if the test crashes before `close()` is called.
