# PeriodicSync - Reverse Engineering Documentation

## Executive Summary
`PeriodicSync` represents a sync operation that is scheduled to run periodically. It behaves like a value object.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.

## Data Model
- `account`: `Account`.
- `authority`: `String`.
- `extras`: `Bundle`.
- `period`: `long` (seconds).
- `flexTime`: `long` (seconds).

## API Reference
- `public PeriodicSync(Account account, String authority, Bundle extras, long period)`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.
- **Equality**: Custom equals method checking fields and bundle contents.

## Implementation Risks
- None.