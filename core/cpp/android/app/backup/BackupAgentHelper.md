# BackupAgentHelper - Reverse Engineering Documentation

## Executive Summary
`BackupAgentHelper` is a convenience wrapper around `BackupAgent` that simplifies key/value backups by dispatching requests to registered `BackupHelper` instances based on key prefixes. It is the standard parent class for most Android backup agents.

## Architecture Overview
-   **Inheritance**: `BackupAgent` -> `BackupAgentHelper`.
-   **Design Pattern**: Dispatcher / Composite.
-   **Key Component**: `BackupHelperDispatcher`.

## Detailed Functionality

### Helper Registration (`addHelper`)
-   **Input**: `String keyPrefix`, `BackupHelper helper`.
-   **Logic**: Registers the helper with the internal `mDispatcher`. The prefix allows multiple helpers to coexist without key collisions.

### Backup Dispatch (`onBackup`)
-   **Override**: Overrides `BackupAgent.onBackup`.
-   **Logic**: Delegates entirely to `mDispatcher.performBackup`. The dispatcher handles reading the state file chunks and routing to the correct helper.

### Restore Dispatch (`onRestore`)
-   **Override**: Overrides `BackupAgent.onRestore`.
-   **Logic**: Delegates entirely to `mDispatcher.performRestore`. The dispatcher parses the raw entity key (format `prefix:key`), identifies the prefix, and routes the entity to the matching helper.

## Data Model
-   `mDispatcher`: Instance of `BackupHelperDispatcher`.

## API Reference
-   `addHelper(String, BackupHelper)`: Main API for subclasses.
-   `onBackup(...)`, `onRestore(...)`: Standard overrides.

## Java-to-C++ Translation Guide
-   **Dispatcher Logic**: The core logic resides in `BackupHelperDispatcher`. `BackupAgentHelper` is a thin wrapper.
-   **Prefixing**: Ensure the string prefixing convention (`prefix:key`) is maintained exactly for compatibility with existing backups.

## Implementation Risks
-   None specific to this class; mostly relies on `BackupHelperDispatcher`.
