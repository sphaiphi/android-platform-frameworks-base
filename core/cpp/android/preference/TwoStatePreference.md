# TwoStatePreference - Reverse Engineering Documentation

## Executive Summary
`TwoStatePreference` is an abstract base class for preferences that have a boolean state (checked/unchecked).

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `TwoStatePreference` -> `Preference`.
- **Persistance**: Boolean.

## Detailed Functionality
-   **State**: `setChecked`, `isChecked`.
-   **Persistence**: Persists boolean.
-   **Summary**: Supports dynamic summary based on state (`summaryOn`, `summaryOff`).
-   **Dependencies**: Can disable dependents based on state (`disableDependentsState`).

## API Reference
-   `setChecked(boolean)`, `isChecked()`
-   `setSummaryOn(...)`, `setSummaryOff(...)`
-   `setDisableDependentsState(boolean)`

## Java-to-C++ Translation Guide
-   **Logic**: Core logic for any toggle-able preference.
