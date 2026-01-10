# SaveRequest - Reverse Engineering Documentation

## Executive Summary
`SaveRequest` carries the data for `onSaveRequest`. It contains the state of the screen (`FillContext`s) when the save was triggered, allowing the service to extract user-entered data.

## Data Model

### Fields
*   `mFillContexts`: `ArrayList<FillContext>` - Snapshots of the screen. `get(0)` is usually the state at first fill request, `get(size-1)` is the state at save time.
*   `mClientState`: `Bundle` - The bundle set in the last `FillResponse`.
*   `mDatasetIds`: `ArrayList<String>` - IDs of datasets selected by the user previously (if any).

## API Reference

### Getters
*   `getFillContexts()`
*   `getClientState()`
*   `getDatasetIds()`

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Standard `Parcelable`.
*   **C++**: `android::Parcelable`.

### Usage
*   Service iterates `FillContexts`, traverses `AssistStructure` in them, finds `AutofillId`s of interest, and reads `AutofillValue`.

## Implementation Notes
*   **Immutable**.
*   **Context History**: The list of contexts allows handling multi-screen save workflows (where data was entered across multiple activities or steps).
