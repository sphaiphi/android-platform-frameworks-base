# TimePickerSpinnerDelegate - Reverse Engineering Documentation

## Executive Summary
`TimePickerSpinnerDelegate` is a concrete implementation of the `TimePicker.TimePickerDelegate` interface. It provides the "spinner" style UI for picking time, utilizing `NumberPicker` widgets for hour, minute, and AM/PM selection. This delegate handles the logic for 12-hour vs 24-hour modes, localization of time formats, and synchronizing the UI state with the internal time model.

## Architecture Overview
- **Inheritance**: Extends `TimePicker.AbstractTimePickerDelegate`.
- **Composition**:
    - Owns and manages three `NumberPicker` instances (Hour, Minute, AM/PM) or two `NumberPicker`s and a `Button` (Legacy AM/PM).
    - Uses `Calendar` for time calculations and localization.
- **Key Relationships**:
  - **Delegator**: Attached to a `TimePicker` view (the `mDelegator`).
  - **UI**: Inflates a layout (typically `R.layout.time_picker_legacy`) into the delegator.
  - **Localization**: Relies heavily on `android.text.format.DateFormat` and `java.util.Calendar`.

## Detailed Functionality

### Initialization (`TimePickerSpinnerDelegate` Constructor)
**Purpose**: Sets up the UI and initial state.
**Algorithm**:
1.  **Style Attributes**: Reads `R.styleable.TimePicker` to find the layout resource (default `R.layout.time_picker_legacy`).
2.  **Inflation**: Inflates the layout into the `mDelegator`.
3.  **Component Binding**: Finds `NumberPicker`s for Hour and Minute.
4.  **AM/PM Logic**:
    - Detects if the AM/PM control is a `Button` or a `NumberPicker` based on the inflated layout.
    - Sets up listeners to toggle `mIsAm` state.
5.  **Reordering**: Checks `isAmPmAtStart()` (based on locale). If true, moves the AM/PM view to the start of the layout container.
6.  **Formatting**: Calls `getHourFormatData()` to determine if hours should be 2-digits and what character ('H', 'h', 'K', 'k') represents the hour pattern.
7.  **Initial State**: Updates controls and sets the time to the current time via `Calendar.getInstance()`.

### Time Selection Logic
- **Listeners**: `NumberPicker.OnValueChangeListener` are attached to spinners.
- **Hour Change**:
    - Updates `mIsAm` if the value crosses the 11->12 or 12->11 boundary in 12-hour mode.
    - Calls `onTimeChanged()`.
- **Minute Change**:
    - Detects rollover (59->0 or 0->59) and increments/decrements the hour.
    - Updates `mIsAm` if the hour rollover crosses the noon/midnight boundary.
- **AM/PM Change**:
    - Toggles `mIsAm`.
    - Updates controls.

### Mode Switching (`setIs24Hour`)
**Purpose**: Toggles between 12-hour and 24-hour views.
**Algorithm**:
1.  Cache current hour (normalized).
2.  Update `mIs24HourView` flag.
3.  Recalculate format data (`getHourFormatData()`).
4.  Update `NumberPicker` ranges (0-23 for 24h, 1-12/0-11 for 12h).
5.  Restore the cached hour into the new format.
6.  Show/Hide AM/PM control.

### Localization & Formatting
- **Divider**: logic in `setDividerText()` extracts the separator char (usually ':') from the `bestDateTimePattern` for the locale.
- **Hour Format**: `getHourFormatData()` parses `DateFormat.getBestDateTimePattern` to find the hour char:
    - 'H': 0-23
    - 'k': 1-24
    - 'K': 0-11 (12-hour)
    - 'h': 1-12 (12-hour)

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mHourSpinner` | `NumberPicker` | Selector for hours. |
| `mMinuteSpinner` | `NumberPicker` | Selector for minutes. |
| `mAmPmSpinner` | `NumberPicker` | Selector for AM/PM (if spinner style). Nullable. |
| `mAmPmButton` | `Button` | Toggle for AM/PM (if button style). Nullable. |
| `mIs24HourView` | `boolean` | True if in 24-hour mode. |
| `mIsAm` | `boolean` | True if time is AM. Only relevant in 12-hour mode logic. |
| `mHourFormat` | `char` | The pattern character for hours ('H', 'h', 'K', 'k'). |
| `mTempCalendar` | `Calendar` | Reused instance for accessibility text generation. |

## API Reference
(Inherited from `TimePicker.AbstractTimePickerDelegate`)
- `setHour(int hour)`: Sets the current hour (0-23).
- `getHour()`: Returns the current hour (0-23).
- `setMinute(int minute)`: Sets the current minute (0-59).
- `getMinute()`: Returns the current minute.
- `setIs24Hour(boolean)`: Sets the display mode.
- `is24Hour()`: Returns true if 24-hour mode is active.
- `validateInput()`: Always returns true for this delegate.
- `setEnabled(boolean)`: Enables/disables all child spinners and buttons.

## Java-to-C++ Translation Guide

### UI Components
- **NumberPicker**: This is a complex custom view. The C++ UI framework must have an equivalent wheel/spinner widget or one must be implemented.
- **Inflation**: The dynamic inflation of XML layouts (`LayoutInflater`) needs to be replaced by explicit view creation code or a C++ UI builder pattern.

### Localization
- **DateFormat**: The logic heavily relies on `android.text.format.DateFormat.getBestDateTimePattern`.
    - *C++ Requirement*: Need an ICU wrapper or a `std::locale` based mechanism to get the localized time pattern strings (skeletons like "hm" or "Hm").
    - *Parsing*: The logic that parses the returned pattern string to find 'H', 'h', separators, etc., must be ported to C++ string manipulation.

### State Management
- **Calendar**: `java.util.Calendar` usage for `HOUR_OF_DAY` vs `HOUR` logic needs to be mapped to `std::chrono` or a struct `tm` based helper.
- **Auto-Rollover**: The logic where minutes rolling over changes the hour is manual here. Ensure this business logic is preserved.

### Event Handling
- **InputMethodManager**: The `updateInputState()` method interacts with the soft keyboard (hiding it when focus changes). This platform-specific behavior might need abstraction in C++.

## Implementation Risks
- **Locale Complexity**: Parsing date format strings is fragile. Different locales might return patterns that the simple parser in `setDividerText` or `getHourFormatData` handles poorly if not exactly matching expectations.
- **Legacy Layouts**: The code handles two different UI structures (Button vs Spinner for AM/PM). C++ implementation should decide if it supports both or standardizes on one.
- **Off-by-one Errors**: Converting between 0-11, 1-12, 0-23, and 1-24 hour formats is error-prone. Strict unit tests are needed for the `getHour()` / `setHour()` conversion logic.
