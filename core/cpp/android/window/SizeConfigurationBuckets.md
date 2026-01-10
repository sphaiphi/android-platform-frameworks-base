# SizeConfigurationBuckets - Reverse Engineering Documentation

## Executive Summary
`SizeConfigurationBuckets` is a utility and data class used to filter configuration changes. It allows the system to ignore small size changes that don't cross specific "bucket" thresholds defined by the application (e.g., via `layout-w600dp` resources), preventing unnecessary activity restarts.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Configuration Diff Filter.

## Data Model
*   `mHorizontal`: `int[]` (Width thresholds).
*   `mVertical`: `int[]` (Height thresholds).
*   `mSmallest`: `int[]` (Smallest width thresholds).
*   `mScreenLayoutSize`: `int[]` (Screen layout size buckets).
*   `mScreenLayoutLongSet`: `boolean`.

## Detailed Functionality

### `crossesSizeThreshold(int[] thresholds, int first, int second)`
**Algorithm**:
1.  Iterate through thresholds.
2.  If `(first < threshold && second >= threshold)` OR `(first >= threshold && second < threshold)`, return true.
3.  Else false.

### `filterDiff(...)`
**Inputs**: `diff` (int), `oldConfig`, `newConfig`, `buckets`.
**Logic**:
1.  If buckets null, return diff.
2.  If `CONFIG_SCREEN_SIZE` in diff: check horizontal/vertical thresholds. If not crossed, remove bit.
3.  If `CONFIG_SMALLEST_SCREEN_SIZE` in diff: check smallest thresholds. If not crossed, remove bit.
4.  Similar for `CONFIG_SCREEN_LAYOUT`.

## Java-to-C++ Translation Guide

### Data Types
*   `int[]` -> `std::vector<int>`.

### Logic
*   Pure logic. Direct translation.

## Implementation Risks
*   None.
