# TimeZoneState - Reverse Engineering Documentation

## Executive Summary
Snapshot of the system's current Time Zone ID (e.g., "America/New_York") and a confirmation signal.

## Architecture Overview
*   **Type**: `public final class` implementing `Parcelable`.

## Data Model
*   `String mId`: The Olson ID.
*   `boolean mUserShouldConfirmId`.

## API Reference
*   `parseCommandLineArgs`: Parsing shell args `--zone_id`, `--user_should_confirm_id`.

## Java-to-C++ Translation Guide
*   **String**: Use `std::string`.
*   **Parceling**: `readString8` (UTF-8).

## Test Cases & Validation
*   Shell argument parsing.

## Implementation Risks
*   String encoding (ensure UTF-8).
