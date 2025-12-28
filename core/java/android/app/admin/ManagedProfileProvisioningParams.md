# ManagedProfileProvisioningParams - Reverse Engineering Documentation

## 1. Executive Summary
`ManagedProfileProvisioningParams` is a final, `Parcelable` class that functions as a parameter object for provisioning a new managed profile (i.e., setting a Profile Owner). It aggregates all the necessary configuration details for the `DevicePolicyManager#createAndProvisionManagedProfile` system API into a single, immutable container. The class is constructed using the Builder pattern, which provides a clear and robust way to specify the desired provisioning options.

## 2. Architecture Overview
This class is the managed profile counterpart to `FullyManagedDeviceProvisioningParams` and shares the same architectural design. It serves as a Data Transfer Object (DTO) created by a privileged provisioning app and consumed by the `DevicePolicyManagerService`.

### Design Patterns
- **Builder Pattern**: A public static nested `Builder` class provides a fluent API for construction. The builder's constructor requires the essential admin `ComponentName` and owner name, while optional settings are configured via chainable setter methods.
- **Immutable Value Object**: The main class is immutable, with all fields being `final` and set only once during construction via the `Builder`. This ensures the parameters are stable and thread-safe once created.
- **Parameter Object**: This pattern is used to group the many parameters associated with managed profile provisioning into a single, cohesive class, greatly simplifying the signature of the provisioning method.

### Key Dependencies
- **`DevicePolicyEventLogger`**: The class contains a hidden `logParams` method that integrates with the system's statistics logging framework, allowing for analytics on how provisioning features are being utilized.

## 3. Detailed Functionality

### `Builder` Class
- **`public Builder(ComponentName, String)`**: The constructor for the builder, taking the `ComponentName` of the app that will become the Profile Owner and a human-readable name for that owner.
- **`set...()` Methods**: A series of methods for configuring the provisioning process:
    - `setProfileName()`: Sets a custom name for the managed profile.
    - `setAccountToMigrate()`: Specifies an `Account` from the parent user to be moved into the new profile.
    - `setKeepingAccountOnMigration()`: Determines if the migrated account should also be kept on the parent profile.
    - `setLeaveAllSystemAppsEnabled()`: Controls the availability of non-essential system apps in the new profile.
    - `setOrganizationOwnedProvisioning()`: A critical flag to declare that the profile is on a company-owned device, granting the Profile Owner elevated privileges.
    - `setAdminExtras()`: Provides a `PersistableBundle` for the DPC to pass custom data to itself.
- **`build()`**: Constructs and returns the final, immutable `ManagedProfileProvisioningParams` object.

### `ManagedProfileProvisioningParams` Class
- **Getters**: Public getter methods (e.g., `getProfileAdminComponentName()`, `getAccountToMigrate()`) provide read-only access to the configured parameters.
- **`logParams(String callerPackage)`**: A hidden (`@hide`) method used by the framework to log the configured parameters to `StatsLog` for system analytics.

### Serialization (`Parcelable`)
- The class implements the standard `Parcelable` interface for IPC.
- **`writeToParcel(...)`**: Writes all member fields to the `Parcel` in a defined sequence. This includes `ComponentName`, `String` (for names), `Account`, `boolean` flags, and `PersistableBundle`. Notably, `writeTypedObject` is used for `ComponentName` and `Account`, leveraging their own `Parcelable` implementations.
- **`CREATOR`**: The static factory reads the fields from the `Parcel` in the same sequence to reconstruct the object. It uses `readTypedObject` for `ComponentName` and `Account`.

## 4. Data Model
All fields are `private` and `final`, ensuring immutability.
- **`mProfileAdminComponentName`**: `@NonNull ComponentName`
- **`mOwnerName`**: `@NonNull String`
- **`mProfileName`**: `@Nullable String`
- **`mAccountToMigrate`**: `@Nullable Account`
- **`mLeaveAllSystemAppsEnabled`**: `boolean`
- **`mOrganizationOwnedProvisioning`**: `boolean`
- **`mKeepAccountOnMigration`**: `boolean`
- **`mAdminExtras`**: `@NonNull PersistableBundle`

## 5. Java-to-C++ Translation Guide
- **Parameter Object Pattern**: The overall pattern is directly applicable to C++. A C++ class would be created to hold the parameters.
- **Builder Pattern**: A nested `Builder` class should be implemented in C++ to maintain API clarity and ease of use.
- **Data Types**:
  - `ComponentName`, `String`, `PersistableBundle` would map to C++ equivalents like custom structs, `std::string`, and map-like structures (e.g., `std::map<std::string, std::any>` or a custom equivalent for `PersistableBundle`).
  - `Account` is an Android-specific `Parcelable` class. A C++ equivalent would need to be created, likely as a struct containing `name` and `type` strings.
- **IPC**: If the object is passed over a C++ IPC boundary, custom serialization/deserialization functions would be needed. This would involve replicating the exact sequence of `writeTypedObject`, `writeString`, `writeBoolean`, `writePersistableBundle` using C++ equivalents for parceling.

## 6. Implementation Risks & Key Considerations
- **`organizationOwnedProvisioning` Flag**: This boolean has significant security implications. When `true`, the resulting Profile Owner gains a much higher level of device control than a standard Profile Owner on a personal device. The system must correctly interpret and enforce the different permission levels based on this flag.
- **Account Migration**: The account migration logic is a complex flow handled deep within the system server (`AccountManagerService`). The parameters in this class are merely the inputs to that flow.
- **Parcelable Objects (`ComponentName`, `Account`, `PersistableBundle`)**: The `Parcelable` implementations of these nested objects must also be correctly translated and be wire-compatible if cross-language communication is required.

## 7. Questions for C++ Team
1.  What is the C++ equivalent of the Android `Account` object and `AccountManager` framework? How would an account be identified for migration in the C++ environment?
2.  How will the C++ policy service differentiate between a "regular" Profile Owner and one on an organization-owned device to grant the correct, elevated permissions?
3.  What is the preferred mechanism for serializing complex, nested data structures like `ManagedProfileProvisioningParams` for IPC in C++?