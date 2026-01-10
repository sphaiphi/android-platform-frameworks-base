# SyncableFlag - Reverse Engineering Documentation

## Executive Summary
`SyncableFlag` is a `Parcelable` data transfer object (DTO) used to transport flag information across Binder.

## Data Model
- `mNamespace` (String)
- `mName` (String)
- `mValue` (String): String representation of the value.
- `mDynamic` (boolean)
- `mOverridden` (boolean)

## Java-to-C++ Translation Guide
- **Serialization**: AIDL Parcelable.
- **Value**: Transmitted as string, parsed on receiver.

## Source Reference
Defined in `SyncableFlag.java` and `SyncableFlag.aidl`.
