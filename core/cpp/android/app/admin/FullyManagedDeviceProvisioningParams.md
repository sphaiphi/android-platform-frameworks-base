# FullyManagedDeviceProvisioningParams - Reverse Engineering Documentation

## 1. Executive Summary
`FullyManagedDeviceProvisioningParams` is a final, `Parcelable` class that acts as a parameter object for provisioning a fully managed device (i.e., setting a Device Owner). It consolidates all the configuration options required by `DevicePolicyManager#provisionFullyManagedDevice` into a single, immutable object. The class is constructed using the Builder pattern, ensuring that instances are valid and easy to create.

## 2. Architecture Overview
This class is a Data Transfer Object (DTO) designed to be created by a privileged provisioning application and consumed by the `DevicePolicyManagerService`.

### Design Patterns
- **Builder Pattern**: The class features a public static nested `Builder` class. This provides a fluent, readable API for constructing the complex parameter object. The builder requires essential parameters (the admin component and owner name) in its constructor and provides chainable methods for setting optional configurations.
- **Immutable Value Object**: The main `FullyManagedDeviceProvisioningParams` class is immutable. Its fields are `final` and are set only once by the private constructor, which is called by the `Builder`. This guarantees that the provisioning parameters are stable and cannot be changed after creation.
- **Parameter Object**: It groups a large number of method parameters into a single class, simplifying the method signature of `provisionFullyManagedDevice` and making the code more readable and maintainable.

### Key Dependencies
- **`DevicePolicyEventLogger`**: The class includes a hidden `logParams` method that integrates with the system's statistics logging framework, providing analytics on which provisioning features are being used.

## 3. Detailed Functionality

### `Builder` Class
- **`public Builder(ComponentName, String)`**: The constructor for the builder, requiring the two most critical pieces of information: the `ComponentName` of the app that will become the Device Owner, and a human-readable name for that owner.
- **`set...()` Methods**: A series of methods like `setLeaveAllSystemAppsEnabled()`, `setTimeZone()`, `setLocale()`, etc., allow the caller to configure various aspects of the device during provisioning. Each method returns the `Builder` instance to allow for a fluent, chainable calling style.
- **`build()`**: The terminal method that validates the parameters (implicitly through the builder's logic) and constructs the final, immutable `FullyManagedDeviceProvisioningParams` object.

### `FullyManagedDeviceProvisioningParams` Class
- **Getters**: A set of public getter methods (e.g., `getDeviceAdminComponentName()`, `isLeaveAllSystemAppsEnabled()`) provide read-only access to the configured parameters.
- **`logParams(String callerPackage)`**: A hidden (`@hide`) method used internally by the framework to log the configured parameters to `StatsLog` for metrics and analytics. It iterates through its settings and creates several `DevicePolicyEventLogger` events.

### Serialization (`Parcelable`)
- The class implements the `Parcelable` interface for IPC.
- **`writeToParcel(...)`**: Writes all member fields to the `Parcel` in a specific order. Notably, it serializes the `Locale` object by writing its language tag as a `String` (`mLocale.toLanguageTag()`).
- **`CREATOR`**: The static creator reads the fields from the `Parcel` in the same order and reconstructs the object. It correctly handles recreating the `Locale` from its language tag string.

## 4. Data Model
All fields are `private` and `final`, ensuring immutability.
- **`mDeviceAdminComponentName`**: `@NonNull ComponentName`
- **`mOwnerName`**: `@NonNull String`
- **`mLeaveAllSystemAppsEnabled`**: `boolean`
- **`mTimeZone`**: `@Nullable String`
- **`mLocalTime`**: `long`
- **`mLocale`**: `@Nullable Locale`
- **`mDeviceOwnerCanGrantSensorsPermissions`**: `boolean`
- **`mAdminExtras`**: `@NonNull PersistableBundle`
- **`mDemoDevice`**: `boolean`

## 5. Java-to-C++ Translation Guide
- **Parameter Object Pattern**: The overall pattern is directly applicable to C++. A C++ class would be created to hold the parameters.
- **Builder Pattern**: The Builder pattern is a common and recommended pattern in C++ for complex object construction. A nested `Builder` class can be implemented similarly.
- **Data Types**:
  - `ComponentName`, `String`, `PersistableBundle`, `Locale` would be mapped to their C++ equivalents, such as custom structs, `std::string`, and a map-like structure for the bundle.
  - `Locale` would be handled by storing and transmitting its string representation (language tag).
- **IPC**: If this parameter object needs to be sent over a C++ IPC mechanism, custom serialization/deserialization functions would be required (e.g., for Protobuf, D-Bus, or a custom format).

## 6. Implementation Risks & Key Considerations
- **Parameter Validation**: While the `Builder` enforces `non-null` for required objects, the ultimate validation of the parameters (e.g., is the timezone string valid?) happens within the `DevicePolicyManagerService` when it consumes this object.
- **Extensibility**: The use of a `PersistableBundle` (`mAdminExtras`) is a key extensibility point, allowing DPCs to pass arbitrary, custom data to themselves through the provisioning process.

## 7. Questions for C++ Team
1.  For passing a collection of optional parameters in C++, is the Builder pattern the preferred idiom, or are other patterns like designated initializers (if C++20 is available) or passing a single configuration struct used?
2.  What is the standard C++ equivalent for passing arbitrary key-value data like an Android `Bundle` or `PersistableBundle`? Would a `std::map<std::string, std::string>` or a more complex `std::map<std::string, std::any>` be used?
