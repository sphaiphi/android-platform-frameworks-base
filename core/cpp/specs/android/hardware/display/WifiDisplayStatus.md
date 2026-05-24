# WifiDisplayStatus - Reverse Engineering Documentation

## Executive Summary
`WifiDisplayStatus` is a snapshot of the global Wi-Fi Display state. It includes the feature state (On/Off), scan state, active connection status, and lists of known displays.

## Data Model
- `mFeatureState`: Unavailable, Disabled, Off, On.
- `mScanState`: Not Scanning, Scanning.
- `mActiveDisplayState`: Not Connected, Connecting, Connected.
- `mActiveDisplay`: `WifiDisplay` (nullable).
- `mDisplays`: `WifiDisplay[]` (Available/Remembered peers).
- `mSessionInfo`: `WifiDisplaySessionInfo`.

## Java-to-C++ Translation Guide
- **Parceling**: Writes integers for states, then `ActiveDisplay` (presence flag + object), then Array of displays, then SessionInfo.
