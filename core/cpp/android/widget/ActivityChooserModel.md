# ActivityChooserModel - Reverse Engineering Documentation

## Executive Summary
`ActivityChooserModel` is a data model class responsible for reading, writing, and sorting historical data about activity choices (e.g., "Share via..."). It backs the `ActivityChooserView`. It maintains a history of which activities the user selected for specific intents to rank frequently used activities higher.

## Architecture Overview
*   **Type**: Data Model / Observable.
*   **Role**: History management and ranking for intent resolution.
*   **Storage**: XML file (historical-records).
*   **Pattern**: Singleton-per-file (Registry).

## Detailed Functionality

### 1. History Persistence
*   **Read**: Parses an XML file containing `<historical-record>` tags with `activity`, `time`, and `weight`.
*   **Write**: Serializes the in-memory list of `HistoricalRecord`s to XML on a background thread (`PersistHistoryAsyncTask`).

### 2. Ranking Algorithm (`DefaultSorter`)
*   **Weight Decay**: Older choices have less influence.
*   **Scoring**:
    *   Iterates history from newest to oldest.
    *   Activity Score += `record.weight` * `nextRecordWeight`.
    *   `nextRecordWeight` decays by a factor (e.g., 0.95) each step.
*   Sorts `ActivityResolveInfo` objects based on this calculated score.

### 3. Activity Loading
*   Uses `PackageManager.queryIntentActivities` to find all candidates for the given `Intent`.

## Java-to-C++ Translation Guide
*   **Persistence**: Use a lightweight file format (JSON/XML/Binary) to store the history.
*   **Threading**: File I/O MUST be on a background thread.
*   **Observation**: Implement an Observer pattern to notify the UI when data changes.

## Implementation Risks
*   **Concurrency**: Access to the historical records list needs synchronization (`synchronized (mInstanceLock)`).
*   **Disk I/O**: File corruption handling during read/write.
