# ConfirmationPrompt - Reverse Engineering Documentation

## Executive Summary
The `ConfirmationPrompt` class provides an interface for displaying a system-provided confirmation prompt to the user. This is part of the "Android Protected Confirmation" feature, which ensures that a user has seen and approved a specific message, even if the Android framework or kernel is compromised. It relies on dedicated hardware support.

## Architecture Overview
*   **Package**: `android.security`
*   **Type**: Class (Public)
*   **Dependencies**:
    *   `android.security.ConfirmationCallback`
    *   `android.security.AndroidProtectedConfirmation` (Internal helper)
    *   `android.security.IConfirmationCallback` (AIDL)
    *   `android.content.Context`
*   **Key Components**:
    *   `Builder`: Helper class to construct a `ConfirmationPrompt`.
    *   `AndroidProtectedConfirmation`: Accessor to the underlying system service (likely interacting with Keystore/Trusted UI).

## Detailed Functionality

### 1. Prompt Presentation
*   **Method**: `presentPrompt(Executor executor, ConfirmationCallback callback)`
*   **Purpose**: Initiates the display of the confirmation prompt.
*   **Mechanism**:
    *   Checks if a callback is already pending (`ConfirmationAlreadyPresentingException`).
    *   Checks if Accessibility Services are running (incompatible with Protected Confirmation due to screen reading/control risks). Returns `ConfirmationNotAvailableException` if so.
    *   Obtains `AndroidProtectedConfirmation` service.
    *   Calls `presentConfirmationPrompt` on the service with:
        *   Prompt text.
        *   Extra data (cryptographic nonce).
        *   Locale.
        *   UI options (flags for inverted color or magnified font based on system settings).
*   **Result**: Asynchronous. Success/Failure is delivered via `ConfirmationCallback`.

### 2. Prompt Cancellation
*   **Method**: `cancelPrompt()`
*   **Purpose**: Dismisses the currently active prompt.
*   **Mechanism**: Calls `cancelConfirmationPrompt` on the internal service.

### 3. Support Check
*   **Method**: `isSupported(Context context)`
*   **Purpose**: Static check for feature availability.
*   **Logic**: Returns `false` if Accessibility Services are running, otherwise queries the underlying service.

### 4. Builder Pattern
*   **Class**: `ConfirmationPrompt.Builder`
*   **Purpose**: Fluent API to creating instances.
*   **Validation**: Ensures `promptText` is not empty and `extraData` is not null.

## Data Model

### Fields
*   `mPromptText`: `CharSequence` - The text to be confirmed by the user.
*   `mExtraData`: `byte[]` - Cryptographic challenge/nonce to be signed.
*   `mCallback`: `ConfirmationCallback` - User-provided callback.
*   `mExecutor`: `Executor` - Thread to run the callback on.
*   `mProtectedConfirmation`: `AndroidProtectedConfirmation` - Service wrapper.

## API Reference

### Public Methods
*   `void presentPrompt(@NonNull Executor executor, @NonNull ConfirmationCallback callback)`: Shows the prompt.
*   `void cancelPrompt()`: Hides the prompt.
*   `static boolean isSupported(Context context)`: Checks hardware/software support.

### Builder Methods
*   `setPromptText(CharSequence promptText)`
*   `setExtraData(byte[] extraData)`
*   `build()`

## Java-to-C++ Translation Guide

### Dependencies
*   C++ equivalent will need to interact with the Keystore / ConfirmationUI HAL (Hardware Abstraction Layer).
*   Corresponding AIDL interfaces (`IConfirmationUI` or similar) will be needed.

### Threading
*   Java uses `Executor` for callbacks. C++ implementation should use a callback mechanism compatible with the thread loop (e.g., `std::function`, `ndk::ScopedAStatus`, or a custom looper).

### Memory Management
*   `mExtraData` is a `byte[]`. In C++, use `std::vector<uint8_t>`.
*   `mPromptText` is `CharSequence`. In C++, use `std::string`.

## Implementation Risks
*   **Accessibility Compatibility**: The logic explicitly blocks functionality if Accessibility services are enabled. This constraint must be preserved in C++ to maintain security guarantees (preventing overlays/readers from mimicking user interaction).
*   **Concurrency**: Handling multiple `presentPrompt` calls needs careful state management (`ConfirmationAlreadyPresentingException`).
