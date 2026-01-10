# UriRelativeFilterGroup - Reverse Engineering Documentation

## Executive Summary
`UriRelativeFilterGroup` is a collection of `UriRelativeFilter`s that must *all* match for the group to match. It also defines an action (ALLOW/BLOCK).

## Architecture Overview
- **Usage:** Used in `IntentFilter` (new in Android V?).

## Data Model
- `mAction`: `int` (ALLOW/BLOCK).
- `mUriRelativeFilters`: `ArraySet<UriRelativeFilter>`.

## API Reference
- `public boolean matchData(Uri data)`

## Java-to-C++ Translation Guide
- **Logic**: AND logic for filters in the group.

## Implementation Risks
- None.