# LocusId - Reverse Engineering Documentation

## Executive Summary
`LocusId` represents a unique state (locus) in an application, used for correlating state between subsystems like content capture, shortcuts, and notifications.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Immutability:** Immutable class.

## Data Model
- `mId`: `String` (The ID).

## API Reference
- `public String getId()`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.

## Implementation Risks
- None.
