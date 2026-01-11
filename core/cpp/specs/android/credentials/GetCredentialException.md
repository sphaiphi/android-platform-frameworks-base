# Credential Exceptions - Reverse Engineering Documentation

## Executive Summary
This document covers the exception classes used by `CredentialManager` to report errors. They all extend standard Java `Exception` and provide specific error types and messages.

## Common Structure
All exception classes share a similar pattern:
- **`mType` (String)**: A specific error string constant (e.g., `TYPE_USER_CANCELED`).
- **`message` (String)**: Human-readable debug message.
- **Constructors**: (Type, Message), (Type, Cause), etc.

## 1. GetCredentialException
**Used in**: `getCredential`, `prepareGetCredential`.
**Key Types**:
- `TYPE_UNKNOWN`
- `TYPE_NO_CREDENTIAL`: No credentials found/selected.
- `TYPE_USER_CANCELED`: User dismissed the UI.
- `TYPE_INTERRUPTED`: System interruption.

## 2. CreateCredentialException
**Used in**: `createCredential`.
**Key Types**:
- `TYPE_UNKNOWN`
- `TYPE_NO_CREATE_OPTIONS`: No provider accepted the creation request.
- `TYPE_USER_CANCELED`
- `TYPE_INTERRUPTED`

## 3. ClearCredentialStateException
**Used in**: `clearCredentialState`.
**Key Types**:
- `TYPE_UNKNOWN`

## 4. GetCandidateCredentialsException
**Used in**: `getCandidateCredentials` (Hidden API).
**Key Types**:
- `TYPE_NO_CREDENTIAL`
- `TYPE_UNKNOWN`

## 5. SetEnabledProvidersException
**Used in**: `setEnabledProviders`.
**Key Types**: None specific defined as constants, general string types used.

## Java-to-C++ Translation Guide
- **Error Types**: Map the string constants to a C++ `enum class` or `std::string` constants.
- **Result Type**: Use `std::expected<T, ErrorType>` where `ErrorType` contains the type string and message.

## Data Model Example
```cpp
struct CredentialError {
    std::string type;
    std::string message;
};
// Usage: std::expected<Credential, CredentialError>
```
