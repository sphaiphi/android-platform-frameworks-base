# SpellCheckerSubtype - Reverse Engineering Documentation

## Executive Summary
Represents a specific locale or mode supported by a Spell Checker.

## Data Model
*   **Attributes**: Locale, Language Tag, Extra Value (key-value pairs string), ID.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Map Parsing**: "key=value,key2=value2" parsing logic for extras.
