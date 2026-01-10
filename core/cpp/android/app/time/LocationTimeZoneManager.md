# LocationTimeZoneManager - Reverse Engineering Documentation

## Executive Summary
Defines string constants used for shell command interactions with the `LocationTimeZoneManager` service.

## Architecture Overview
*   **Type**: `public final class` (Utility/Constants).
*   **Dependencies**: None.

## Detailed Functionality
Provides contract strings for:
*   Service name: `location_time_zone_manager`
*   Provider names: `primary`, `secondary`
*   Commands: `start`, `stop`, `dump_state`, `start_with_test_providers`.

## Data Model
*   String constants.

## API Reference
*   `PRIMARY_PROVIDER_NAME`, `SECONDARY_PROVIDER_NAME`
*   `SHELL_COMMAND_*`

## Java-to-C++ Translation Guide
*   Define as `static constexpr char[]` or `#define` macros in a header file.

## Test Cases & Validation
*   N/A (Constants).

## Implementation Risks
*   None.
