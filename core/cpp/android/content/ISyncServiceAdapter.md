# ISyncServiceAdapter - Reverse Engineering Documentation

## Executive Summary
`ISyncServiceAdapter` is an interface for anonymous services to perform anonymous syncs (without an Account/Provider).

## Architecture Overview
- **Type:** AIDL Interface (Oneway).

## API Reference
- `void startSync(ISyncContext syncContext, Bundle extras)`
- `void cancelSync(ISyncContext syncContext)`

## Java-to-C++ Translation Guide
- **AIDL**: C++ generated code.

## Implementation Risks
- None.
