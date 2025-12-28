# Notification - Reverse Engineering Documentation

## Executive Summary
`Notification` is a foundational class representing a persistent message or event presented to the user through the `NotificationManager`. It encapsulates everything from simple text and icons to complex, interactive media controllers and conversational messaging threads. It uses a builder pattern for construction and supports extensive customization through "Styles".

## Architecture Overview
- **Key Components**:
    - **Core Metadata**: `when`, `creationTime`, `number`, `icon`, `contentIntent`, `deleteIntent`, `fullScreenIntent`.
    - **UI Elements**: `tickerText`, `contentView`, `bigContentView`, `headsUpContentView`, `mLargeIcon`.
    - **Internal Storage**: `extras` (Bundle) stores semantic data and original inputs.
    - **Style Framework**: Abstract inner class `Style` and its implementations (`BigTextStyle`, `BigPictureStyle`, `InboxStyle`, `MediaStyle`, `MessagingStyle`, `CallStyle`, `ProgressStyle`).
- **Inner Classes**:
    - `Builder`: The primary entry point for constructing notifications.
    - `Action`: Represents interactive buttons attached to the notification.
    - `MessagingStyle.Message`: Individual message units for conversations.
    - `BubbleMetadata`: Configures floating window (bubble) behavior.

## Detailed Functionality

### Construction via `Notification.Builder`
**Purpose**: Simplifies the creation of complex notification objects.
**Logic**:
1. Sets basic properties (title, text, small icon).
2. Manages `extras` to store raw inputs for consumption by listeners.
3. Automatically selects standard layout resources (XML) based on target SDK and provided data.
4. `build()` method aggregates all inputs, applies styles, and performs validation (e.g., matching shortcut IDs).

### Style System
**Mechanism**: Subclasses of `Style` override how the notification is rendered in its various forms (collapsed, expanded, heads-up).
- `MessagingStyle`: Optimizes for conversation flows, managing a list of `Message` objects and support for avatars and group titles.
- `CallStyle`: Specializes in incoming/ongoing/screening call UIs, providing standardized "Answer" and "Decline" actions with emphasized colors.
- `ProgressStyle`: Offers advanced progress tracking with segments, points, and custom icons.

### Parcelable Implementation
**Purpose**: Enables the transfer of complex notification data across process boundaries (App -> System Server -> System UI).
**Algorithm**:
- Uses a custom versioning scheme.
- Explicitly marshals `allPendingIntents` separately to ensure they are tracked by the system for battery/security allowlisting.
- Handles `Icon` and `Uri` serialization.

### Resource and Image Management
**Purpose**: Reduces memory pressure and ensures compatibility.
**Logic**:
- `reduceImageSizes(...)`: Downscales large bitmaps and icons to conform to device-specific memory limits (especially on Low RAM devices).
- `visitUris(...)`: Traverses the entire notification structure to collect all referenced `Uri` objects, facilitating permission grants for the recipient process.

## Data Model
- `flags`: Bitmask defining behavior (`FLAG_ONGOING_EVENT`, `FLAG_AUTO_CANCEL`, `FLAG_FOREGROUND_SERVICE`, etc.).
- `priority`/`visibility`: Determines how and where the notification appears.
- `mChannelId`: Links the notification to a specific `NotificationChannel`.
- `mGroupKey`: Used for clustering notifications into stacks.

## API Reference (Key Methods)
- `public String getChannelId()`: Returns the target channel.
- `public Icon getSmallIcon()`: Returns the primary icon.
- `public List<Action> getContextualActions()`: Returns system-suggested actions.
- `public boolean isSilent()`: Checks if the notification was configured to be quiet.

## Java-to-C++ Translation Guide
- **Complex Bundles**: Map `extras` to `android::os::Bundle`.
- **UI Templates**: In a native environment, these would be mapped to a native layout engine or serialized as metadata for a separate UI process (like SystemUI).
- **Styles**: Use a visitor or decorator pattern to apply style-specific modifications to the base notification structure.
- **Icon Management**: Map `android.graphics.drawable.Icon` to a native equivalent that handles resource IDs, bitmaps, and URIs.

## Implementation Risks
- **Parcel Size**: Notifications can grow very large due to nested extras, actions, and messages. C++ marshalling must be efficient and potentially use shared memory for large bitmaps (ashmem).
- **Consistency**: The `extras` keys must be kept in perfect sync with the Java side, as many system components rely on these specific strings for logic (e.g., `android.title`, `android.template`).
- **Compatibility**: Logic for `isLegacy()` and SDK-version-dependent layout choices must be replicated carefully to maintain visual consistency across app targets.
