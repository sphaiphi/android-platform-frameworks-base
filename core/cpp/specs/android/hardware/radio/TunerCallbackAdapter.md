# TunerCallbackAdapter - Reverse Engineering Documentation

## Executive Summary
`TunerCallbackAdapter` implements the `ITunerCallback` AIDL stub. It receives callbacks from the system service (on binder threads) and dispatches them to the client's `RadioTuner.Callback` (on the client's `Handler` thread).

## Architecture Overview
-   **Type**: Final Package-Private Class.
-   **Extends**: `ITunerCallback.Stub` (Binder implementation).
-   **Package**: `android.hardware.radio`.
-   **Role**: Callback dispatcher and adapter.

## Detailed Functionality

### Core Logic
-   **Thread Dispatch**: Uses `Handler.post(() -> ...)` to switch from Binder thread to Client thread.
-   **State Caching**:
    -   `mCurrentProgramInfo`: Caches the latest info.
    -   `mIsAntennaConnected`: Caches antenna state.
    -   `mLastCompleteList`: Caches the last full program list (for legacy support).
-   **Program List Integration**:
    -   `mProgramList`: Reference to the active `ProgramList` object.
    -   `onProgramListUpdated(Chunk)`: Forwards the chunk to `mProgramList.apply()`.
    -   `onBackgroundScanComplete()`: Handles delayed callbacks if the list isn't ready.

### Error Mapping
-   `onTuneFailed(status, selector)`: Maps various AIDL status codes (e.g., `TUNER_RESULT_CANCELED`) to legacy `onError` codes (e.g., `ERROR_CANCELLED`) for backward compatibility, invoking both `onTuneFailed` and `onError`.

## Java-to-C++ Translation Guide
-   **Callback Stub**: Implement `BnTunerCallback` (native binder stub).
-   **Threading**: Use a `Looper` or `MessageQueue` equivalent to dispatch callbacks to the main thread (if required by C++ client contract).
-   **Weak References**: Consider if `mProgramList` needs weak reference semantics to avoid cycles (though Java uses `OnCloseListener` pattern here).

---
