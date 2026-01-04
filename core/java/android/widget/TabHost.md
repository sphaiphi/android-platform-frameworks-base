# TabHost - Reverse Engineering Documentation

## Executive Summary
`TabHost` is a container for a tabbed window view. It manages a `TabWidget` (the tabs) and a `FrameLayout` (the content). It handles switching between tabs and showing the correct content.

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `TabHost`.
*   **Deprecated**: Superseded by `TabLayout` / `ViewPager`.
*   **Components**:
    *   `TabWidget`: Displays indicators.
    *   `FrameLayout mTabContent`: Displays pages.
    *   `TabSpec`: Configuration for a tab (Indicator + Content Strategy).

## Detailed Functionality

### 1. TabSpec
*   **Indicator Strategy**: How to draw the tab (Label, Icon, or Custom View).
*   **Content Strategy**: How to create content (View ID, `TabContentFactory`, or `Intent`).

### 2. Setup
*   **`setup()`**: Finds standard views (`android.R.id.tabs`, `android.R.id.tabcontent`).
*   **`addTab`**: Adds indicator to `TabWidget` and stores spec.

### 3. Navigation
*   **Focus**: Handles keyboard navigation (D-pad) moving focus between tabs and content.
*   **Selection**: `setCurrentTab` updates `TabWidget` focus and visibility of content views.

## Java-to-C++ Translation Guide
*   **Container**: Standard composition.
*   **LocalActivityManager**: The `Intent` content strategy embeds *Activities* inside the view. This is very Android-specific and likely deprecated/unnecessary in a modern C++ UI engine (replace with Fragments/Child Controllers).

## Implementation Risks
*   **Focus**: Managing focus transitions between the tab strip and the content area is tricky.
