# UniqueProgramIdentifier - Reverse Engineering Documentation

## Executive Summary
`UniqueProgramIdentifier` is a wrapper class used to uniquely identify a radio program. It is primarily a transport object for internal communication between the Broadcast Radio Service and the Radio Manager. It encapsulates a primary identifier and a set of "critical" secondary identifiers needed for uniqueness (e.g., DAB Ensemble + Frequency).

## Architecture Overview
-   **Type**: Parcelable, Internal API.
-   **Package**: `android.hardware.radio`.
-   **Role**: Unique Key for programs in `ProgramList` maps.

## Detailed Functionality

### Core Fields
-   `mPrimaryId`: The main `ProgramSelector.Identifier`.
-   `mCriticalSecondaryIds`: Array of `ProgramSelector.Identifier` that are essential for distinguishing the program (e.g., distinguishing the same service on different ensembles).

### Logic
-   **Constructor**:
    -   Takes a `ProgramSelector`.
    -   Extracts `mPrimaryId`.
    -   **DAB Logic**: If the primary ID is `DAB_SID_EXT` or `DAB_DMB_SID_EXT`, it scans `secondaryIds` for `DAB_ENSEMBLE` and `DAB_FREQUENCY`. These are added to `mCriticalSecondaryIds` to ensure uniqueness (since SId alone might not be unique across ensembles/frequencies).
-   `requireCriticalSecondaryIds(int type)`: Static helper. Returns `true` for DAB types.
-   `equals/hashCode`: Uses both primary and critical secondary IDs.

## Java-to-C++ Translation Guide
-   **Struct**: C++ class/struct holding `Identifier` primary and `vector<Identifier>` critical secondary.
-   **Logic**: Replicate the DAB-specific extraction logic in the constructor/factory.
-   **Usage**: Use as key in `std::map` (requires defining `operator<` or a hash function).

---
