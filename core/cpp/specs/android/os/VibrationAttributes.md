# VibrationAttributes - Reverse Engineering Documentation

## Executive Summary
`VibrationAttributes` encapsulates metadata about *why* a vibration is happening (Usage) and *how* it should be handled (Flags). It replaces the legacy `AudioAttributes` usage for vibrations, decoupling audio and haptics.

## Architecture Overview
-   **Pattern**: Configuration Object / DTO.
-   **Usage**: Passed to `Vibrator.vibrate()` to determine priority, interruption policy (Do Not Disturb), and intensity scaling.

## Data Model
-   **Usage**:
    -   `USAGE_ALARM`, `USAGE_RINGTONE`, `USAGE_NOTIFICATION`.
    -   `USAGE_TOUCH`: Haptic feedback.
    -   `USAGE_MEDIA`: Music/Games.
    -   `USAGE_COMMUNICATION_REQUEST`: VoIP calls.
-   **Flags**:
    -   `FLAG_BYPASS_INTERRUPTION_POLICY`: Vibrates even in DND (requires permission).
    -   `FLAG_BYPASS_USER_VIBRATION_INTENSITY_OFF`: Vibrates even if user disabled haptics.

## API Reference
-   `createForUsage(int usage)`: Static factory.
-   `getUsage()`: Returns the usage int.
-   `getFlags()`: Returns the flags bitmask.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::os::VibrationAttributes` (AIDL generated).
-   **Mapping**: Ensure the integer constants for `USAGE_*` match exactly (defined in `VibrationAttributes.aidl` or `java`).
    -   `USAGE_TOUCH` = 0x12 (18)
    -   `USAGE_RINGTONE` = 0x21 (33)
    *(Note: Check exact values in source code, they are often offsets of base classes)*.

## Implementation Risks
-   **Policy**: C++ code implementing policy checks (e.g., inside `VibratorService`) relies on these attributes to correctly filter vibrations. Incorrect mapping allows background apps to vibrate when they shouldn't.
