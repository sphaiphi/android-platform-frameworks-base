# AlertDialog - Reverse Engineering Documentation

## Executive Summary
`AlertDialog` is a concrete subclass of `Dialog` capable of displaying a title, message, and up to three buttons (Positive, Negative, Neutral). It can also host a custom view or a list of selectable items. It delegates most of its UI construction and logic to `AlertController`.

## Architecture Overview
*   **Inheritance**: `Dialog` -> `DialogInterface`.
*   **Delegation**: Uses `AlertController` (internal class) to handle the heavy lifting of view binding and layout.
*   **Builder Pattern**: Includes a static inner class `Builder` for fluent API construction.

## Detailed Functionality

### UI Composition
**Purpose**: Display standard dialog elements.
**Components**:
*   Title (Text or Custom View).
*   Message (Text).
*   Buttons (1-3).
*   Content Area (Custom View, ListView for single/multi-choice).
*   Icon.

### Theme Resolution
**Purpose**: Select appropriate visual style (Traditional, Holo, Material, DeviceDefault).
**Mechanism**: `resolveDialogTheme` static method checks resource ID and attributes (`R.attr.alertDialogTheme`).

### Interaction Handling
**Purpose**: Handle user input.
**Events**:
*   Button clicks (`OnClickListener`).
*   List item clicks (`OnMultiChoiceClickListener` etc.).
*   Key events (`onKeyDown`, `onKeyUp`).

## Data Model
*   `mAlert`: `AlertController`. Holds the state and logic.

## API Reference
*   `setTitle`, `setMessage`, `setIcon`.
*   `setButton(int which, CharSequence text, OnClickListener listener)`.
*   `setView(View)`.
*   `getButton(int)`, `getListView()`.

### Builder Class
*   Methods: `setTitle`, `setMessage`, `setPositiveButton`, `setNegativeButton`, `setNeutralButton`, `setItems`, `setAdapter`, `setMultiChoiceItems`, `setSingleChoiceItems`, `create`, `show`.

## Java-to-C++ Translation Guide

### AlertController dependency
*   `AlertDialog` is mostly a wrapper. The core logic resides in `AlertController` (com.android.internal.app). This dependency must be resolved—either by implementing `AlertController` in C++ or merging logic if `AlertController` isn't exposed.

### Builder Pattern
*   Standard C++ Builder pattern implementation.
*   Store parameters in a struct (`AlertParams`) and pass to `AlertDialog` constructor or `create()` method.

### Callbacks
*   Use `std::function` or interface classes for `OnClickListener`.

## Implementation Risks
*   **Theme/Style Complexity**: Android's theming system for Dialogs is complex (resolving attributes). C++ implementation might need a simplified styling mechanism if the full Resource/Theme engine isn't available.
*   **ListView Binding**: Supporting Cursors and Adapters in C++ requires a corresponding Adapter architecture.
