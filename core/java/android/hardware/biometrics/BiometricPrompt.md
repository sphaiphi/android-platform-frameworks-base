# BiometricPrompt - Reverse Engineering Documentation

## Executive Summary
`BiometricPrompt` is the standard API for prompting the user to authenticate using biometrics or device credentials. It manages the system-provided dialog, handles cryptographic object unlocking, and reports results back to the application.

## Architecture Overview
The class uses a **Builder** pattern for configuration. It acts as a client to `IAuthService` (and internally `BiometricService`), passing a `PromptInfo` parcelable to configure the system UI. It uses an internal `IBiometricServiceReceiver` to receive callbacks from the system service.

## Detailed Functionality

### Builder
Configures the prompt:
- **Title/Subtitle/Description**: Text to display.
- **Logo**: Custom icon (restricted/advanced permission).
- **Buttons**: Negative button (Cancel) or "Use Password" (implicit via allowed authenticators).
- **Authenticators**: Sets allowed types (`BIOMETRIC_STRONG`, `DEVICE_CREDENTIAL`, etc.).
- **ContentView**: Custom content views (vertical list, description with more options).

### Authentication
- `authenticate(CryptoObject, ...)`: Auth with a crypto object (Signature, Cipher, Mac, IdentityCredential, PresentationSession). Unlocks the object upon success.
- `authenticate(CancellationSignal, ...)`: Auth without crypto (just verification).

### CryptoObject
A wrapper class (`BiometricPrompt.CryptoObject`) that holds references to Java crypto primitives. It abstracts the underlying operation handle (`opId`) required by Keystore.

### Callbacks
- `AuthenticationCallback`:
    - `onAuthenticationSucceeded(AuthenticationResult)`
    - `onAuthenticationError`
    - `onAuthenticationFailed`

## Data Model
- **PromptInfo**: Internal parcelable holding all builder configuration.
- **AuthenticationResult**: Contains the `CryptoObject` and authentication type (Biometric vs Credential).

## Java-to-C++ Translation Guide
- **UI**: `BiometricPrompt` launches a system UI. The C++ implementation of the *client* would trigger this IPC. The UI itself is typically in SystemUI (Java).
- **Crypto**: `CryptoObject` management involves extracting the `opId` (operation handle) from the native SSL/Keystore handles.
- **Receiver**: Implement `IBiometricServiceReceiver` stub to handle callbacks from the service.

## Implementation Risks
- **Lifecycle**: Handling activity lifecycle events (pause/resume) to cancel authentication correctly.
- **Crypto Validity**: Ensuring the `CryptoObject` is valid and the `opId` matches the one expected by Keystore.
- **Permissions**: Advanced customization (Logo, content view) requires `SET_BIOMETRIC_DIALOG_ADVANCED`.
