# TabActivity - Reverse Engineering Documentation

## Executive Summary
`TabActivity` is a specialized `ActivityGroup` that provides a standard UI for managing tabs. It hosts a `TabHost` and a `TabWidget`, allowing users to switch between different embedded activities. It is deprecated in favor of using `Fragment` and `ActionBar.newTab()` (which is also deprecated) or modern components like `TabLayout` and `ViewPager2`.

## Architecture Overview
- **Inheritance**: Extends `ActivityGroup`.
- **Core Components**:
    - `TabHost mTabHost`: The primary container managing the tab logic and view hierarchy.
    - `TabWidget`: The component displaying the actual tab buttons.
- **Management**: Coordinates with the `LocalActivityManager` from its parent class to embed child activities within the tab content area.

## Detailed Functionality

### Initialization (`onContentChanged`)
**Purpose**: Sets up the tab host after the layout has been inflated.
**Algorithm**:
1. Finds the `TabHost` by ID `android.R.id.tabhost`.
2. Calls `mTabHost.setup(getLocalActivityManager())` to link it with the embedded activity lifecycle manager.

### Tab Navigation
**Logic**: 
- `setDefaultTab(String tag)`: Sets the initial tab by name.
- `setDefaultTab(int index)`: Sets the initial tab by position.
- `onPostCreate()`: Ensures that at least one tab is selected (defaulting to 0) if none was set.

### State Persistence
**Mechanism**:
- `onSaveInstanceState()`: Records the currently active tab's tag in the bundle.
- `onRestoreInstanceState()`: Retrieves the saved tag and calls `mTabHost.setCurrentTabByTag(cur)`.

### Child Activity Support
**Logic**: `onChildTitleChanged` updates the text label of the corresponding tab if the embedded activity's title changes.

## API Reference
- `public TabHost getTabHost()`: Returns the hosted controller.
- `public TabWidget getTabWidget()`: Returns the UI widget for tabs.
- `public void setDefaultTab(String tag)`: Configures startup tab.

## Java-to-C++ Translation Guide
- **Container UI**: Map `TabHost` to a native tab container that manages a stack of sub-views or sub-components.
- **Embedded Lifecycle**: Use the C++ `LocalActivityManager` equivalent to drive the lifecycle of the components within each tab.
- **Event Handling**: Map tab selection changes to a signal/slot or callback system.

## Implementation Risks
- **Visual Glitches**: Ensuring that the content area correctly resizes and renders the embedded activity window/surface is complex in native code.
- **Lifecycle Overlap**: Multiple activities remain "alive" but paused in other tabs. C++ implementation must manage resource consumption for these hidden components.
