# SwitchPreference - Reverse Engineering Documentation

## Executive Summary
`SwitchPreference` is a two-state preference that uses a `Switch` widget.

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `SwitchPreference` -> `TwoStatePreference`.

## Detailed Functionality
-   **UI**: Displays a `Switch` widget.
-   **Customization**: Supports "on" and "off" text labels on the switch itself.
-   **Listener**: Listens to switch toggle events.

## API Reference
-   `setSwitchTextOn(...)`, `setSwitchTextOff(...)`

## Java-to-C++ Translation Guide
-   **Widget**: Switch/Toggle control.
