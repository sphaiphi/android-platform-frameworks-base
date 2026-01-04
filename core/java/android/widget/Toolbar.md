# Toolbar - Reverse Engineering Documentation

## Executive Summary
`Toolbar` is a flexible generalization of the `ActionBar` pattern, designed to be used at any level of a view hierarchy. It manages a complex internal layout consisting of navigation buttons, logos, titles/subtitles, custom views, and an `ActionMenuView`. It supports RTL layouts, content insets, and expanded action views (search bars).

## Architecture Overview
- **Inheritance**: Extends `android.view.ViewGroup`.
- **Role**: A top-level or nested navigational and action container.
- **Key Components**:
    - `ActionMenuView`: Manages the overflow and action buttons.
    - `TextView` (Title/Subtitle): Managed internally for branding and context.
    - `ImageButton` (Navigation/Collapse): Standardized entry points for "Up" or "Close".
    - `DecorToolbar`: Implemented via `ToolbarWidgetWrapper` to allow `Toolbar` to act as an `ActionBar`.
- **Layout Logic**: Custom `onMeasure` and `onLayout` implementations to handle complex positioning of system and custom views.

## Detailed Functionality

### Component Management
**Purpose**: Lazy instantiation and dynamic management of internal views.
**Algorithm**:
- **Titles**: `setTitle()` checks if `mTitleTextView` exists; if not, it's created with appropriate styling and added as a "System View".
- **Navigation**: `setNavigationIcon()` creates `mNavButtonView`.
- **Menu**: `ensureMenu()` sets up the `ActionMenuView` and attaches an `ExpandedActionViewMenuPresenter`.

### Expanded Action Views
**Purpose**: Supports expanding a `MenuItem` into a full-width view (e.g., a search bar).
**Algorithm**:
1.  A `MenuItem` with `SHOW_AS_ACTION_COLLAPSE_ACTION_VIEW` is clicked.
2.  `mExpandedMenuPresenter` intercepts the expansion.
3.  Toolbar hides all other system views (titles, navigation, etc.) and adds the `MenuItem`'s action view.
4.  A collapse button is added to return to the normal state.

### Content Insets (`RtlSpacingHelper`)
**Purpose**: Manages margins for the toolbar content to align with app gridlines.
**Algorithm**:
- Supports relative (`start`, `end`) and absolute (`left`, `right`) insets.
- Values are adjusted based on the layout direction (LTR vs RTL).
- Insets can be increased when a navigation button or action menu is present (`contentInsetStartWithNavigation`).

### Touch Handling
- **`onTouchEvent`**: Toolbar is designed to "eat" touch events. If a child doesn't handle a touch, the Toolbar returns `true` to ensure the gesture isn't passed through to views behind it.

## Layout Logic (`onMeasure` / `onLayout`)
- **Measurement Priority**:
    1.  Navigation Button.
    2.  Collapse Button.
    3.  Action Menu.
    4.  Content Insets.
    5.  Expanded Action View / Logo.
    6.  Custom Views.
    7.  Title / Subtitle.
- **Collapsing**: If `mCollapsible` is true and no children are visible, the Toolbar measures to height 0.
- **Gravity**: Supports `buttonGravity` (Top, Bottom, Center) to align internal buttons independently of the overall toolbar gravity.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mMenuView` | `ActionMenuView` | Container for action buttons. |
| `mTitleTextView` | `TextView` | The primary label. |
| `mNavButtonView` | `ImageButton` | The start-side navigation icon. |
| `mContentInsets`| `RtlSpacingHelper`| Logic for start/end padding management. |
| `mExpandedActionView`| `View` | The view currently taking over the toolbar. |
| `mHiddenViews` | `List<View>` | List of views temporarily removed during expansion. |

## API Reference
- `setTitle(CharSequence)` / `setSubtitle(CharSequence)`: Set branding text.
- `setNavigationIcon(Drawable)` / `setNavigationOnClickListener(OnClickListener)`: Setup navigation.
- `inflateMenu(int)` / `getMenu()`: Manage actions.
- `setLogo(Drawable)`: Sets a branding image.
- `collapseActionView()`: Manages search/expanded states.

## Java-to-C++ Translation Guide

### View Hierarchy
- **ViewGroup**: Translates to a native container. In C++, implement a custom layout pass in `onMeasure`/`onLayout` following the "System View" vs "Custom View" priority logic.
- **ContextThemeWrapper**: Used for `mPopupContext`. In C++, ensure the menu inflation system can accept an override theme/style.

### Menu System
- **MenuBuilder / MenuPresenter**: These are complex AIDL/Java classes. The C++ implementation needs a native Menu framework that supports the Observer pattern for item expansion and clicks.

### RTL Support
- **RtlSpacingHelper**: Port this logic directly to handle start/end vs left/right margins. Use the current layout direction from the native `Configuration`.

## Implementation Risks
- **Measurement Complexity**: The interaction between `minHeight`, `maxButtonHeight`, and `titleMargin` is complex. Jitter or overlapping views are common if the `onLayout` logic isn't pixel-perfect.
- **Expanded Views**: Transitioning between the normal state and an expanded state requires careful management of view visibility. Ensure that views added via `addView` (Custom) are distinguished from views managed by the Toolbar (System).
- **Accessibility**: Toolbars are critical for screen readers. Ensure `navigationContentDescription` and `logoDescription` are properly mapped to native accessibility properties.
