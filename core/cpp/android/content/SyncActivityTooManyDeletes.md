# SyncActivityTooManyDeletes - Reverse Engineering Documentation

## Executive Summary
`SyncActivityTooManyDeletes` is an Activity presented to the user when a sync operation fails because it would delete too many items. It asks the user whether to proceed with the deletion, undo the deletion, or do nothing.

## Architecture Overview
- **Inheritance:** Extends `Activity`.
- **UI:** Simple list of options (`ListView`).

## Detailed Functionality
- **`onCreate`**: Parses the intent extras (`numDeletes`, `account`, `authority`, `provider`). Sets up the UI.
- **`onItemClick`**: Handles user selection.
    - **Really Delete**: Triggers a sync with `SYNC_EXTRAS_OVERRIDE_TOO_MANY_DELETIONS`.
    - **Undo Deletes**: Triggers a sync with `SYNC_EXTRAS_DISCARD_LOCAL_DELETIONS`.
    - **Do Nothing**: Finishes.

## API Reference
- Standard Activity lifecycle.

## Java-to-C++ Translation Guide
- **Activity**: Maps to a UI controller. Code logic is simple intent manipulation.

## Implementation Risks
- None.