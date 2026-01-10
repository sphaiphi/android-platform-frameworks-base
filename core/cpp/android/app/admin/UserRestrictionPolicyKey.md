# UserRestrictionPolicyKey - Reverse Engineering Documentation

## 1. Executive Summary
`UserRestrictionPolicyKey` is a final class that extends `PolicyKey`. It is used to identify a policy that specifically relates to a user restriction, such as those set via `DevicePolicyManager#addUserRestriction` or `DevicePolicyManager#addUserRestrictionGlobally`. This class encapsulates a policy identifier (inherited from `PolicyKey`) and the specific user restriction string (`mRestriction`). It provides mechanisms for serialization to `Parcel` and `Bundle`, ensuring its transportability across different Android components. During construction, it enforces maximum length constraints on the restriction string using `PolicySizeVerifier`.

## 2. Architecture Overview
`UserRestrictionPolicyKey` is a specialized `PolicyKey` designed to pair a policy with a user restriction string. It leverages the base `PolicyKey`'s identifier and adds a specific restriction string to form a unique key for user restriction policies. The class is immutable, with its final fields assigned during construction.

### Inheritance
- **`android.app.admin.PolicyKey`**: Base class providing the core policy identifier and `Parcelable` implementation.

### Design Patterns
- **Value Object**: Represents an immutable pair of a policy key and a user restriction string.
- **Factory Method**: The `CREATOR` field is a standard Android pattern for un-parceling objects.

## 3. Detailed Functionality

### `public UserRestrictionPolicyKey(@NonNull String identifier, @NonNull String restriction)`
- **Purpose**: The primary constructor for creating a `UserRestrictionPolicyKey`.
- **Algorithm**:
    1.  Calls the `super` constructor with `identifier`.
    2.  Verifies `restriction` string length using `PolicySizeVerifier.enforceMaxStringLength()`.
    3.  Asserts `restriction` is not null and assigns it to `mRestriction`.

### `private UserRestrictionPolicyKey(Parcel source)`
- **Purpose**: Constructor used during deserialization from a `Parcel`.
- **Algorithm**: Reads the identifier and restriction string from the `Parcel`.

### `getRestriction()`
- **Purpose**: Returns the user restriction string associated with this policy key.
- **Algorithm**: Returns the value of the `mRestriction` field.

### `writeToBundle(Bundle bundle)`
- **Purpose**: Serializes the policy key into a `Bundle`, typically for use in broadcasts to `PolicyUpdateReceiver`.
- **Algorithm**: Puts the policy's string identifier into the `Bundle` under the key `EXTRA_POLICY_KEY`. (Note: unlike `PackagePolicyKey`, it does not put the restriction string in a nested bundle here; the `PolicyUpdateReceiver` typically processes this directly from the top-level identifier or infers it.)

### `writeToParcel(@NonNull Parcel dest, int flags)`
- **Purpose**: Implements `Parcelable` serialization.
- **Algorithm**: Writes the identifier string and the `mRestriction` string to the `Parcel`.

### `CREATOR` field
- **Purpose**: The `Parcelable.Creator` factory for deserializing `UserRestrictionPolicyKey` instances.
- **Algorithm**: Reads the identifier and restriction strings from the `Parcel` and uses them to construct a new `UserRestrictionPolicyKey`.

## 4. Data Model
- **`mRestriction`**: `private final String`
  - **Type**: `java.lang.String`
  - **Invariants**: Must not be `null`. Length constrained by `PolicySizeVerifier`.
  - **Description**: Stores the user restriction string (e.g., `UserManager.DISALLOW_USB_FILE_TRANSFER`).

## 5. Java-to-C++ Translation Guide
- **Class Structure**: A C++ equivalent would be a concrete subclass inheriting from a C++ `PolicyKey` base class.
  ```cpp
  class UserRestrictionPolicyKey : public PolicyKey {
  public:
      explicit UserRestrictionPolicyKey(std::string identifier, std::string restriction);

      const std::string& getRestriction() const;

      // ... serialization, comparison, hashing
  private:
      std::string mRestriction;
  };
  ```
- **Validation**: The `PolicySizeVerifier.enforceMaxStringLength` validation must be replicated in the C++ constructor.
- **`PolicyKey` Inheritance**: Relies on the C++ `PolicyKey` base class for the identifier.
- **Serialization**: Custom C++ serialization/deserialization functions would be needed for IPC and `Bundle` equivalents. The `Parcel` serialization would involve writing the identifier and `mRestriction` as strings.

## 6. Implementation Risks & Key Considerations
- **String Length Limits**: The C++ implementation must correctly enforce the same string length constraint as the Java version for `mRestriction`.
- **`Bundle` Compatibility**: Although `mRestriction` is not explicitly put in the `Bundle` by `writeToBundle` in this class (unlike `PackagePolicyKey` with `EXTRA_PACKAGE_NAME`), it's important to understand how `PolicyUpdateReceiver` might use `policyIdentifier` and `additionalPolicyParams` in general.

## 7. Questions for C++ Team
1.  How will `PolicySizeVerifier.enforceMaxStringLength` be applied to the `restriction` string in the C++ environment?
2.  How will the C++ `Bundle` abstraction handle policy keys that have additional parameters but don't explicitly put them in a nested bundle (relying on the main `policyIdentifier` instead)?
