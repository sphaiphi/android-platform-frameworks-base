# Tile - Reverse Engineering Documentation

## Executive Summary
`Tile` is a data class (Parcelable) representing the UI state of a Quick Settings tile. It defines the icon, label, and visual state (on/off/unavailable) shown to the user.

## Data Model

### Visual Fields
*   **`mIcon`**: `Icon` - The primary image. Should be white on transparent.
*   **`mLabel`**: `CharSequence` - Primary text.
*   **`mSubtitle`**: `CharSequence` - Secondary text (optional).
*   **`mContentDescription`**: `CharSequence` - Accessibility label.
*   **`mStateDescription`**: `CharSequence` - Accessibility state (e.g., "Connected to Home WiFi").

### Interaction Fields
*   **`mState`**: `int` - The visual state.
    *   `STATE_ACTIVE` (2): Tile is "on" (usually colored background).
    *   `STATE_INACTIVE` (1): Tile is "off" (usually grey background).
    *   `STATE_UNAVAILABLE` (0): Tile cannot be used (greyed out, not clickable).
*   **`mPendingIntent`**: `PendingIntent` - If set, the system will launch this intent on click instead of calling `TileService.onClick()`.

## API Reference

### Setters/Getters
*   `getState()`, `setState(int)`
*   `getIcon()`, `setIcon(Icon)`
*   `getLabel()`, `setLabel(CharSequence)`
*   `setActivityLaunchForClick(PendingIntent)`

### Persistence
*   **`updateTile()`**: Mandatory call to send the current local state of this object to the System UI process via `IQSService`.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Custom serialization for `Icon` and `PendingIntent`. Uses `TextUtils.writeToParcel` for char sequences.
*   **C++**: `android::Parcelable`.
    *   `Icon` and `PendingIntent` have C++ equivalents in the framework.
    *   `CharSequence` typically maps to `std::u16string` or `String16`.

## Implementation Notes
*   **Staleness**: The `Tile` object in `TileService` is a local copy. It is only updated from the system during `onBind`. The service must push changes back using `updateTile()`.
*   **Accessibility**: Proper use of `contentDescription` and `stateDescription` is critical for screen reader support.
