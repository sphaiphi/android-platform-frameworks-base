# AppFunctionException - Reverse Engineering Documentation

## Executive Summary
`AppFunctionException` represents an exception related to app functions in the Android App Function framework. It extends `Exception` and implements `Parcelable`, making it suitable for cross-process communication (IPC) via Binder. It provides categorized error codes and optional metadata (extras).

## Architecture Overview
- **Inheritance**: `Exception` (Java) -> `AppFunctionException`
- **Interfaces**: `Parcelable` (Android)
- **Role**: Standard exception class for the App Function ecosystem, used to report errors from the App Function Service to clients or the system server.

## Detailed Functionality

### Error Categorization
Errors are grouped into categories to help callers handle them appropriately:
-   **Request Errors (1000-1999)**: Issues with the caller's request (e.g., permission denied, invalid arguments).
-   **System Errors (2000-2999)**: Internal system failures or policy restrictions.
-   **App Errors (3000-3999)**: Failures within the target application (e.g., crashes, unknown errors).

### Error Codes
Defined as integer constants:
-   `ERROR_DENIED` (1000)
-   `ERROR_INVALID_ARGUMENT` (1001)
-   `ERROR_DISABLED` (1002)
-   `ERROR_FUNCTION_NOT_FOUND` (1003)
-   `ERROR_SYSTEM_ERROR` (2000)
-   `ERROR_CANCELLED` (2001)
-   `ERROR_ENTERPRISE_POLICY_DISALLOWED` (2002)
-   `ERROR_APP_UNKNOWN_ERROR` (3000)

### Metadata
-   **Extras**: A `Bundle` containing additional error-specific data.

## Data Model

| Field Name | Type | Description |
| :--- | :--- | :--- |
| `mErrorCode` | `int` | The specific error code. |
| `mErrorMessage` | `String` (Nullable) | Human-readable error description. |
| `mExtras` | `Bundle` | Key-value pairs for additional context. |

## API Reference

### Constructors
-   `AppFunctionException(int errorCode, String errorMessage)`
-   `AppFunctionException(int errorCode, String errorMessage, Bundle extras)`

### Methods
-   `int getErrorCode()`: Returns the error code.
-   `String getErrorMessage()`: Returns the error message.
-   `int getErrorCategory()`: logic mapping error code ranges to `ERROR_CATEGORY_*` constants.
-   `Bundle getExtras()`: Returns the extras bundle.

### Parcelable Implementation
-   `writeToParcel`: Serializes code, message, and bundle.
-   `createFromParcel`: Deserializes fields.

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `Exception` | `std::exception` / Custom Error Class | C++ exceptions usually don't support Parceling directly. |
| `Parcelable` | `android::os::Parcelable` | Implement `writeToParcel` and `readFromParcel`. |
| `Bundle` | `android::os::Bundle` | Use Android Binder Bundle implementation. |
| `IntDef` | `enum class` | Use strong enums for error codes. |

## Test Cases & Validation
1.  **Serialization**: Create exception with code, message, extras -> Parcel -> Unparcel -> Verify equality.
2.  **Categorization**: Verify `getErrorCategory()` returns correct category for boundary codes (1000, 1999, 2000, etc.).
3.  **Null Handling**: Verify `mExtras` is never null (defaults to `Bundle.EMPTY`).

## Implementation Risks
-   **Bundle Handling**: `Bundle` serialization in C++ requires careful handling of typed values.
-   **Category Logic**: Ensure the numeric ranges in C++ match the Java implementation exactly.

## Questions for C++ Team
-   Should this be implemented as a C++ Exception type or just a data carrier (struct)? Since it's passed via AIDL callback `onError`, it's likely just a data type in the Binder interface.
