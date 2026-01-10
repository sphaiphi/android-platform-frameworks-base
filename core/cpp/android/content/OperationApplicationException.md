# OperationApplicationException - Reverse Engineering Documentation

## Executive Summary
`OperationApplicationException` is thrown when a `ContentProviderOperation` fails. It can report the number of successful operations before the failure (specifically "yield points").

## Architecture Overview
- **Inheritance:** Extends `Exception`.

## Data Model
- `mNumSuccessfulYieldPoints`: `int`.

## API Reference
- `public int getNumSuccessfulYieldPoints()`

## Java-to-C++ Translation Guide
- **Exception**: Standard C++ exception class.

## Implementation Risks
- None.
