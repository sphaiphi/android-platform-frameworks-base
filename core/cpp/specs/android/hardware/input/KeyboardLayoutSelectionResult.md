# KeyboardLayoutSelectionResult - Reverse Engineering Documentation

## Executive Summary
`KeyboardLayoutSelectionResult` holds the result of a keyboard layout query, including the selected layout descriptor and the criteria used to select it (User, Device, IME, etc.).

## Architecture Overview
- **Data Class**: Generated via `DataClass`.
- **Parcelable**.

## Detailed Functionality
- `mLayoutDescriptor`: The selected layout ID (String).
- `mSelectionCriteria`: Int enum (`USER`, `DEVICE`, `VIRTUAL_KEYBOARD`, `DEFAULT`, `UNSPECIFIED`).

## API Reference
- `getLayoutDescriptor()`
- `getSelectionCriteria()`

## Java-to-C++ Translation Guide
- Struct with `std::string` and `enum`.

## Implementation Risks
- None.
