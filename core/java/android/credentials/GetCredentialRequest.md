# GetCredentialRequest - Reverse Engineering Documentation

## Executive Summary
`GetCredentialRequest` encapsulates all information needed to retrieve a credential from the user. It holds a list of options (requests for different types of credentials) and global request data.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Input to `CredentialManager.getCredential`.

## Detailed Functionality

### Core Fields
- `mCredentialOptions` (`List<CredentialOption>`): The list of specific credential requests (e.g., "Password" and "Passkey").
- `mData` (Bundle): Top-level request data (global parameters).
- `mOrigin` (String): Origin of the calling app (used by browsers/middle-layers to assert identity).
- `mAlwaysSendAppInfoToProvider` (boolean): Privacy flag. If false, calling app info is hidden during the query phase.

### Methods
- Getters for all fields.
- Builder pattern for construction.

## Java-Specific Notes
- **Origin**: String field, crucial for WebAuthn/FIDO contexts.
- **Privacy Flag**: `alwaysSendAppInfoToProvider` defaults to `true` in the Builder.

## Java-to-C++ Translation Guide
- **List**: `std::vector<CredentialOption>`.
- **Bundle**: `android::os::Bundle`.
- **Origin**: `std::optional<std::string>`.

## Data Model
```cpp
struct GetCredentialRequest {
    std::vector<CredentialOption> credentialOptions;
    android::os::Bundle data;
    std::optional<std::string> origin;
    bool alwaysSendAppInfoToProvider;
};
```
