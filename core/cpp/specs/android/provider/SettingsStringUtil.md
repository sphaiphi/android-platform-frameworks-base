# SettingsStringUtil - Reverse Engineering Documentation

## Executive Summary
`SettingsStringUtil` provides utilities for parsing and serializing colon-delimited string sets used frequently in `Settings` values (e.g., list of enabled input methods).

## Architecture Overview
- **Type**: Utility Class.
- **Inner Classes**:
    -   `ColonDelimitedSet`: Generic set using ":" as a delimiter.
    -   `ComponentNameSet`: Specialization for `ComponentName` objects.
    -   `SettingStringHelper`: Helper to read/write settings and apply modifications.

## Data Model
-   **Delimiter**: ":"

## Java-to-C++ Translation Guide
-   **String Splitting**: Use `std::getline` or similar to split by ':'.
-   **Sets**: `std::unordered_set<std::string>`.
