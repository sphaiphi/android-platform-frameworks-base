// File: android/accessibilityservice/IRemoteAccessibilityInputConnection.aidl
package android.accessibilityservice;

/**
 * The IPC interface an accessibility service uses to communicate back with
 * an input method.
 *
 * All methods are oneway to prevent deadlocks between the system and the service.
 * @hide
 */
oneway interface IRemoteAccessibilityInputConnection {
    // Methods for interacting with the editor would be defined here, for example:
    // void commitText(in CharSequence text, int newCursorPosition);
}