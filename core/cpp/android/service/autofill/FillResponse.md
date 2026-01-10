# FillResponse - Reverse Engineering Documentation

## Executive Summary
`FillResponse` is the container for the `AutofillService`'s reply to a `FillRequest`. It holds `Dataset`s (options for the user) and `SaveInfo` (how to save data later).

## Data Model

### Core Fields
*   `mDatasets`: `ParceledListSlice<Dataset>` - The list of autofill options.
*   `mSaveInfo`: `SaveInfo` - Configuration for saving data.
*   `mClientState`: `Bundle` - State to pass to future requests.
*   `mPresentation`: `RemoteViews` - UI for authentication/header/footer.
*   `mAuthentication`: `IntentSender` - Intent to launch if response requires auth.
*   `mIgnoredIds`: `AutofillId[]` - Views to ignore (not trigger further requests).
*   `mDisableDuration`: `long` - If set, disables autofill for this duration.
*   `mFieldClassificationIds`: `AutofillId[]` - IDs to perform classification on.

## API Reference

### Builder (`FillResponse.Builder`)
*   **`addDataset(Dataset)`**: Adds a dataset option.
*   **`setSaveInfo(SaveInfo)`**: Enables saving data.
*   **`setAuthentication(...)`**: Requires auth to see the response.
*   **`setClientState(Bundle)`**: Sets state bundle.
*   **`setIgnoredIds(AutofillId...)`**: Ignores specific views.
*   **`disableAutofill(long)`**: Disables the service temporarily.
*   **`setHeader`/`setFooter`**: Adds decoration to the UI.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Custom serialization.
    *   `ParceledListSlice` is used for `mDatasets` to handle large lists efficiently over Binder.
*   **C++**: `android::Parcelable`.
    *   Need to handle `ParceledListSlice` equivalent (likely iterating and writing to Parcel, or using a specific C++ helper if available in framework).

### Dependencies
*   `Dataset`, `SaveInfo`, `RemoteViews`, `AutofillId`.

## Implementation Notes
*   **Binder Limits**: Historically limited by transaction size. `ParceledListSlice` helps, but huge responses can still fail.
*   **Mutually Exclusive**: `disableAutofill` cannot be used with other setters.
