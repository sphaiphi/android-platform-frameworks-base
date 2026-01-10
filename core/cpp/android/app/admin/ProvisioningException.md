# ProvisioningException - Reverse Engineering Documentation

## 1. Executive Summary
`ProvisioningException` is a custom exception class that extends `AndroidException`. It is specifically designed to be thrown when a failure occurs during the managed provisioning flows in Android (i.e., `DevicePolicyManager#provisionFullyManagedDevice` and `DevicePolicyManager#createAndProvisionManagedProfile`). This exception encapsulates a specific error code, providing granular information about the cause of the provisioning failure, which helps in debugging and error handling.

## 2. Architecture Overview
`ProvisioningException` integrates into Android's exception hierarchy, providing a specialized error type for provisioning-related issues. It combines a standard Java exception mechanism with a custom integer error code, allowing for both general error handling and specific programmatic responses.

### Inheritance
- **`android.util.AndroidException`**: The base class for exceptions that are part of the Android framework.

### Design Patterns
- **Custom Exception**: Defines a domain-specific exception for managed provisioning failures.
- **Enumeration (via `IntDef`)**: Uses `@IntDef` to define a set of clear, type-safe integer constants (`ERROR_UNKNOWN`, `ERROR_PRE_CONDITION_FAILED`, etc.) for `ProvisioningError` codes.

## 3. Detailed Functionality

### Constants (Error Codes)
The class defines several `public static final int` constants for various provisioning failure scenarios:
- **`ERROR_UNKNOWN` (0)**: A generic failure.
- **`ERROR_PRE_CONDITION_FAILED` (1)**: A precondition check failed.
- **`ERROR_PROFILE_CREATION_FAILED` (2)**: Managed profile creation failed.
- **`ERROR_ADMIN_PACKAGE_INSTALLATION_FAILED` (3)**: The admin package could not be installed.
- **`ERROR_SETTING_PROFILE_OWNER_FAILED` (4)**: Setting the profile owner failed.
- **`ERROR_STARTING_PROFILE_FAILED` (5)**: Starting the new profile failed.
- **`ERROR_REMOVE_NON_REQUIRED_APPS_FAILED` (6)**: Removing non-required apps failed (for fully managed devices).
- **`ERROR_SET_DEVICE_OWNER_FAILED` (7)**: Setting the device owner failed.

### Constructors
- **`public ProvisioningException(@NonNull Exception cause, @ProvisioningError int provisioningError)`**:
    - **Purpose**: Constructs an exception with a root cause and a specific error code.
    - **Algorithm**: Calls the more detailed constructor with `errorMessage = null`.
- **`public ProvisioningException(@NonNull Exception cause, @ProvisioningError int provisioningError, @Nullable String errorMessage)`**:
    - **Purpose**: The most detailed constructor, allowing for a root cause, an error code, and an optional human-readable message.
    - **Algorithm**: Calls the `super` constructor (`AndroidException`) with the `errorMessage` and `cause`. Stores the `provisioningError` in `mProvisioningError`.

### `getProvisioningError()`
- **Purpose**: Returns the specific error code associated with this exception.
- **Algorithm**: Returns the value of `mProvisioningError`.

## 4. Data Model
- **`mProvisioningError`**: `private final int` (`@ProvisioningError`)
  - **Type**: `int`
  - **Invariants**: Must be one of the predefined `ERROR_` constants.
  - **Description**: The specific error code indicating the cause of the provisioning failure.

## 5. Java-to-C++ Translation Guide
- **Custom Exception Class**: A C++ equivalent would be a custom exception class inheriting from `std::runtime_error` or a project-specific base exception class.
  ```cpp
  class ProvisioningException : public std::runtime_error {
  public:
      enum class ErrorCode : int {
          UNKNOWN = 0,
          PRE_CONDITION_FAILED = 1,
          // ... and so on
      };

      ProvisioningException(const std::exception& cause, ErrorCode errorCode, const std::string& errorMessage = "");

      ErrorCode getProvisioningError() const;

  private:
      ErrorCode mProvisioningError;
  };
  ```
- **Constants (`IntDef`)**: The integer constants for error codes should be translated to a C++ `enum class` for type safety and better encapsulation.
- **Constructor Delegation**: The Java constructors with `cause` and `errorMessage` can be replicated using C++ constructor delegation or by having a primary constructor that others call.
- **Root Cause (`cause`)**: `AndroidException` takes a `Throwable` cause. In C++, this can be handled by storing a `std::exception_ptr` or a `const std::exception*` in the exception object if deep exception chains are needed.

## 6. Implementation Risks & Key Considerations
- **Error Code Consistency**: It is vital that the C++ error codes precisely match the Java ones if cross-language communication or logging of these errors is expected.
- **Exception Hierarchy**: Ensure the C++ exception fits well into the project's existing exception handling strategy.

## 7. Questions for C++ Team
1.  What is the standard C++ base class for custom exceptions in this project (e.g., `std::runtime_error`, `std::exception`)?
2.  How should the `cause` parameter (the underlying exception) be represented and stored in the C++ `ProvisioningException`?
3.  Are there conventions for how error codes are exposed (e.g., as public `static const` members of the class, or as `enum class` members)?
