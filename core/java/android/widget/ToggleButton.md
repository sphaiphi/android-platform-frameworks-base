# ToggleButton - Reverse Engineering Documentation

## Executive Summary
`ToggleButton` is a specialized `CompoundButton` that displays a checked/unchecked state as a button with text. By default, it displays "ON" and "OFF" text and can include a visual indicator (light) as part of its background drawable. It automatically switches displayed text based on its state.

## Architecture Overview
- **Inheritance**: Extends `android.widget.CompoundButton`.
- **Role**: A binary state selector with explicit text labels.
- **Key Features**:
    - Dual text labels (`textOn`, `textOff`).
    - Support for a "toggle" layer in the background `LayerDrawable`.
    - Automated alpha adjustment when disabled.

## Detailed Functionality

### Text State Synchronization (`syncTextState`)
**Purpose**: Updates the visible text of the button to match the current checked state.
**Algorithm**:
1.  Calls `isChecked()`.
2.  If checked and `mTextOn` is not null, sets the button text to `mTextOn`.
3.  If unchecked and `mTextOff` is not null, sets the button text to `mTextOff`.
4.  This method is called during initialization and whenever `setChecked()` is invoked.

### Indicator Management
**Purpose**: Manages a specific "toggle indicator" drawable if it exists within the background.
**Algorithm**:
1.  **Binding**: In `onFinishInflate` or `setBackgroundDrawable`, it checks if the background is a `LayerDrawable`.
2.  **Lookup**: If it is a `LayerDrawable`, it searches for a layer with ID `com.android.internal.R.id.toggle` and stores a reference in `mIndicatorDrawable`.
3.  **State Change**: In `drawableStateChanged()`, it updates the alpha of `mIndicatorDrawable`:
    - If enabled: 255 (Opaque).
    - If disabled: `255 * mDisabledAlpha`.

### Disabled State Alpha
- **`mDisabledAlpha`**: A float (default 0.5f) defined in XML (`android:disabledAlpha`). It controls how much the indicator drawable fades when the button is disabled.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mTextOn` | `CharSequence` | Label displayed when state is "Checked". |
| `mTextOff` | `CharSequence` | Label displayed when state is "Unchecked". |
| `mIndicatorDrawable` | `Drawable` | Reference to the "toggle" layer in the background. |
| `mDisabledAlpha` | `float` | Alpha multiplier for the indicator when disabled. |

## API Reference
- `setTextOn(CharSequence)` / `getTextOn()`: Sets/gets the "On" label.
- `setTextOff(CharSequence)` / `getTextOff()`: Sets/gets the "Off" label.
- `setDisabledAlpha(float)`: Configures the fading factor.
- `getButtonStateDescription()`: (Internal) Returns the localized "ON"/"OFF" string or the custom labels for accessibility.

## Java-to-C++ Translation Guide

### Layout and Drawables
- **LayerDrawable**: The logic relies on `LayerDrawable.findDrawableByLayerId`. The C++ drawable system must support layered drawables with ID-based lookup to preserve the "indicator light" feature.
- **Resources**: Default strings for "ON" and "OFF" (e.g., `R.string.capital_on`) must be available in the C++ resource manager.

### Property Propagation
- **setChecked**: The C++ implementation must override the equivalent of `setChecked` to trigger the `syncTextState` logic.

### Accessibility
- **State Description**: Ensure that the `getButtonStateDescription()` logic is ported to the native accessibility node provider, so screen readers correctly identify the toggle state using the custom labels.

## Implementation Risks
- **Background Coupling**: The `mIndicatorDrawable` logic is tightly coupled to a specific background structure. If a developer sets a plain color or a simple `BitmapDrawable` as the background, the indicator light feature will be silently disabled (correct behavior, but requires null checks).
- **Text Styling**: `ToggleButton` inherits from `Button`/`TextView`. Ensure that changing the text via `setText` during state sync doesn't inadvertently clear spans or styling if `mTextOn`/`mTextOff` are `SpannableStrings`.
