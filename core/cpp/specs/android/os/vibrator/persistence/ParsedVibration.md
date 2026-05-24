# ParsedVibration - Reverse Engineering Documentation

## Executive Summary
`ParsedVibration` is an opaque container for the result of an XML parse operation. It holds one or more `VibrationEffect`s. It allows for "resolving" the best effect for a specific vibrator from a list of options (e.g., if the XML contained a `<vibration-select>` block).

## Architecture Overview
-   **Pattern**: Container / Resolver.
-   **Data**: `List<VibrationEffect>`.

## API Reference
-   `resolve(Vibrator)` / `resolve(VibratorInfo)`: Iterates through the list and returns the *first* effect that the target vibrator supports (`areVibrationFeaturesSupported`).

## Java-to-C++ Translation Guide
-   **Logic**: The resolution logic (first supported wins) is simple but critical for device compatibility (fallback mechanism).
