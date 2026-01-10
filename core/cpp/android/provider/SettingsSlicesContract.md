# SettingsSlicesContract - Reverse Engineering Documentation

## Executive Summary
`SettingsSlicesContract` defines the contract for accessing Settings Slices (interactive UI snippets from Settings) via `SliceProvider`.

## Architecture Overview
- **Authority**: `android.settings.slices`.
- **Base URI**: `content://android.settings.slices`.

## Detailed Functionality
-   **Paths**:
    -   `action`: Inline controls (toggles, sliders).
    -   `intent`: Intent-based navigation.
-   **Keys**: `wifi`, `bluetooth`, `location`, `airplane_mode`, `battery_saver`.

## Java-to-C++ Translation Guide
-   **URI Construction**: `content://android.settings.slices/action/wifi`, etc.
