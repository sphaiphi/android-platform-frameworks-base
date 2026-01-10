# NightDisplayListener - Reverse Engineering Documentation

## Executive Summary
`NightDisplayListener` is a helper class for clients to listen for changes to Night Light settings (Secure Settings). It wraps a `ContentObserver`.

## Architecture Overview
- **Type**: Listener / Helper.
- **Mechanism**: Observes `Settings.Secure` URIs.
- **Dependencies**: `ColorDisplayManager` (to fetch values), `ContentResolver`.

## Detailed Functionality
- Listens to:
    - `NIGHT_DISPLAY_ACTIVATED`
    - `NIGHT_DISPLAY_AUTO_MODE`
    - `NIGHT_DISPLAY_CUSTOM_START_TIME`
    - `NIGHT_DISPLAY_CUSTOM_END_TIME`
    - `NIGHT_DISPLAY_COLOR_TEMPERATURE`
- Dispatches to `Callback` interface.

## Java-to-C++ Translation Guide
- **ContentObserver**: Native code observes settings via `IContentObserver`.
- **Usage**: Only needed if the C++ component needs to react to user settings changes regarding Night Light.
