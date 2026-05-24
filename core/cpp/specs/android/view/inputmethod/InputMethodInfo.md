# InputMethodInfo - Reverse Engineering Documentation

## Executive Summary
Metadata about an installed Input Method (IME). Parsed from XML.

## Data Model
*   `mId`: Unique ID (Component Name).
*   `mSettingsActivityName`.
*   `mSubtypes`: List of `InputMethodSubtype`.
*   Flags: `mIsAuxIme`, `mSupportsStylusHandwriting`, etc.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
