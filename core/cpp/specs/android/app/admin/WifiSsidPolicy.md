# WifiSsidPolicy - Reverse Engineering Documentation

## 1. Executive Summary
`WifiSsidPolicy` is a final, `Parcelable` class that defines a policy for restricting Wi-Fi network connections based on their SSIDs. It allows administrators to specify either an allowlist (only connect to listed SSIDs) or a denylist (do not connect to listed SSIDs). This policy is applied to all network connections, including admin-configured ones, and will cause disconnections if the current network violates the policy.

## 2. Architecture Overview
`WifiSsidPolicy` is a data container for a Wi-Fi SSID policy type and a set of `WifiSsid` objects. It is designed to be an immutable value object, ensuring the consistency of the policy once it's created.

### Inheritance
- **`java.lang.Object`**: The root of the class hierarchy.
- **`android.os.Parcelable`**: Enables efficient serialization and deserialization for IPC.

### Design Patterns
- **Value Object**: Represents an immutable policy configuration.
- **Enumeration (via `IntDef`)**: Uses `@IntDef` to define a set of clear, type-safe constants for `WifiSsidPolicyType` (allowlist, denylist).

## 3. Detailed Functionality

### Constants (Policy Types)
- **`WIFI_SSID_POLICY_TYPE_ALLOWLIST` (0)**: Only SSIDs in the provided set are allowed.
- **`WIFI_SSID_POLICY_TYPE_DENYLIST` (1)**: SSIDs in the provided set are not allowed.

### `public WifiSsidPolicy(@WifiSsidPolicyType int policyType, @NonNull Set<WifiSsid> ssids)`
- **Purpose**: The sole constructor for creating a `WifiSsidPolicy` instance.
- **Algorithm**:
    1.  Validates that the input `ssids` set is not empty, throwing `IllegalArgumentException` if it is.
    2.  Validates `policyType` against the defined constants, throwing `IllegalArgumentException` if invalid.
    3.  Initializes `mPolicyType`.
    4.  Creates a new `ArraySet<WifiSsid>` and copies `ssids` into it, ensuring the internal set is defensively copied.

### `getSsids()`
- **Purpose**: Returns the set of `WifiSsid` objects associated with this policy.
- **Algorithm**: Returns the internal `mSsids` `ArraySet`.

### `getPolicyType()`
- **Purpose**: Returns the configured policy type.
- **Algorithm**: Returns the `mPolicyType` field.

### Serialization (`Parcelable`)
- **`writeToParcel(@NonNull Parcel dest, int flags)`**: Writes `mPolicyType` (int) and `mSsids` (ArraySet of `WifiSsid`) to the `Parcel`. The `WifiSsid` objects within the `ArraySet` are themselves `Parcelable`.
- **`CREATOR`**: Reads `mPolicyType` (int) and `mSsids` (ArraySet of `WifiSsid`) from the `Parcel` to reconstruct the object. The `readArraySet` method handles deserialization of the `WifiSsid` objects.

### `equals(Object thatObject)` and `hashCode()`
- **Purpose**: Provide value-based equality and consistent hashing.
- **Algorithm**: `equals` compares both `mPolicyType` and `mSsids` for equality. `hashCode` combines the hash codes of these two fields.

## 4. Data Model
- **`mPolicyType`**: `private int` (`@WifiSsidPolicyType`)
  - **Description**: The type of Wi-Fi SSID policy (allowlist or denylist).
- **`mSsids`**: `private ArraySet<WifiSsid>`
  - **Description**: The set of `WifiSsid` objects relevant to the policy.

## 5. Java-to-C++ Translation Guide
- **Class Structure**: A C++ equivalent would be a `class` with an `enum class` for `policyType` and an `std::unordered_set<WifiSsidC++>` for SSIDs.
  ```cpp
  class WifiSsidPolicy {
  public:
      enum class Type : int {
          ALLOWLIST = 0,
          DENYLIST = 1
      };

      explicit WifiSsidPolicy(Type policyType, const std::unordered_set<WifiSsidC++>& ssids);

      const std::unordered_set<WifiSsidC++>& getSsids() const;
      Type getPolicyType() const;

      // ... serialization, comparison, hashing
  private:
      Type mPolicyType;
      std::unordered_set<WifiSsidC++> mSsids; // Where WifiSsidC++ is the C++ equivalent of WifiSsid
  };
  ```
- **`WifiSsid`**: This is an Android-specific `Parcelable` class. A C++ equivalent (`WifiSsidC++`) would need to be created, likely as a struct or class with a `std::string` to hold the SSID value, and it would need its own serialization/deserialization.
- **`ArraySet`**: Maps to `std::unordered_set<WifiSsidC++>` in C++.
- **`Parcelable`**: A custom C++ serialization/deserialization mechanism is needed. `writeArraySet` implies writing the size then each element; C++ would replicate this by iterating through the `std::unordered_set` and serializing each `WifiSsidC++` object.

## 6. Implementation Risks & Key Considerations
- **`WifiSsid` Representation**: The correct translation of `WifiSsid` to a C++ equivalent is crucial, ensuring byte-for-byte compatibility if wire compatibility with Java `Parcel` is needed. `WifiSsid` often represents a byte array or a specific encoding of the SSID.
- **Empty Set Validation**: The Java constructor explicitly throws an `IllegalArgumentException` if the `ssids` set is empty. This validation should be replicated in the C++ constructor.

## 7. Questions for C++ Team
1.  Is there an existing C++ representation for Wi-Fi SSIDs, or will a new `WifiSsidC++` class need to be defined?
2.  How will the C++ serialization handle complex types like `std::unordered_set<WifiSsidC++>` for `Parcelable` compatibility?
3.  What is the expected behavior when `WifiSsid` objects contain non-UTF8 characters, as SSIDs can be arbitrary byte sequences?
