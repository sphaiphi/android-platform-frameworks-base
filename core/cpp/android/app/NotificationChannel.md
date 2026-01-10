# NotificationChannel - Reverse Engineering Documentation

## Executive Summary
`NotificationChannel` represents a collection of settings that apply to a similarly themed category of notifications. Introduced in Android O, it allows users to have granular control over notification behaviors (like sound, vibration, and importance) for each app, rather than global on/off switches. Once a channel is created, most of its settings are "locked" and can only be modified by the user.

## Architecture Overview
- **Key Settings**:
    - `mImportance`: Controls how interruptive notifications are (`NONE`, `MIN`, `LOW`, `DEFAULT`, `HIGH`).
    - `mSound`: The URI of the alert sound.
    - `mVibrationPattern` / `mVibrationEffect`: Vibration configuration.
    - `mLockscreenVisibility`: Visibility on the secure lockscreen.
    - `mGroup`: ID of the `NotificationChannelGroup` this channel belongs to.
- **State Persistence**: Serializes to XML for storage in the system server.
- **Security**: Includes flags for `mUserLockedFields` to track which settings were explicitly changed by the user, preventing the app from overriding them.

## Detailed Functionality

### Constructor(String id, CharSequence name, int importance)
**Purpose**: Creates a new channel.
**Logic**: Validates and trims the ID and name strings. Truncates them to `MAX_TEXT_LENGTH` (1000 chars) if exceeded.

### Vibration Management
**Purpose**: Handles both legacy vibration patterns (long arrays) and modern `VibrationEffect` objects.
**Algorithm**: 
- `setVibrationPattern`: Enables vibration and stores the array.
- `setVibrationEffect`: Stores the effect and attempts to compute an equivalent waveform pattern for compatibility.
- Includes logic to "crop" long vibration effects if the `notif_channel_crop_vibration_effects` flag is enabled.

### XML Serialization (`writeXml`, `populateFromXml`)
**Purpose**: Facilitates backup/restore and system storage.
**Algorithm**:
- Writes all attributes (ID, name, description, importance, sound, vibration, etc.) to a `TypedXmlSerializer`.
- Handles canonicalization of sound URIs during backup to ensure they remain valid on different devices.
- `populateFromXml`: Reads attributes and handles special cases like restoring sound URIs based on whether the parent package is installed.

### Importance Locking
**Purpose**: Prevents apps from changing channel settings after the user has expressed a preference.
**Logic**: Tracks bits in `mUserLockedFields` (e.g., `USER_LOCKED_IMPORTANCE`, `USER_LOCKED_SOUND`). If a bit is set, the system server will ignore app-requested updates to that specific field.

## Data Model
- `mId`: Unique string ID per package.
- `mName`: User-visible name.
- `mDesc`: Optional user-visible description.
- `mParentId` / `mConversationId`: Links to shortcuts for conversation-centric channels.

## API Reference
- `public String getId()`: Returns the unique ID.
- `public int getImportance()`: Returns the current importance level.
- `public boolean canBubble()`: Checks if notifications on this channel can show as bubbles.
- `public boolean isConversation()`: Checks if the channel represents a messaging thread.

## Java-to-C++ Translation Guide
- **XML Mapping**: Use `android::modules::utils::TypedXmlPullParser` equivalents if available in C++.
- **URI Handling**: Map `android.net.Uri` to a native URI wrapper that handles scheme resolution.
- **Audio Attributes**: Map `android.media.AudioAttributes` to its C++ counterpart used in the audio framework.
- **Bitmasks**: Use bitwise operations for `mUserLockedFields` logic.

## Implementation Risks
- **Parsing Robustness**: Malformed XML or unexpectedly long strings must be handled gracefully to avoid crashing the system server.
- **Vibration Compatibility**: Replicating the logic that converts between `VibrationEffect` and long arrays is tricky and must match the framework's internal math.
- **Sound Restoration**: The logic for `restoreSoundUri` is complex, involving ringtone type resolution and uncanonicalization.
