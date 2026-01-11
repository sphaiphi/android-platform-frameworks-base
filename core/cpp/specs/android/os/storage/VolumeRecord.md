# VolumeRecord - Reverse Engineering Documentation

## Executive Summary
`VolumeRecord` persists metadata about a storage volume even when it is physically removed (unmounted). It stores user preferences like "nickname" (custom label), "user flags" (inited, snoozed), and historical timestamps (last seen, last bench).

## Architecture Overview
-   **Pattern**: Data Object / Parcelable / Persistent Record.
-   **Usage**: Stored in `fsUuid`-keyed XML file by `StorageManagerService` to remember settings across reboots/ejects.

## Data Model
-   **Key**: `fsUuid`.
-   **Type**: `type` (Public/Private).
-   **User Data**: `nickname`, `userFlags` (`USER_FLAG_INITED`, `USER_FLAG_SNOOZED`).
-   **Stats**: `createdMillis`, `lastSeenMillis`, `lastTrimMillis`, `lastBenchMillis`.

## Java-to-C++ Translation Guide
-   **Parceling**: Type, FsUuid, PartGuid, Nickname, UserFlags, CreatedMillis, LastSeenMillis, LastTrimMillis, LastBenchMillis.
-   **Usage**: Primarily managed by System Server. `vold` uses the `fsUuid` to identify volumes, but this record logic is mostly policy-level (Java).
