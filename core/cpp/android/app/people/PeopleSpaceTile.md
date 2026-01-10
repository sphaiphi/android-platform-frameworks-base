# PeopleSpaceTile - Reverse Engineering Documentation

## Executive Summary
`PeopleSpaceTile` is a comprehensive data object containing all the information required to render a "People Tile" in the UI (e.g., SystemUI or Launcher). It aggregates contact info, notification content, conversation status, and interaction timestamps.

## Architecture Overview
- **Type**: Data Transfer Object (Parcelable).
- **Design Pattern**: Builder Pattern.
- **Purpose**: Decouples the UI rendering from the underlying data sources (Shortcuts, Notifications, Contacts).

## Detailed Functionality

### Builder Construction
**Purpose**: Flexible creation from different sources.
**Sources**:
1. **ShortcutInfo + LauncherApps**: Extracts label, icon, user handle, package, contact URI.
2. **ConversationChannel + LauncherApps**: Extracts shortcut info plus conversation-specifics like statuses and DND settings.
3. **Manual**: Raw fields (used for specific cases like "Birthday" tiles without a shortcut).

### Icon Conversion (`convertDrawableToIcon`)
**Purpose**: Utility to convert a `Drawable` into a `Bitmap`-based `Icon`.
**Logic**:
1. If `BitmapDrawable`, use its bitmap.
2. Otherwise, draw the drawable onto a new Canvas/Bitmap.
3. Handle zero-size drawables by creating a 1x1 placeholder.

## Data Model

### Fields
| Java Field | Type | Description | C++ Equivalent |
| :--- | :--- | :--- | :--- |
| `mId` | `String` | Unique Tile ID (usually Shortcut ID). | `std::string` |
| `mUserName` | `CharSequence` | Display name. | `std::u16string` |
| `mUserIcon` | `Icon` | Avatar icon. | `android::graphics::drawable::Icon*` |
| `mContactUri` | `Uri` | Contacts Provider URI. | `android::net::Uri*` |
| `mUserHandle` | `UserHandle` | User profile handle. | `android::os::UserHandle*` |
| `mPackageName` | `String` | Source app package. | `std::string` |
| `mBirthdayText` | `String` | Text for birthday status. | `std::string` |
| `mLastInteractionTimestamp` | `long` | Last event time. | `int64_t` |
| `mIsImportantConversation` | `boolean` | Priority status. | `bool` |
| `mNotificationKey` | `String` | Key for active notification. | `std::string` |
| `mStatuses` | `List<ConversationStatus>` | Rich statuses. | `std::vector<ConversationStatus>` |
| `mIntent` | `Intent` | Launch intent (onClick). | `android::content::Intent*` |
| `mNotificationPolicyState` | `int` | Bitmask for policy (Show/Block). | `int32_t` |

### Notification Policy Flags
- `SHOW_CONVERSATIONS` (1)
- `BLOCK_CONVERSATIONS` (2)
- `SHOW_IMPORTANT_CONVERSATIONS` (4)
- `SHOW_STARRED_CONTACTS` (8)
- `SHOW_CONTACTS` (16)

## Java-to-C++ Translation Guide

### Static Methods
- `convertDrawableToIcon` involves graphics operations (`Canvas`, `Bitmap`). This is complex to port directly to core C++ without HWUI or Skia dependencies. If this logic is needed in C++, ensure the graphics stack is available, or delegate icon creation to a layer that handles graphics.

### Parcelable
- Extensive `writeToParcel`/`createFromParcel` implementation.
- Contains nested Parcelables (`Icon`, `Uri`, `UserHandle`, `Intent`).
- **Critical**: Order of fields in `writeToParcel` must strictly match the read order.

### Builder Pattern
- Implement a standard C++ Builder or a fluent interface for struct initialization.

### URIs and Intents
- These are opaque objects in C++ core usually handled as `android::net::Uri` (if available) or flattened strings/parcel representations.

## Implementation Risks
- **Graphics Dependency**: The `convertDrawableToIcon` method logic strongly implies this class is used where graphics context is available. Pure logic C++ components might not be able to execute this method.
- **Field Explosion**: This class has many fields. Adding/removing fields requires updating the Parcel read/write logic carefully to maintain compatibility.

## Questions for C++ Team
- Do we need to support the `convertDrawableToIcon` utility in the C++ layer? Or is this purely a helper for the Java UI layer?
