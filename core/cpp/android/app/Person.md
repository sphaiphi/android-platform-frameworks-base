# Person - Reverse Engineering Documentation

## Executive Summary
`Person` is an immutable class that represents an entity (usually a human user or a machine/bot) that appears on different surfaces of the platform, such as in notifications. It provides a way to associate a name, an icon, a URI (linking to contacts), and a unique key with an entity. It is a key component of the `MessagingStyle` and `CallStyle` notification frameworks.

## Architecture Overview
- **Structure**:
    - `mName`: Display name of the person.
    - `mIcon`: Avatar image.
    - `mUri`: Link to system contacts (e.g., `content://com.android.contacts/contacts/lookup/...`).
    - `mKey`: Unique identifier to differentiate people with the same name.
    - `mIsBot`: Flag indicating if the entity is automated.
    - `mIsImportant`: Priority flag for the entity.
- **Inheritance**: Implements `Parcelable`.
- **Builder Pattern**: Uses an internal `Builder` class for construction to maintain immutability.

## Detailed Functionality

### Construction
**Purpose**: Creates a `Person` object.
**Mechanism**: Private constructor used by `Builder.build()` or `Parcelable.CREATOR`.

### URI Visitation (`visitUris`)
**Purpose**: Collects all `Uri` objects contained within the `Person` instance.
**Logic**: Collects the `mUri` and the URI from the `mIcon` (if it's a URI-based icon). This is used by the system to grant temporary URI permissions to recipient processes.

### Equality and Hashing
**Purpose**: Allows comparing people across notification updates.
**Logic**: Checks all fields, including deep icon comparison (`mIcon.sameAs(...)`).

## API Reference
- `public String getUri()`: Returns contact link.
- `public CharSequence getName()`: Returns display name.
- `public Icon getIcon()`: Returns avatar.
- `public boolean isBot()`: Checks bot status.
- `public Builder toBuilder()`: Allows creating a modified copy.

## Java-to-C++ Translation Guide
- **Immutability**: Enforce immutability in C++ by making all members `const` or private with no setters.
- **Icon Mapping**: Use `android::graphics::drawable::Icon` equivalent.
- **URI Support**: Use a native URI library or string representation for the `mUri` field.
- **Builder**: Implement a C++ builder pattern with a fluent interface.

## Implementation Risks
- **Reference Management**: If icons are bitmap-based, ensure proper memory management (smart pointers) to avoid duplication or leaks.
- **Permission Chains**: The `visitUris` logic is critical for the system's security model. If missed in C++, recipients might crash when attempting to render an icon without permissions.
