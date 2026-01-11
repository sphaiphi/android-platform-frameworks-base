# DisplayAdjustments - Reverse Engineering Documentation

## Executive Summary
`DisplayAdjustments` is a container for configuration-based adjustments applied to a `Display`. It primarily manages `CompatibilityInfo` (used for app-scaling/legacy modes) and the current `Configuration`.

## Architecture Overview
*   **Role**: Compatibility and configuration carrier.
*   **Context**: Often used by `Resources` and `Display` to ensure that metrics (like width/height) are reported correctly to apps running in compatibility modes.

## Detailed Functionality
*   **Compatibility Info**: Holds `mCompatInfo`, which defines scaling factors for apps designed for smaller or lower-density screens.
*   **Configuration**: Holds `mConfiguration`, representing the localized UI settings (orientation, density, locale).

## Java-to-C++ Translation Guide
*   **Mapping**: In C++, this can be a simple `struct` or `class` containing `Configuration` and `CompatibilityInfo` instances.
*   **Immutability**: `DEFAULT_DISPLAY_ADJUSTMENTS` is a protected singleton; ensure C++ implementations guard against accidental modifications to global defaults.

## Implementation Risks
*   **Consistency**: Mismatched `DisplayAdjustments` between the `Display` object and the `Resources` used to inflate views can lead to layout artifacts (e.g., views thinking the screen is a different size than the surface).
