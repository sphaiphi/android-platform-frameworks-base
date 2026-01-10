# IRestrictionsManager - Reverse Engineering Documentation

## Executive Summary
`IRestrictionsManager` is the AIDL interface for the Restrictions Manager service. It allows querying application restrictions and requesting permissions from a restrictions provider.

## Architecture Overview
- **Type:** AIDL Interface.
- **Relationship:** Interface for `RestrictionsManager` (client) to talk to `RestrictionsManagerService` (system).

## API Reference
- `Bundle getApplicationRestrictions(String packageName)`
- `boolean hasRestrictionsProvider()`
- `void requestPermission(...)`
- `void notifyPermissionResponse(...)`
- `Intent createLocalApprovalIntent()`

## Java-to-C++ Translation Guide
- **AIDL**: C++ generated code.

## Implementation Risks
- None.
