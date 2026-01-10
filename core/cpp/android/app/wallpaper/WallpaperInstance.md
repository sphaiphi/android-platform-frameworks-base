# WallpaperInstance - Reverse Engineering Documentation

## Executive Summary
`WallpaperInstance` represents a wallpaper that has been actively set as the current wallpaper. It wraps a `WallpaperDescription` and provides stronger guarantees, such as ensuring an ID exists and linking to the specific `WallpaperInfo` (service component info).

## Architecture Overview
- **Package**: `android.app.wallpaper`
- **Implements**: `Parcelable`
- **Role**: Wrapper / State Object.
- **Relationships**:
  - Contains `WallpaperDescription` (mandatory).
  - Contains `WallpaperInfo` (nullable, for live wallpapers).

## Detailed Functionality

### ID Resolution Logic
**Purpose**: Determine the unique ID for this wallpaper instance.
**Algorithm**:
1. Check `mIdOverride` (explicit ID provided at creation).
2. If null, check `mDescription.getId()`.
3. If null, check if `mInfo` exists and use `mInfo.getComponent().flattenToString()`.
4. Fallback to `"default_id"`.

### Comparison Strategy
**Purpose**: Equality checks.
**Logic**:
- Checks equality of `mInfo.getComponent()` (if `mInfo` exists).
- Checks equality of `getId()`.
- Does *not* explicitly check every field of `mDescription` for equality, relying primarily on Component+ID identity.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mInfo` | `WallpaperInfo` | System info about the wallpaper service (nullable). |
| `mDescription` | `WallpaperDescription` | Metadata for this specific instance. |
| `mIdOverride` | `String` | Optional ID forcing mechanism. |

## Java-to-C++ Translation Guide

- **Parcelable**:
  - `WallpaperInfo` is a complex object. Ensure the C++ definition of `WallpaperInfo` is available or treat it as an opaque Parcelable if only passing through.
  - `WallpaperDescription` is flattened into the parcel.
- **ID Logic**: The `getId()` logic is business critical and must be replicated exactly.

## Implementation Risks
- **Null Safety**: Java relies on `Optional` like behavior checks. `mInfo` can be null (static wallpaper). C++ usage must check pointers/optionals rigorously.

## Questions for C++ Team
- Is `WallpaperInfo` fully implemented in C++?
