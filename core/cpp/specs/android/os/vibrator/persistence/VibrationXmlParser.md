# VibrationXmlParser - Reverse Engineering Documentation

## Executive Summary
`VibrationXmlParser` deserializes `VibrationEffect` objects from an XML format. This allows vibration patterns to be defined in resource files (XSD schema compliant) rather than hardcoded in code. It supports both single effects and effect selectors.

## Architecture Overview
-   **Pattern**: XML Parser (Pull Parser).
-   **Dependencies**: `TypedXmlPullParser`, `VibrationEffectXmlParser` (internal).
-   **MIME Type**: `application/vnd.android.haptics.vibration+xml`.

## Supported Tags
-   `<vibration-effect>`: Root for single effect.
-   `<vibration-select>`: Root for a list of effects.
-   `<predefined-effect name="...">`: Maps to `PrebakedSegment`.
-   `<waveform-effect>`: Maps to `Waveform` (Ramp/Step segments).
-   `<primitive-effect name="..." scale="...">`: Maps to `PrimitiveSegment`.

## API Reference
-   `parse(InputStream)`: Returns `ParsedVibration`.
-   `parseVibrationEffect(InputStream)`: Returns single `VibrationEffect`.

## Java-to-C++ Translation Guide
-   **XML Parsing**: Android C++ uses `libxml2` or `XmlPullParser` equivalents in native code (often `TinyXML` or internal parsers).
-   **Schema**: The parsing logic (attribute names, tag structure) must be strictly identical to read the same files.
-   **Internal Delegate**: Note usage of `com.android.internal.vibrator.persistence.*`. Much of the heavy lifting is in internal classes not shown here, implying the parser logic is complex.

## Implementation Risks
-   **Schema Drift**: If the C++ parser isn't updated alongside the Java one (or the XSD), XMLs valid in Java might fail in native (or vice versa).
