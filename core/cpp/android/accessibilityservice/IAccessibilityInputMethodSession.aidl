// File: android/accessibilityservice/IAccessibilityInputMethodSession.aidl
package android.accessibilityservice;

import android.view.inputmethod.EditorInfo;
import android.accessibilityservice.IRemoteAccessibilityInputConnection;

/**
 * The IPC interface for an accessibility service's input method session.
 * This is a one-way interface from the system to the service.
 *
 * @hide
 */
oneway interface IAccessibilityInputMethodSession {
    /**
     * Called by the system when the input session is finished.
     */
    void finishInput();

    /**
     * Called by the system to notify of a change in text selection or cursor position.
     */
    void updateSelection(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd,
            int candidatesStart, int candidatesEnd);

    /**
     * Called by the system when the editor's state has become invalid. The service
     * must re-evaluate the editor state using the provided info and connection.
     * @param editorInfo The updated information about the text editor.
     * @param connection The new remote connection to the text editor.
     * @param sessionId A unique identifier for the new session.
     */
    void invalidateInput(in EditorInfo editorInfo,
            IRemoteAccessibilityInputConnection connection,
            int sessionId);
}