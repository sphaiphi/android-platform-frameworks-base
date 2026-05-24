
# InputMethod - Reverse Engineering Documentation

## Executive Summary
The `InputMethod` class is a base class that allows an `AccessibilityService` to act as a limited Input Method Editor (IME). By extending this class and setting the `AccessibilityServiceInfo.FLAG_INPUT_METHOD_EDITOR` flag, a service can gain access to the `InputConnection` of the currently focused text field. This enables the service to directly manipulate text (e.g., commit text, set selection), receive selection updates, and send key events, providing a powerful way to implement custom text entry and editing experiences.

## Architecture Overview
*   **Base Class for Extension**: `InputMethod` is designed to be subclassed. An accessibility service developer overrides its methods (like `onStartInput` and `onUpdateSelection`) to implement their custom logic. The service then returns an instance of their custom `InputMethod` subclass from an overridden `AccessibilityService.onCreateInputMethod()`.
*   **Session-Based**: The lifecycle is session-based. A session begins with `onStartInput` when a user focuses an editable field and ends with `onFinishInput` when focus is lost.
*   **Decoupling via `AccessibilityInputConnection`**: The class provides access to the editor's `InputConnection` through a wrapper, `InputMethod.AccessibilityInputConnection`. This wrapper exposes a safe, limited subset of the full `InputConnection` API, preventing the service from accessing more sensitive or dangerous operations.
*   **Internal IPC Handling**: The `InputMethod` class works in conjunction with internal framework classes (`SessionImpl`, `AccessibilityInputMethodSessionWrapper`) to handle the Binder IPC and threading between the system's input method manager and the service. The service developer who is using the `InputMethod` class is shielded from these complexities.

## Detailed Functionality

### Core Lifecycle Callbacks
These are the primary methods for a developer to override.
*   **`onStartInput(@NonNull EditorInfo attribute, boolean restarting)`**: Called when an editor becomes active. This is the entry point for an input session. The `EditorInfo` object provides details about the editor (e.g., its input type). `restarting` is true if the session is for the same editor but its state (like the text content) has been reset by the application.
*   **`onFinishInput()`**: Called when the editor is no longer active. This is the place to clean up any session-specific state.
*   **`onUpdateSelection(...)`**: Called whenever the cursor position or text selection changes in the active editor, giving the service real-time updates.

### `AccessibilityInputConnection` (Inner Class)
This is the main tool provided to the service for interacting with the editor. It is a wrapper around the remote `InputConnection` object.
*   **`commitText(...)`**: Inserts text into the editor.
*   **`setSelection(int start, int end)`**: Moves the cursor or changes the text selection.
*   **`deleteSurroundingText(int beforeLength, int afterLength)`**: Deletes text around the cursor.
*   **`getSurroundingText(...)`**: Retrieves the text currently in the editor around the cursor. This is an IPC call and can be slow.
*   **`sendKeyEvent(KeyEvent)`**: Injects a key event into the application, simulating a hardware key press.
*   **`performEditorAction(int)`**: Triggers an IME action like "Done", "Go", or "Search".
*   **`performContextMenuAction(int)`**: Triggers a standard text action like "Cut", "Copy", or "Paste".

### Internal Session Management (`SessionImpl` and `createImeSession`)
*   **`SessionImpl`**: A private inner class that implements the `AccessibilityInputMethodSession` AIDL contract. It acts as the direct receiver of IPC calls from the system.
*   **`createImeSession(...)`**: A package-private method called by the `AccessibilityService` framework to create a new session. It instantiates `SessionImpl`, wraps it in the `AccessibilityInputMethodSessionWrapper` (the Binder stub), and sends it back to the system.
*   **Thread Safety**: The `AccessibilityInputMethodSessionWrapper` ensures that all calls from the system (e.g., `updateSelection`, `finishInput`) are executed on the accessibility service's main thread, so the developer subclassing `InputMethod` doesn't need to worry about multithreading within the `on...` callbacks.

## Data Model
*   `mService`: A reference to the parent `AccessibilityService`.
*   `mInputStarted`: A `boolean` flag indicating if an input session is currently active.
*   `mStartedInputConnection`: The `RemoteAccessibilityInputConnection` object, which is the actual Binder proxy for the `InputConnection`. This is hidden inside the `AccessibilityInputConnection` wrapper.
*   `mInputEditorInfo`: The `EditorInfo` for the currently active editor.

## Java-to-C++ Translation Guide
*   **Base Class**: `InputMethod` would be an abstract base class in C++ with virtual methods for `onStartInput`, `onFinishInput`, and `onUpdateSelection`.
*   **`AccessibilityInputConnection`**: This wrapper class would also be translated to C++. Its methods would make IPC calls to the editor via a C++ Binder proxy object.
*   **`EditorInfo`**: A C++ class/struct equivalent to `EditorInfo` would be needed to pass editor state across IPC.
*   **IPC Infrastructure**: The entire `SessionImpl` and `AccessibilityInputMethodSessionWrapper` mechanism would need to be reimplemented in C++. This involves creating a C++ Binder service (`Bn` class) to receive calls from the system and a C++ Binder proxy (`Bp` class) to make calls to the editor's `InputConnection`.
*   **Threading**: The thread-switching logic provided by the `Handler` in `AccessibilityInputMethodSessionWrapper` is critical. The C++ Binder service implementation would need to post incoming calls as tasks to the service's main event loop before invoking the C++ `InputMethod`'s virtual methods.

## Implementation Risks
*   **IPC Complexity**: Replicating the three-way IPC communication (System -> Service, Service -> Editor) is complex. The C++ implementation must correctly manage the lifecycle of multiple Binder objects.
*   **Race Conditions**: State management (e.g., `mInputStarted`, the active `InputConnection`) must be thread-safe, as calls from the system can arrive at any time. The Java implementation relies on the main thread `Handler` for this safety; a C++ version must replicate it carefully.
*   **API Surface**: The `InputConnection` API is large. The `AccessibilityInputConnection` wrapper exposes only a subset. The C++ version must correctly implement this subset and ensure the method signatures and behaviors match. For example, `getSurroundingText` is a synchronous IPC call that can be slow or fail, and the C++ implementation must handle this gracefully.

## Questions for C++ Team
*   What is the C++ equivalent for `EditorInfo` that will be passed to `onStartInput`?
*   How will the `InputConnection` be exposed to the C++ service? Will it also be a limited-API wrapper class?
*   What is the expected threading model for the C++ `InputMethod` callbacks? Will they be guaranteed to run on a specific thread?
