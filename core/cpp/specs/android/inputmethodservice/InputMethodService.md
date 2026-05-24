# InputMethodService - Reverse Engineering Documentation

## Executive Summary
`InputMethodService` (IMS) is the central class for implementing an IME in Android. It manages the lifecycle, window, UI (Input View, Candidates View), and interaction with the InputMethodManager and the target application. It handles complex states like fullscreen mode, extracted text mode, and stylus handwriting.

## Architecture Overview
*   **Inheritance**: `AbstractInputMethodService`.
*   **Key Components**:
    *   `SoftInputWindow`: The main window.
    *   `InputMethodImpl`: Implementation of `InputMethod` interface.
    *   `InputMethodSessionImpl`: Implementation of `InputMethodSession`.
    *   `NavigationBarController`: Manages nav bar rendering.
    *   `InlineSuggestionSessionController`: Manages Autofill suggestions.
    *   `InkWindow`: For handwriting.

## Detailed Functionality

### Lifecycle (`onCreate`, `onDestroy`, `initViews`)
*   **Creation**:
    *   Applies theme.
    *   Creates `SoftInputWindow`.
    *   Inflates standard layout (`com.android.internal.R.layout.input_method`).
    *   Initializes `NavigationBarController` and `InlineSuggestionSessionController`.
*   **Views**:
    *   `mFullscreenArea`, `mExtractFrame`, `mCandidatesFrame`, `mInputFrame`.
    *   Standard layout places candidates above input. Extract view fills top in fullscreen.

### Input Lifecycle (`startInput`, `onStartInput`)
*   **Bind**: `onBindInput`.
*   **Start**: `onStartInput` -> `doStartInput`.
    *   Restarts input connection.
    *   Updates fullscreen mode logic (`updateFullscreenMode`).
    *   Calls `onStartInputView` if view is shown.

### Window Management
*   **Show/Hide**: `showWindow`, `hideWindow`.
    *   Manages visibility of `mWindow`.
    *   Updates `mDecorViewVisible`, `mWindowVisible`.
    *   Calls `onWindowShown`, `onWindowHidden`.
*   **Insets**: `onComputeInsets` allows IME to specify content/visible/touchable insets to the WindowManager (determines how app resizes/pans).

### Fullscreen / Extracted Mode
*   **Logic**: `onEvaluateFullscreenMode`. Default: true if landscape.
*   **Extraction**:
    *   `onCreateExtractTextView`: Creates `ExtractEditText`.
    *   `updateExtractingVisibility`: Shows/hides extract frame.
    *   Syncs text between `ExtractEditText` and target app.

### Stylus Handwriting
*   **APIs**: `onStartStylusHandwriting`, `onFinishStylusHandwriting`.
*   **Mechanism**:
    *   Creates `InkWindow`.
    *   Capture events via `InputEventReceiver` on the passed `InputChannel`.
    *   Dispatches events to `InkWindow`.

### Navigation Bar
*   **Logic**: `mNavigationBarController` handles drawing the Back and IME Switcher buttons if the device supports IME-rendered nav bar (gestural nav).

## Data Model
*   `mInputBinding`, `mInputConnection`: Current connection.
*   `mInputEditorInfo`: Current field info.
*   `mTmpInsets`: Insets buffer.
*   `mTheme`: Current theme resource.

## API Reference
*   **Overridable**: `onCreateInputView`, `onCreateCandidatesView`, `onStartInput`, `onFinishInput`, `onUpdateSelection`, `onKeyDown`, `onEvaluateFullscreenMode`.
*   **Control**: `requestShowSelf`, `requestHideSelf`, `switchInputMethod`.

## Java-to-C++ Translation Guide
*   **Complexity**: This is a massive class. It should be broken down.
*   **Windowing**: Heavy reliance on `Dialog` / `Window`. C++ needs equivalent Surface/Window management.
*   **Input**: `InputConnection` interaction is central.
*   **Resources**: Layout inflation is heavy in Java. C++ might need manual view construction or a UI toolkit.

## Test Cases & Validation
*   **Basic**: Show/Hide keyboard. Type text.
*   **Lifecycle**: Switch apps. Verify `onFinishInput` / `onStartInput`.
*   **Fullscreen**: Rotate to landscape. Verify extract view appears.
*   **Handwriting**: Trigger stylus input. Verify `InkWindow` appears.

## Implementation Risks
*   **State Management**: Many boolean flags (`mInputStarted`, `mInputViewStarted`, `mWindowVisible`, etc.). easy to get out of sync.
*   **Concurrency**: Binder callbacks vs Main thread.
