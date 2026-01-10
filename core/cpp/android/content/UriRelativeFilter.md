# UriRelativeFilter - Reverse Engineering Documentation

## Executive Summary
`UriRelativeFilter` represents a filter for a specific part of a URI (Path, Query, Fragment). It uses a `PatternMatcher` logic.

## Architecture Overview
- **Usage:** Part of `UriRelativeFilterGroup`.

## Constants
- `PATH`, `QUERY`, `FRAGMENT`.

## Data Model
- `mUriPart`: `int`.
- `mPatternType`: `int`.
- `mFilter`: `String`.

## API Reference
- `public boolean matchData(Uri data)`

## Java-to-C++ Translation Guide
- **PatternMatcher**: Need the logic from `android.os.PatternMatcher` (globbing).

## Implementation Risks
- **Query Matching**: Matches against *any* query parameter value? The code splits query by `&` and `;`.