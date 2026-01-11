# ProgressDialog - Reverse Engineering Documentation

## Executive Summary
`ProgressDialog` is a specialized `AlertDialog` that displays a progress bar and an optional text message. It can show either a circular spinner (indeterminate) or a horizontal bar (determinate). It is designed to block user interaction during a long-running task. It is deprecated in favor of embedding a `ProgressBar` directly in the UI or using a `Notification`.

## Architecture Overview
- **Inheritance**: Extends `AlertDialog`.
- **Core Components**:
    - `ProgressBar mProgress`: The actual progress widget.
    - `TextView mMessageView`: Displays the descriptive message.
    - `Handler mViewUpdateHandler`: Manages UI updates for the horizontal progress style to ensure they happen on the correct thread.
- **Styles**:
    - `STYLE_SPINNER` (Default): Circular animation for unknown duration.
    - `STYLE_HORIZONTAL`: Linear bar for known progress (0 to `max`).

## Detailed Functionality

### onCreate(Bundle savedInstanceState)
**Purpose**: Initializes the dialog layout based on the selected style.
**Algorithm**:
1. Inflates either `alert_dialog_progress` (horizontal) or `progress_dialog` (spinner) based on `mProgressStyle`.
2. Locates the `ProgressBar` and `TextView` widgets.
3. If horizontal, sets up a `mViewUpdateHandler` to refresh the "X/Y" text and "%" labels.
4. Applies all previously set values (Max, Progress, Message, etc.) to the initialized views.

### Progress Updates
**Purpose**: Updates the visual state of the bar.
**Mechanism**: 
- `setProgress(int value)`: Updates the primary progress. If the dialog has started, it directly updates the widget and triggers a refresh of the text labels.
- `setIndeterminate(boolean indeterminate)`: Toggles between known and unknown progress states.

### Thread Safety
**Purpose**: Ensures UI updates are valid.
**Logic**: Uses `mViewUpdateHandler` to post messages for text updates (progress number and percentage) to the main thread, as these are calculated values derived from the widget's state.

## API Reference
- `public static ProgressDialog show(...)`: Static helper to create and display a dialog in one call.
- `public void setProgressStyle(int style)`: Configures the dialog type.
- `public void setProgress(int value)`: Sets current progress.
- `public void setMax(int max)`: Sets the upper bound.
- `public void setIndeterminate(boolean indeterminate)`: Configures indeterminate mode.

## Java-to-C++ Translation Guide
- **Widget Mapping**: Map `ProgressBar` to a native progress component.
- **Handler**: Use a C++ message queue or event loop (e.g., `android::os::Handler`) to handle cross-thread UI updates.
- **String Formatting**: Use `sprintf` or `std::format` (C++20) to replicate the "%1d/%2d" formatting for the progress label.

## Implementation Risks
- **Modality**: Being a modal dialog, it can lead to poor UX if the task hangs. C++ implementation should ensure the cancel button and back key are always responsive.
- **Layout Inflation**: In a native environment, the XML layouts must be replaced with programmatic view construction or a native layout engine.
