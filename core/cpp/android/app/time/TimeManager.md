# TimeManager - Reverse Engineering Documentation

## Executive Summary
The primary system service API surface for Time and Time Zone management. It provides access to configuration, capabilities, and manual suggestion injection. It acts as a client-side wrapper around `ITimeDetectorService` and `ITimeZoneDetectorService`.

## Architecture Overview
*   **Type**: `public final class` (System Service Manager).
*   **Pattern**: Proxy/Facade.
*   **IPC**: Communicates via AIDL interfaces (`ITimeDetectorService`, `ITimeZoneDetectorService`).
*   **Concurrency**: Uses a registered Listener pattern for updates.

## Detailed Functionality
*   **Configuration**:
    *   `getTimeCapabilitiesAndConfig()` / `getTimeZoneCapabilitiesAndConfig()`: Fetch state.
    *   `updateTimeConfiguration()` / `updateTimeZoneConfiguration()`: Push updates.
*   **Suggestions**:
    *   `suggestExternalTime()`: Inject time from external sources.
    *   `setManualTime()` / `setManualTimeZone()`: User manual overrides.
    *   `confirmTime()` / `confirmTimeZone()`: Validate current state during setup.
*   **Listeners**:
    *   Manages `TimeZoneDetectorListener`.
    *   Wraps the AIDL callback (`ITimeZoneDetectorListener.Stub`) and dispatches to a user-provided `Executor`.
    *   Reference counts listeners to register/unregister with the service only when needed.

## Data Model
*   `ArrayMap<Listener, Wrapper>`: Maps client listeners to internal executor wrappers.
*   `ITimeZoneDetectorListener mTimeZoneDetectorReceiver`: The single binder stub passed to the server.

## API Reference
*   See `TimeManager.java` for full list. Key methods involve permission checks (`MANAGE_TIME_AND_ZONE_DETECTION`, `SUGGEST_EXTERNAL_TIME`).

## Java-to-C++ Translation Guide
*   **Service Access**: Use `android::os::ServiceManager::getService("time_detector")`.
*   **Binder**: Implement Bp/Bn proxy/stubs for the AIDL interfaces.
*   **Listeners**:
    *   Implement `ITimeZoneDetectorListener` as a `class : public BnTimeZoneDetectorListener`.
    *   Use `std::mutex` for thread safety of the listener map.

## Test Cases & Validation
*   Register listener -> Verify `addListener` called on service.
*   Unregister last listener -> Verify `removeListener` called.
*   Permissions are checked on the server side, but client should handle `SecurityException` (or C++ equivalent `Status`).

## Implementation Risks
*   Managing the listener lifecycle and death recipients in C++ to avoid leaks.
