# VibrationConfig - Reverse Engineering Documentation

## Executive Summary
`VibrationConfig` loads and stores device-specific vibration configuration from `config.xml` resources (internal R). It defines defaults for intensities, amplitudes, ramp durations, and behavior quirks (like ignoring vibration on wireless chargers).

## Architecture Overview
-   **Pattern**: Configuration/Settings Holder.
-   **Source**: `com.android.internal.R`.
-   **Scope**: System-wide configuration.

## Key Configs
-   **Haptic Channel**: `mHapticChannelMaxVibrationAmplitude`.
-   **Default Intensities**: Per-usage defaults (Alarm, Ring, Touch, etc.).
-   **Ramping**: `mRampStepDurationMs`, `mRampDownDurationMs`.
-   **Request Timeout**: `mRequestVibrationParamsTimeoutMs` (for delayed parameter requests).
-   **Pipeline**: `mVibrationPipelineMaxDurationMs`.

## API Reference
-   Getters for all loaded config values.
-   `getDefaultVibrationIntensity(usage)`: Maps usage to configured default intensity.

## Java-to-C++ Translation Guide
-   **Access**: These values are typically loaded by `VibratorManagerService` (Java) and passed to native code if needed, or looked up via JNI.
-   **Hardware Properties**: Some of these (max amplitude) might be redundant with HAL capabilities but serve as software limits.

## Implementation Risks
-   **Resource Overlays**: These values vary per device (overlay). Hardcoding them in C++ without loading from the actual XML/prop sources would be incorrect.
