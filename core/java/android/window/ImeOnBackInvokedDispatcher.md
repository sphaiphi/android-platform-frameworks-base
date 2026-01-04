# ImeOnBackInvokedDispatcher - Reverse Engineering Documentation

## Executive Summary
`ImeOnBackInvokedDispatcher` is a specialized implementation of `OnBackInvokedDispatcher` designed for the IME (Input Method Editor). It handles the IPC complexity of registering back callbacks from the IME process (which has its own window) to the App process (which controls the back gesture dispatching).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` implements `OnBackInvokedDispatcher`, `Parcelable`
*   **Role**: IPC Bridge for Back Callbacks.
*   **Mechanism**:
    *   Created in App process.
    *   Parceled to IME process.
    *   IME registers callbacks on this dispatcher.
    *   Dispatcher uses `ResultReceiver` to send registration request back to App process.
    *   App process registers a wrapper callback (`ImeOnBackInvokedCallbackWrapper`) on the actual window dispatcher.

## Detailed Functionality

### Constructor & Receiver
*   Constructor takes a `Handler`. Creates a `ResultReceiver`.
*   `onReceiveResult`: Handles `RESULT_CODE_REGISTER` and `RESULT_CODE_UNREGISTER`.
*   **Queueing**: If `getReceivingDispatcher()` returns null (not attached yet), it queues the messages in `mQueuedReceive`.

### Registration Flow
1.  **IME Call**: `registerOnBackInvokedCallback`
2.  **Action**: Creates a Bundle with `Binder` (callback wrapper), Priority, ID.
3.  **IPC**: `mResultReceiver.send(RESULT_CODE_REGISTER, bundle)`.
4.  **App Side**: `receive()` -> extracts callback -> `registerReceivedCallback`.
5.  **Wrapper**: Wraps the AIDL callback into `ImeOnBackInvokedCallback` (local object) and registers with `WindowOnBackInvokedDispatcher`.

### Classes
*   `ImeOnBackInvokedCallback`: Wraps the remote `IOnBackInvokedCallback` to call it.
*   `DefaultImeOnBackAnimationCallback`: Subclass for system priority.
*   `ImeOnBackInvokedCallbackWrapper`: The App-side stub that receives calls from WindowManager and forwards them via the Handler to the IME callback (local).

## Java-to-C++ Translation Guide

### IPC Mechanism
*   The Java code uses `ResultReceiver`. C++ might need to use a generic `IResultReceiver` AIDL interface or a custom AIDL definition for this dispatching channel if `ResultReceiver` isn't readily available or idiomatic.
*   **Bundle**: Heavily used to pack binder tokens and ints. C++ `Bundle` (PersistableBundle) equivalents exist in Binder.

### Strong/Weak References
*   Comments mention using strong references to avoid GC. C++ `sp<>` handles this.

## Implementation Risks
*   **Cross-Process Callback Loop**: The callback goes WindowManager -> App -> IME. Ensure no deadlocks or lifetime issues where the App process dies and leaves the IME holding a dead dispatcher.
*   **Handler/Threading**: The dispatcher relies on a `Handler` to run callbacks on the correct thread. C++ needs a `Looper` or message queue integration.
