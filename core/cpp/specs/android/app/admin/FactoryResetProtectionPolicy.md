# FactoryResetProtectionPolicy - Reverse Engineering Documentation

## 1. Executive Summary
`FactoryResetProtectionPolicy` is a final, `Parcelable` class that defines the enterprise policy for Android's Factory Reset Protection (FRP) feature. It allows a Device Owner or a Profile Owner on an organization-owned device to specify which accounts are authorized to unlock and provision a device after it undergoes an untrusted factory reset. It also provides a switch to disable the FRP feature entirely. The class uses a Builder pattern for easy and readable construction.

## 2. Architecture Overview
This class is a data-centric value object. Its primary purpose is to be constructed by a DPC application and passed to the `DevicePolicyManager` to be enforced by the system.

### Design Patterns
- **Builder Pattern**: A nested public static `Builder` class provides a fluent and clear API for constructing a `FactoryResetProtectionPolicy` object. This is suitable for a class with multiple configuration options, some of which may be optional. The builder defaults `factoryResetProtectionEnabled` to `true`.
- **Value Object**: The class represents an immutable policy configuration. Once `build()` is called, the state of the resulting `FactoryResetProtectionPolicy` object cannot be changed. Its `final` fields enforce this.
- **Data Transfer Object (DTO)**: It serves as a container to transfer the FRP policy data from the DPC client to the `DevicePolicyManagerService` via IPC.

### Serialization
- **`Parcelable`**: The class implements the `Parcelable` interface, allowing it to be marshaled and sent across process boundaries.
- **XML Persistence**: It includes hidden (`@hide`) methods `writeToXml` and `readFromXml`. These are used internally by the `DevicePolicyManagerService` to persist the policy to disk (typically in `/data/system/device_policies.xml`), ensuring the policy survives a reboot.

## 3. Detailed Functionality

### `Builder` Class
- **`public Builder()`**: Initializes a new builder with FRP enabled by default.
- **`public Builder setFactoryResetProtectionAccounts(@NonNull List<String> accounts)`**: Sets the list of account identifiers that can unlock the device. The list is defensively copied into a new `ArrayList`.
- **`public Builder setFactoryResetProtectionEnabled(boolean enabled)`**: Sets the master switch for the FRP feature.
- **`public FactoryResetProtectionPolicy build()`**: Constructs and returns the final, immutable `FactoryResetProtectionPolicy` object.

### `FactoryResetProtectionPolicy` Class
- **`getFactoryResetProtectionAccounts()`**: A public getter that returns the list of authorized accounts.
- **`isFactoryResetProtectionEnabled()`**: A public getter that returns whether the FRP feature is enabled.
- **`isNotEmpty()`**: A hidden helper method that returns `true` only if the policy is enabled *and* at least one account is specified, indicating an active, restrictive policy.

### `writeToParcel(...)` and `CREATOR`
- Standard `Parcelable` implementation. It writes the number of accounts, followed by each account string, and then the enabled boolean. This format must be mirrored in any C++ deserialization logic.

### `writeToXml(...)` and `readFromXml(...)`
- **`writeToXml`**: Serializes the policy to XML. It writes the `enabled` flag as an attribute of the main tag and then creates a separate `<factory_reset_protection_account>` tag for each account in the list.
- **`readFromXml`**: Deserializes the policy from XML, reading the attributes and iterating through the child tags to reconstruct the account list.

## 4. Data Model
- **`mFactoryResetProtectionAccounts`**: `private final List<String>`
  - **Description**: A list of opaque strings representing accounts. The interpretation of these strings (e.g., as email addresses) is left to the underlying FRP agent on the device.
- **`mFactoryResetProtectionEnabled`**: `private final boolean`
  - **Description**: A flag to enable or disable the FRP feature.

## 5. Java-to-C++ Translation Guide
- **Class Structure**: A C++ equivalent would be a simple class with a `std::vector<std::string>` and a `bool` as members.
- **Builder Pattern**: The builder pattern is a common C++ idiom and should be used for construction to maintain API clarity.
- **Immutability**: The main C++ class should enforce immutability by making its members `const` and providing only getter methods.
- **Serialization**:
  - For IPC, a custom serialization function would be needed to write the vector of strings and the boolean to a byte stream.
  - For persistence, an XML writing/parsing function using a standard C++ XML library (like pugixml or tinyxml2) would be required to match the format produced by `writeToXml`.

```cpp
class FactoryResetProtectionPolicy {
public:
    class Builder {
        // ... Builder methods
    };

    const std::vector<std::string>& getFactoryResetProtectionAccounts() const;
    bool isFactoryResetProtectionEnabled() const;

private:
    FactoryResetProtectionPolicy(std::vector<std::string> accounts, bool enabled);
    const std::vector<std::string> mAccounts;
    const bool mEnabled;
};
```

## 6. Implementation Risks & Key Considerations
- **Account String Format**: The documentation notes that the format of the account strings is opaque to the `DevicePolicyManager` and is interpreted by the "FRP management agent". This means a C++ implementation must ensure it uses the exact same account identifiers that the device's FRP agent expects.
- **Policy Application Logic**: The Javadoc contains important notes on when the policy applies (e.g., it applies even on Settings-initiated resets for org-owned POs). This application logic is part of `DevicePolicyManagerService` and the Setup Wizard flow, not this class, but is critical context for anyone using or reimplementing this policy.

## 7. Questions for C++ Team
1.  What component in the C++ environment is responsible for enforcing FRP (the equivalent of the "FRP management agent"), and what format does it expect for account identifiers?
2.  What is the standard C++ library for XML parsing and serialization to be used for policy persistence?
