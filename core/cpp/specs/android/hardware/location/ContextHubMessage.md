# ContextHubMessage - Reverse Engineering Documentation

## Executive Summary
`ContextHubMessage` is a deprecated class representing a message to/from a context hub. It has been replaced by `NanoAppMessage`.

## Architecture Overview
- **Status**: **DEPRECATED**.
- **Role**: Legacy DTO.

## Data Model
- `mType`: `int`.
- `mVersion`: `int`.
- `mData`: `byte[]`.

## Java-to-C++ Translation Guide
- **Skip**: Unless strictly required for backward compatibility with very old HALs, use `NanoAppMessage` equivalents.

## Questions for C++ Team
- Confirm deprecation/removal in new C++ codebase.
