# TrustedPresentationThresholds - Reverse Engineering Documentation

## Executive Summary
`TrustedPresentationThresholds` defines the numeric criteria for a window to be considered in a "trusted presentation" state. These criteria include minimum alpha, minimum fraction of the area rendered, and a stability duration.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Configuration DTO for trust monitoring.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mMinAlpha` | `float` | Minimum opacity (0.0 to 1.0). |
| `mMinFractionRendered` | `float` | Minimum visible area fraction (0.0 to 1.0). |
| `mStabilityRequirementMs` | `int` | Required time in state (milliseconds). |

## Detailed Functionality
*   **Validation**: Throws `IllegalArgumentException` if alpha/fraction <= 0 or time < 1.

## Java-to-C++ Translation Guide
*   Standard DTO.

## Implementation Risks
*   None.
