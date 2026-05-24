# NanoAppRpcService - Reverse Engineering Documentation

## Executive Summary
`NanoAppRpcService` describes an RPC interface published by a nanoapp. It is informational, allowing clients to discover that a nanoapp supports a specific service ID and version.

## Architecture Overview
- **Pattern**: Metadata / Descriptor.
- **Inheritance**: Implements `android.os.Parcelable`.

## Data Model
- `mServiceId`: `long` (Unique Service ID).
- `mServiceVersion`: `int` (SemVer: Major.Minor.Patch).

## Java-to-C++ Translation Guide
- **Data Structure**: Struct.

## Questions for C++ Team
- None.
