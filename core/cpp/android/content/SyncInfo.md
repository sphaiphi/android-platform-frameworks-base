# SyncInfo - Reverse Engineering Documentation

## Executive Summary
`SyncInfo` represents a currently active sync operation. It contains the authority, account, start time, and an ID.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Usage:** Returned by `ContentResolver.getCurrentSyncs()`.

## Data Model
- `authorityId`: `int` (Internal ID).
- `account`: `Account`.
- `authority`: `String`.
- `startTime`: `long`.

## API Reference
- `public SyncInfo(int authorityId, Account account, String authority, long startTime)`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.

## Implementation Risks
- **Privacy**: `createAccountRedacted` creates a safe version for callers without GET_ACCOUNTS permission.