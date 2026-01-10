# NanoApp - Reverse Engineering Documentation

## Executive Summary
`NanoApp` is a deprecated class representing a nanoapp binary and metadata. It has been largely superseded by `NanoAppBinary` (for loading) and `NanoAppState` (for status querying).

## Architecture Overview
- **Status**: **DEPRECATED**.
- **Role**: Legacy container for app binary + metadata.

## Data Model
- `mAppId`, `mAppVersion`, `mName`, `mPublisher`.
- `mNeeded*MemBytes`.
- `mNeededSensors`, `mOutputEvents`.
- `mAppBinary`: `byte[]`.

## Java-to-C++ Translation Guide
- **Action**: Use `NanoAppBinary` for binary data and `NanoAppState` for runtime info.

## Questions for C++ Team
- Confirm legacy support requirements.
