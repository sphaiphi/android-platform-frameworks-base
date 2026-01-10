# Credential Responses - Reverse Engineering Documentation

## Executive Summary
This document covers the response classes for the Credential Manager API: `GetCredentialResponse` and `CreateCredentialResponse`. They are simple wrappers around the result data.

## 1. GetCredentialResponse

### Functionality
- **Purpose**: Returns the successfully retrieved credential.
- **Data**: Contains a single `Credential` object.
- **Helper**: `getAutofillId()` extracts the `AutofillId` from the credential data if present (helper for Autofill integration).

### Data Model
```cpp
struct GetCredentialResponse {
    Credential credential;
};
```

## 2. CreateCredentialResponse

### Functionality
- **Purpose**: Returns the result of a creation operation.
- **Data**: Contains a `Bundle` (`mData`). The content of this bundle is provider-specific/type-specific.

### Data Model
```cpp
struct CreateCredentialResponse {
    android::os::Bundle data;
};
```

## Java-to-C++ Translation Guide
- **Simple Wrappers**: These classes are thin wrappers. In C++, you might return the inner object directly or keep the wrapper for future extensibility.
- **Parcelable**: Both must be Parcelable.
