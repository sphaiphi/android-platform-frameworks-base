# SyncRequest - Reverse Engineering Documentation

## Executive Summary
`SyncRequest` represents a request to perform a sync operation. It can be a one-time sync or a periodic sync. It is constructed using `SyncRequest.Builder`.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Pattern:** Builder Pattern.

## Detailed Functionality
- **Builder**: Validates arguments (e.g., periodic syncs cannot have certain extras like `EXPEDITED`).

## Data Model
- `mAccountToSync`: `Account`.
- `mAuthority`: `String`.
- `mExtras`: `Bundle`.
- `mSyncRunTimeSecs`: `long` (Execution time / Period).
- `mSyncFlexTimeSecs`: `long` (Flex time).
- `mIsPeriodic`: `boolean`.
- `mDisallowMetered`: `boolean`.
- `mIsExpedited`: `boolean`.

## API Reference
- `public static class Builder`
    - `syncOnce()`, `syncPeriodic()`.
    - `setSyncAdapter(Account, String)`.
    - `setExtras(Bundle)`.
- `public boolean isPeriodic()`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.
- **Validation**: Builder logic needs to be ported to ensure valid requests.

## Implementation Risks
- **Logic**: Complex validation rules in `Builder.build()` regarding allowed extras for different sync types.