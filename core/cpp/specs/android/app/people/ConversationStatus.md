# ConversationStatus - Reverse Engineering Documentation

## Executive Summary
`ConversationStatus` represents a transient status update for a conversation, such as "Listening to music", "Birthday", or "Location sharing". It is an immutable value object designed to be passed via IPC. It uses the Builder pattern for construction.

## Architecture Overview
- **Type**: Immutable Data Object (Parcelable).
- **Design Pattern**: Builder Pattern.
- **Constants**: Defines integer constants for `ActivityType` and `Availability`.

## Detailed Functionality

### Builder (`ConversationStatus.Builder`)
**Purpose**: Construct `ConversationStatus` instances.
**Logic**: Accumulates fields and validates inputs (e.g., non-null ID).
**Key Methods**:
- `setAvailability(int)`
- `setDescription(CharSequence)`
- `setIcon(Icon)`
- `setStartTimeMillis(long)`
- `setEndTimeMillis(long)`

### Equality & Hashing
**Purpose**: Value-based equality.
**Logic**: Compares all fields (`mActivity`, `mAvailability`, `mStartTimeMs`, `mEndTimeMs`, `mId`, `mDescription`, `mIcon`).

## Data Model

### Constants

**ActivityType (`mActivity`)**
| Java Constant | Value | Description |
| :--- | :--- | :--- |
| `ACTIVITY_OTHER` | 0 | Generic activity. |
| `ACTIVITY_BIRTHDAY` | 1 | Birthday today. |
| `ACTIVITY_ANNIVERSARY` | 2 | Anniversary today. |
| `ACTIVITY_NEW_STORY` | 3 | New social story. |
| `ACTIVITY_AUDIO` | 4 | Listening to audio. |
| `ACTIVITY_VIDEO` | 5 | Watching video. |
| `ACTIVITY_GAME` | 6 | Playing a game. |
| `ACTIVITY_LOCATION` | 7 | Sharing location. |
| `ACTIVITY_UPCOMING_BIRTHDAY` | 8 | Birthday soon. |

**Availability (`mAvailability`)**
| Java Constant | Value | Description |
| :--- | :--- | :--- |
| `AVAILABILITY_UNKNOWN` | -1 | Unknown state. |
| `AVAILABILITY_AVAILABLE` | 0 | User is available. |
| `AVAILABILITY_BUSY` | 1 | User is busy (DND equivalent). |
| `AVAILABILITY_OFFLINE` | 2 | User is offline. |

### Fields
| Java Field | Type | Description | C++ Equivalent |
| :--- | :--- | :--- | :--- |
| `mId` | `String` | Unique ID for this status. | `std::string` |
| `mActivity` | `int` | Type of activity (ActivityType). | `int32_t` (enum) |
| `mAvailability` | `int` | User availability. | `int32_t` (enum) |
| `mDescription` | `CharSequence` | User-visible text. | `std::u16string` (or `String16`) |
| `mIcon` | `Icon` | Visual icon. | `android::graphics::drawable::Icon*` |
| `mStartTimeMs` | `long` | Start time (epoch ms). | `int64_t` |
| `mEndTimeMs` | `long` | Expiration time (epoch ms). | `int64_t` |

## Java-to-C++ Translation Guide

### Enum Handling
- Convert `@IntDef` constants into C++ `enum class`.
- `ActivityType` -> `enum class ActivityType : int32_t { ... }`
- `Availability` -> `enum class Availability : int32_t { ... }`

### Strings
- `CharSequence` in Java usually maps to `String16` (UTF-16) in Android C++ framework to support rich text/spans, though usually flattened to plain strings for simple IPC. Here it is likely just text.

### Icon
- `android.graphics.drawable.Icon` needs a C++ equivalent representation, likely handling the Parcelable serialization of the bitmap or resource ID.

### Parcelable Implementation
- **Write Order**: `mId` (String), `mActivity` (int), `mAvailability` (int), `mDescription` (CharSequence), `mIcon` (Parcelable), `mStartTimeMs` (long), `mEndTimeMs` (long).
- Ensure strictly matching read/write order.

## Test Cases & Validation
- **Equality**: Two statuses created with identical builder parameters must compare equal.
- **Serialization**: Write to parcel, read back, assert `equals()` is true.
- **Null Handling**: `mDescription` and `mIcon` can be null. `mId` cannot.

## Implementation Risks
- **Icon Serialization**: Passing Icons (especially those containing Bitmaps) across IPC can be heavy. The C++ implementation must handle the `Icon` parcelable format correctly.

## Questions for C++ Team
- Is there a standard C++ wrapper for `android.graphics.drawable.Icon`?
