# PrintJobInfo - Reverse Engineering Documentation

## Executive Summary
`PrintJobInfo` is a comprehensive snapshot of a print job's state. It includes the ID, current state (created, queued, started, etc.), progress, attributes, and document info.

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Builder**: Uses `Builder`.

## Detailed Functionality
-   **States**: Defines lifecycle states (CREATED -> QUEUED -> STARTED -> COMPLETED/FAILED/CANCELED).
-   **Progress**: Float 0.0 - 1.0.
-   **Advanced Options**: `Bundle` for printer-specific strings/ints.

## Data Model
-   `mId`: PrintJobId
-   `mState`: int
-   `mAttributes`: PrintAttributes
-   `mDocumentInfo`: PrintDocumentInfo
-   `mProgress`: float
-   `mStatus`: CharSequence (and resource ID variant)

## Java-to-C++ Translation Guide
-   **State Machine**: The state constants are critical for logic flow.
-   **Bundle**: `mAdvancedOptions` uses `Bundle`. C++ needs a `PersistableBundle` equivalent (map of strings/variants).
