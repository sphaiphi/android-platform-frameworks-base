# Capabilities - Reverse Engineering Documentation

## Executive Summary
Defines standard constants representing the state of a specific capability for a user on the device. These constants describe whether a user can configure something or perform an action (e.g., modifying time settings). It abstracts the "why" (permissions, policy, hardware) into simple states like `NOT_SUPPORTED` or `NOT_ALLOWED`.

## Architecture Overview
*   **Type**: `public final class` (Utility/Constants)
*   **Role**: Defines the schema for capability states used throughout the `android.app.time` package.
*   **Dependencies**: None (Pure Java/Android constants).

## Detailed Functionality

### Capability States
The class defines four mutually exclusive states for any given capability:
1.  **CAPABILITY_NOT_SUPPORTED (10)**: Hardware/Form-factor limitation. UI should be hidden.
2.  **CAPABILITY_NOT_ALLOWED (20)**: Policy restriction (e.g., secondary user, enterprise policy). UI hidden or disabled.
3.  **CAPABILITY_NOT_APPLICABLE (30)**: User has permission, but the setting is currently irrelevant due to other state (e.g., "Manual Time" is not applicable when "Auto Time" is enabled). UI disabled or effective-no-op.
4.  **CAPABILITY_POSSESSED (40)**: User can perform the action.

## Data Model
*   **State Representation**: `int`
*   **Annotations**: `@IntDef` used for compile-time validation of `CapabilityState`.

## API Reference
*   `public static final int CAPABILITY_NOT_SUPPORTED = 10;`
*   `public static final int CAPABILITY_NOT_ALLOWED = 20;`
*   `public static final int CAPABILITY_NOT_APPLICABLE = 30;`
*   `public static final int CAPABILITY_POSSESSED = 40;`

## Java-to-C++ Translation Guide
*   **Class**: Namespace `android::app::time::Capabilities`.
*   **Constants**: Use `enum class CapabilityState : int32_t` or `static constexpr int32_t`.
*   **Annotations**: Remove `@IntDef`, `@SystemApi`.

## Test Cases & Validation
*   Verify values match: 10, 20, 30, 40.
*   Verify strict ordering if logic depends on `capability > CAPABILITY_NOT_APPLICABLE`.

## Implementation Risks
*   None. Pure constants.
