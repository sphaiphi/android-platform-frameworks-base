# ISyncAdapterUnsyncableAccountCallback - Reverse Engineering Documentation

## Executive Summary
`ISyncAdapterUnsyncableAccountCallback` is a callback interface used by `ISyncAdapter.onUnsyncableAccount` to report whether the account is ready for syncing.

## Architecture Overview
- **Type:** AIDL Interface (Oneway).

## API Reference
- `void onUnsyncableAccountDone(boolean isReady)`

## Java-to-C++ Translation Guide
- **AIDL**: C++ generated code.

## Implementation Risks
- None.
