# ActionBar - Reverse Engineering Documentation

## Executive Summary
`ActionBar` is a primary toolbar component within an Activity that displays the activity title, navigation modes, and interactive items. It serves as a central point for user interaction and navigation. While largely replaced by `Toolbar` in modern Android development, it remains a fundamental abstract base class in the framework.

## Architecture Overview
*   **Inheritance**: `public abstract class ActionBar`
*   **Package**: `android.app`
*   **Key Relationships**:
    *   Associated with an `Activity` and `Window`.
    *   Manages `FragmentTransaction` for tab navigation (deprecated).
    *   Uses `Drawable` for icons and backgrounds.
    *   Uses `View` for custom layouts.

## Detailed Functionality

### Display Options Management
**Purpose**: Controls the appearance of the action bar (title, logo, home button, etc.).
**Mechanism**: Uses bit flags (`DISPLAY_USE_LOGO`, `DISPLAY_SHOW_HOME`, etc.) manipulated via `setDisplayOptions`.

### Navigation Modes (Deprecated)
**Purpose**: Provided Standard, List, and Tab navigation.
**Status**: Deprecated in favor of other navigation patterns.
**Components**:
*   `NavigationMode`: Integer definition.
*   `Tab`: Abstract class for tab operations.
*   `TabListener`: Interface for tab events.

### Custom View
**Purpose**: Allows embedding arbitrary views (e.g., search bars) into the toolbar.
**Mechanism**: `setCustomView(View)` or `setCustomView(int layoutResId)`. Controlled by `LayoutParams` for gravity.

### Styling
**Purpose**: Manages backgrounds, icons, and text visibility.
**Mechanism**:
*   `setBackgroundDrawable`, `setStackedBackgroundDrawable`, `setSplitBackgroundDrawable`.
*   `setIcon`, `setLogo`.
*   `setTitle`, `setSubtitle`.

### Home/Up Navigation
**Purpose**: Handles the "Up" button behavior.
**Mechanism**: `setDisplayHomeAsUpEnabled`, `setHomeButtonEnabled`, `setHomeAsUpIndicator`.

## Data Model

### `ActionBar.LayoutParams`
*   **Inherits**: `ViewGroup.MarginLayoutParams`
*   **Fields**:
    *   `gravity`: Integer (Gravity flags) determining position.

### `ActionBar.Tab` (Abstract)
*   **Fields/Properties**:
    *   `position`: Integer.
    *   `icon`: Drawable.
    *   `text`: CharSequence.
    *   `customView`: View.
    *   `tag`: Object.
    *   `contentDescription`: CharSequence.

## API Reference
*   `setCustomView(View)`: Set custom navigation view.
*   `setIcon(int/Drawable)`: Set icon.
*   `setLogo(int/Drawable)`: Set logo.
*   `setTitle(CharSequence/int)`: Set title text.
*   `setSubtitle(CharSequence/int)`: Set subtitle text.
*   `setDisplayOptions(int options, int mask)`: Configure display flags.
*   `show()` / `hide()`: Visibility control.
*   `addTab(Tab)`: Add navigation tab (deprecated).

## Java-to-C++ Translation Guide

### Class Structure
*   Map `ActionBar` to a C++ class `ActionBar`.
*   Since it's abstract, C++ implementation should likely be an interface or base class.

### Types
*   `CharSequence` -> `std::string` or a custom `String` wrapper supporting rich text.
*   `Drawable` -> `android::graphics::drawable::Drawable` (shared pointer).
*   `View` -> `android::view::View` (shared pointer).
*   `Context` -> `android::content::Context`.

### Enums/Constants
*   Map `DISPLAY_` constants to a C++ `enum class` or `bitmask`.
*   Map `NAVIGATION_MODE_` constants to `enum class`.

### Memory Management
*   Java relies on GC. C++ implementation must use smart pointers (`std::shared_ptr`) for Views and Drawables to manage lifecycle, especially for `Tab` objects which hold references to Views.

## Implementation Risks
*   **Deprecation**: Many methods are deprecated. C++ implementation needs to decide whether to support legacy behavior or focus on modern equivalents.
*   **UI Threading**: Modifications must happen on the UI thread.
*   **Resource Resolution**: Requires access to Android Resource system for `ResId` overloads.
