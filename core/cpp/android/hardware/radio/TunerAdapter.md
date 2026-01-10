# TunerAdapter - Reverse Engineering Documentation

## Executive Summary
`TunerAdapter` is the concrete implementation of `RadioTuner`. It acts as a wrapper around the `ITuner` AIDL interface, translating Java API calls into Binder calls to the `RadioService`. It also manages backward compatibility for program lists.

## Architecture Overview
-   **Type**: Final Package-Private Class.
-   **Package**: `android.hardware.radio`.
-   **Role**: Bridge between client API (`RadioTuner`) and system service (`ITuner`).

## Detailed Functionality

### Components
-   `mTuner`: The `ITuner` binder proxy.
-   `mCallback`: `TunerCallbackAdapter` handling callbacks from service.
-   `mLegacyListProxy`: A `ProgramList` instance used for legacy `getProgramList` calls.
-   `mBand`: Current band (cached for `tune` legacy overload).

### Logic Flow
-   **Method Delegation**: Most methods (`setMute`, `step`, `seek`, `tune`) directly call `mTuner` methods, catching `RemoteException` and returning `STATUS_DEAD_OBJECT` or runtime exceptions.
-   **Program List Management**:
    -   `getDynamicProgramList`: Creates a new `ProgramList`, sets an observer on `mCallback` to feed updates to it, and calls `mTuner.startProgramListUpdates`.
    -   `getProgramList` (Legacy): Manages a singleton `mLegacyListProxy`, updates filter if changed, and waits for a complete list from `mCallback`. This bridges the new async "dynamic list" model to the old sync "get list" model.
-   **Metadata Images**: `getMetadataImage` calls `mTuner.getImage`.

## Java-to-C++ Translation Guide
-   **Proxy Pattern**: This class is a classic Proxy. In C++, this would wrap the `BpRadioService` (or equivalent AIDL client).
-   **Synchronization**: Replicate `mLock` usage for `mLegacyListProxy` management.
-   **Exception Handling**: Convert `RemoteException` to appropriate C++ error codes or exceptions.

---
