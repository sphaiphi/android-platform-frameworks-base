# TtsEngines - Reverse Engineering Documentation

## Executive Summary
`TtsEngines` is a support class for querying and managing installed TTS engines on the device. It handles engine discovery via `PackageManager`, ranking engines by priority (system vs. user), and managing user preferences for locales and default engines.

## Detailed Functionality

### Engine Discovery
- Queries the system for services handling `android.intent.action.TTS_SERVICE`.
- Ranks engines: System engines have higher priority than non-system engines. Within those groups, priority is determined by the `priority` field in the `ResolveInfo`.

### Locale Management
- Handles the conversion between "old-style" locale strings (e.g., "eng-usa") and modern `Locale` objects.
- `normalizeTTSLocale`: Converts 3-letter ISO codes to 2-letter codes for standard `Locale` compatibility.
- `getLocalePrefForEngine`: Retrieves the user's preferred locale for a specific engine from `Settings.Secure.TTS_DEFAULT_LOCALE`.

### Settings Integration
- Reads/writes to `Settings.Secure.TTS_DEFAULT_SYNTH` and `TTS_DEFAULT_LOCALE`.
- Handles comma-separated lists of engine-specific settings (e.g., `engine1:locale1,engine2:locale2`).

## Java-to-C++ Translation Guide

### Package Manager Interaction
- Requires interaction with the Android `PackageManager` (likely via Binder) to find installed services and read meta-data.

### String Processing
- Replicate the parsing logic for the comma-separated settings list.
- Ensure locale normalization logic matches the Java behavior to avoid mismatches in engine selection.
