
# AccessibilityInputMethodSession - Reverse Engineering Documentation

## Executive Summary
`AccessibilityInputMethodSession` is a Java interface that defines the contract for a session between the system and an accessibility service's input method. It outlines the methods that an accessibility service's input method must implement to handle events like finishing input, updating text selection, and receiving new input connections.

## Architecture Overview
This is a pure interface, meaning it only declares methods without providing any implementation. It serves as a contract that other classes must implement. In the Android framework, it is implemented by `InputMethod.SessionImpl` and is wrapped by `AccessibilityInputMethodSessionWrapper` (which is a Binder stub) to facilitate communication from the system (which holds a remote reference) to the accessibility service. This architecture decouples the system's input method management from the accessibility service's implementation.

## Detailed Functionality

This interface defines the essential callbacks that an input method session within an accessibility service must handle.

### `finishInput()`
*   **Purpose**: Called by the system to inform the session that text input has finished in the current editor.
*   **C++ Implementation Guidance**: This would be a virtual method in a C++ abstract base class. The implementation should clean up any state related to the current input session.

### `updateSelection(...)`
*   **Purpose**: Called by the system to notify the session about changes in the text selection or cursor position.
*   **Parameters**: `oldSelStart`, `oldSelEnd`, `newSelStart`, `newSelEnd`, `candidatesStart`, `candidatesEnd`.
*   **C++ Implementation Guidance**: A virtual method that receives integer coordinates for the old and new selection ranges. The implementation would use this to update its internal state or UI.

### `invalidateInput(...)`
*   **Purpose**: Called when the state of the input editor has been invalidated and needs to be reread. This often happens when the text content changes unexpectedly.
*   **Parameters**:
    *   `editorInfo`: Contains the full state of the text editor.
    *   `connection`: A remote IPC connection object to the editor.
    *   `sessionId`: The ID for the new session.
*   **Java-Specific Notes**: `EditorInfo` is a `Parcelable` class containing rich editor state. `IRemoteAccessibilityInputConnection` is a Binder interface for IPC.
*   **C++ Implementation Guidance**: This would be a virtual method taking a C++ equivalent of `EditorInfo` and a C++ IPC proxy object for the input connection. The implementation should reset its state and re-initialize with the new information.

### `setEnabled(boolean enabled)`
*   **Purpose**: Allows the system to enable or disable the session. When disabled, the session should ignore incoming calls.
*   **C++ Implementation Guidance**: A virtual method that sets an internal boolean flag. Implementations of other methods should check this flag before proceeding.

## Data Model
This is an interface and thus has no data members. The implementing class will manage the state, which typically includes:
*   A reference to the current input connection.
*   The current `EditorInfo`.
*   A boolean flag for its enabled state.

## API Reference
*   `void finishInput()`
*   `void updateSelection(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd, int candidatesStart, int candidatesEnd)`
*   `void invalidateInput(EditorInfo editorInfo, IRemoteAccessibilityInputConnection connection, int sessionId)`
*   `void setEnabled(boolean enabled)`

## Java-to-C++ Translation Guide
*   **Interface**: In C++, this would be defined as an abstract base class (a class with only pure virtual functions).
    ```cpp
    class AccessibilityInputMethodSession {
    public:
        virtual ~AccessibilityInputMethodSession() = default;
        virtual void finishInput() = 0;
        virtual void updateSelection(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd, int candidatesStart, int candidatesEnd) = 0;
        virtual void invalidateInput(const EditorInfo& editorInfo, const std::shared_ptr<IRemoteAccessibilityInputConnection>& connection, int sessionId) = 0;
        virtual void setEnabled(bool enabled) = 0;
    };
    ```
*   **`EditorInfo`**: A corresponding C++ struct or class needs to be defined to carry the editor's attributes. This class must also be serializable if it needs to cross IPC boundaries.
*   **`IRemoteAccessibilityInputConnection`**: This is a Binder interface. The C++ implementation will require a corresponding IPC proxy class to communicate back to the text editor.

## Implementation Risks
*   **Contract Adherence**: The C++ class that implements this interface must strictly adhere to the expected behavior for each method, as the system will rely on this contract.
*   **IPC Complexity**: The `invalidateInput` method involves receiving an IPC object (`IRemoteAccessibilityInputConnection`). The C++ implementation must correctly handle the lifecycle and usage of this remote object.

## Questions for C++ Team
*   What is the intended C++ equivalent for `EditorInfo`?
*   What is the IPC mechanism that will be used for the `IRemoteAccessibilityInputConnection` in the C++ environment?
