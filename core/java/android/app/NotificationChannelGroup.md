# NotificationChannelGroup - Reverse Engineering Documentation

## Executive Summary
`NotificationChannelGroup` is a container used to organize related `NotificationChannel` objects. This is particularly useful for applications that support multiple user accounts (e.g., email apps), allowing channels to be grouped by account name in the system settings UI.

## Architecture Overview
- **Structure**:
    - `mId`: Unique identifier for the group.
    - `mName`: User-visible label.
    - `mDescription`: Optional details about the group.
    - `mChannels`: A list of `NotificationChannel` objects associated with this group.
    - `mBlocked`: A boolean indicating if the entire group is blocked.
- **Serialization**: Implements `Parcelable` and supports XML serialization for persistence and backup.

## Detailed Functionality

### XML Serialization (`writeXml`, `populateFromXml`)
**Purpose**: Saves and restores group settings.
**Logic**:
- `writeXml`: Serializes ID, name, description, blocked state, and user-locked fields.
- `populateFromXml`: Reconstructs the group state from a `TypedXmlPullParser`.

### JSON Export (`toJson`)
**Purpose**: Provides a standard representation for diagnostic or logging purposes.
**Mechanism**: Constructs a `JSONObject` containing the group's metadata.

### User Locking
**Purpose**: Tracks if the user has manually blocked/unblocked the group.
**Logic**: Uses `mUserLockedFields` with the bit `USER_LOCKED_BLOCKED_STATE`.

## API Reference
- `public String getId()`: Returns the unique ID.
- `public CharSequence getName()`: Returns the display name.
- `public List<NotificationChannel> getChannels()`: Returns associated channels.
- `public boolean isBlocked()`: Returns the overall group block status.

## Java-to-C++ Translation Guide
- **Container Mapping**: Map `List<NotificationChannel>` to `std::vector<NotificationChannel>`.
- **JSON**: Use `nlohmann/json` or a similar C++ library for the `toJson` equivalent.
- **Parceling**: Use `libbinder`'s `Parcel` class. Note that Java's `writeParcelable` for `ParceledListSlice` must be mapped to a custom list serialization in C++.

## Implementation Risks
- **Trimming**: IDs and names must be trimmed to `MAX_TEXT_LENGTH` (1000) to match framework constraints.
- **Equality**: `equals` and `hashCode` include the list of channels, so deep comparison logic is required.
