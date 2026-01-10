# DeviceAdminInfo - Reverse Engineering Documentation

## Executive Summary
`DeviceAdminInfo` is a critical metadata class in the Android Device Administration framework. It encapsulates all the information about a single device administrator component, parsed from the application's `AndroidManifest.xml` and its associated XML metadata resource. This class informs the system about which policies an administrator can use, how it should be displayed to the user, and other special capabilities it possesses. It is `Parcelable`, allowing it to be efficiently transported across process boundaries.

## Architecture Overview
`DeviceAdminInfo` is essentially a data holder, but its construction involves significant logic. It acts as the bridge between a `DeviceAdminReceiver` component's static declaration and the runtime enforcement by the `DevicePolicyManager`.

- **Source of Truth**: The primary source for its data is the `res/xml/` resource file pointed to by the `android.app.device_admin` meta-data entry in the receiver's manifest declaration.
- **Static Policy Registry**: The class maintains a static set of maps (`sKnownPolicies`, `sRevKnownPolicies`) and a list (`sPoliciesDisplayOrder`) that define all possible policies an admin can request, mapping their integer identifiers to XML tags and descriptive string resources.
- **Bitmask for Policies**: It uses an integer bitmask (`mUsesPolicies`) to efficiently store the set of policies requested by the admin.

### Design Patterns
- **Immutable Object**: Once constructed, the core information (like the policies it uses) of a `DeviceAdminInfo` object does not change.
- **Factory/Builder (Implicit)**: The constructor acts as a factory that builds the `DeviceAdminInfo` object by parsing external resources, a more complex process than typical object creation.
- **Registry**: The static fields act as a central registry for all known device administration policies.

## Detailed Functionality

### `DeviceAdminInfo(Context context, ActivityInfo activityInfo)`
**Purpose**: The main constructor. It parses the XML metadata associated with a `DeviceAdminReceiver` component to populate the `DeviceAdminInfo` object.
**Algorithm**:
1.  Stores the provided `ActivityInfo`.
2.  Gets the `PackageManager` from the `Context`.
3.  Loads the XML metadata file specified by `DeviceAdminReceiver.DEVICE_ADMIN_META_DATA` for the given `activityInfo`.
4.  If the XML is not found, throws an `XmlPullParserException`.
5.  Parses the root `<device-admin>` tag to get attributes like `visible`.
6.  Iterates through child tags:
    - If a `<uses-policies>` tag is found, it iterates through its children.
    - For each child tag inside `<uses-policies>` (e.g., `<wipe-data />`), it looks up the policy name in the static `sKnownPolicies` map.
    - If found, the corresponding integer identifier is used to set a bit in the `mUsesPolicies` integer bitmask.
    - If not found, a warning is logged.
    - If a `<support-transfer-ownership>` tag is found, `mSupportsTransferOwnership` is set to `true`.
    - If a `<headless-system-user>` tag is found, it parses the mode and sets `mHeadlessDeviceOwnerMode`.
7.  Handles potential `NameNotFoundException` if the application's resources can't be found.
**C++ Implementation Guidance**: C++ lacks a direct equivalent of `PackageManager` and XML resource parsing integrated into a component model. A C++ equivalent would require:
    1. A mechanism to associate a metadata file (e.g., an XML file) with a component.
    2. An XML parser (like pugixml) to read and interpret the file.
    3. A data structure to hold the parsed information, analogous to the `DeviceAdminInfo` fields.
    4. A static registry of policies similar to `sKnownPolicies`.

### `usesPolicy(int policyIdent)`
**Purpose**: Checks if the device admin has requested permission to use a specific policy.
**Algorithm**:
1.  Performs a bitwise AND operation between the `mUsesPolicies` bitmask and a mask created by left-shifting `1` by `policyIdent` bits (`1 << policyIdent`).
2.  Returns `true` if the result is not zero, `false` otherwise.
**C++ Implementation Guidance**: This is a straightforward bitwise operation in C++ as well.
```cpp
bool usesPolicy(int policyIdent) const {
    return (mUsesPolicies & (1 << policyIdent)) != 0;
}
```

### `getUsedPolicies()`
**Purpose**: Returns a list of `PolicyInfo` objects for all policies that this admin uses.
**Algorithm**:
1. Creates an empty `ArrayList<PolicyInfo>`.
2. Iterates through the static `sPoliciesDisplayOrder` list.
3. For each `PolicyInfo` in the list, it calls `usesPolicy()` with the policy's identifier.
4. If `usesPolicy()` returns `true`, the `PolicyInfo` object is added to the result list.
5. Returns the list.
**C++ Implementation Guidance**: This logic can be replicated directly in C++, iterating over a static vector of policy information and building a new vector of policies used by the instance.

## Data Model
- **`mActivityInfo`**: `final ActivityInfo`
  - **Description**: Contains all the information about the underlying `BroadcastReceiver` component as parsed from the manifest.
- **`mVisible`**: `boolean`
  - **Description**: Whether the admin should be visible in UI lists even when not enabled.
- **`mUsesPolicies`**: `int`
  - **Description**: An integer bitmask where each bit corresponds to a specific policy identifier (e.g., `USES_POLICY_WIPE_DATA`).
- **`mSupportsTransferOwnership`**: `boolean`
  - **Description**: Whether this admin can be the target of a Device/Profile Owner transfer.
- **`mHeadlessDeviceOwnerMode`**: `int` (`@HeadlessDeviceOwnerMode`)
  - **Description**: The declared mode of operation if provisioned on a headless system user device.

## API Reference
- **`public DeviceAdminInfo(Context context, ResolveInfo resolveInfo)`**: Primary public constructor.
- **`public String getPackageName()`**: Returns the admin's package name.
- **`public ComponentName getComponent()`**: Returns the admin's `ComponentName`.
- **`public CharSequence loadLabel(PackageManager pm)`**: Loads the user-visible label for the admin.
- **`public CharSequence loadDescription(PackageManager pm)`**: Loads the user-visible description for the admin.
- **`public Drawable loadIcon(PackageManager pm)`**: Loads the user-visible icon for the admin.
- **`public boolean usesPolicy(int policyIdent)`**: Checks if a specific policy is used.
- **`public boolean supportsTransferOwnership()`**: Checks if ownership transfer is supported.
- **`public int getHeadlessDeviceOwnerMode()`**: Gets the declared headless mode.
- **`public void writeToParcel(Parcel dest, int flags)`**: `Parcelable` implementation.

## Java-to-C++ Translation Guide
- **XML Parsing**: The constructor's core logic is XML parsing. A standard C++ XML library would be required. The tight coupling between the component model (`PackageManager`) and resource loading would need to be re-architected in a pure C++ environment.
- **Bitmask**: Integer bitmasks are directly translatable to C++.
- **`Parcelable`**: A custom serialization/deserialization mechanism would be needed. The `ActivityInfo` object is complex and would require its own C++ equivalent and serialization logic if it needs to be part of the data model.
- **Resource Loading (`loadLabel`, `loadIcon`, etc.)**: C++ does not have a built-in application resource model like Android. This functionality would depend entirely on the asset/resource management system of the target C++ platform.

## Implementation Risks
- **XML Parsing Complexity**: The XML parsing logic in the constructor is stateful and navigates the XML tree. A C++ reimplementation must be robust against malformed XML to avoid crashes or incorrect state.
- **Static Initializer**: The static block that initializes the policy registry (`sPoliciesDisplayOrder`, etc.) runs once when the class is loaded. In C++, this would be a static initializer. Care must be taken to ensure it is thread-safe and runs before any `DeviceAdminInfo` objects are created.

## Questions for C++ Team
- What is the intended C++ replacement for the Android application and resource model? How will metadata for a component be stored and loaded?
- How should the static policy registry be managed in C++? As a global static variable, or within a singleton manager class?
