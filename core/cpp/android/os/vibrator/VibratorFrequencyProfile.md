# VibratorFrequencyProfile - Reverse Engineering Documentation

## Executive Summary
`VibratorFrequencyProfile` describes the output characteristics of a vibrator: specifically, the maximum acceleration (G-force) it can produce at various frequencies. This allows for equalized vibration effects where amplitude is adjusted based on frequency response to achieve consistent perceived strength.

## Architecture Overview
-   **Role**: Device Profile / Calibration Data.
-   **Backing**: `VibratorInfo.FrequencyProfile` (likely populated from HAL).
-   **Data Structure**: `SparseArray<Float>` mapping Frequency (Hz) -> Max Acceleration (Gs).

## Detailed Functionality
-   **Interpolation**: `getOutputAccelerationGs(float freq)` performs linear interpolation between the discrete points in the profile to estimate response at any frequency.
-   **Range Finding**: `getFrequencyRange(minGs)` finds the bandwidth where the vibrator is strong enough.

## API Reference
-   `getMinFrequencyHz()`, `getMaxFrequencyHz()`.
-   `getMaxOutputAccelerationGs()`: The global peak power.

## Java-to-C++ Translation Guide
-   **Logic**: The linear interpolation logic is critical for mapping "normalized" amplitudes to hardware-specific values in the C++ service.
-   **Representation**: `std::map<float, float>` or sorted `std::vector<pair<float, float>>`.

## Implementation Risks
-   **Empty Profile**: Handled by checks, but if missing, the vibrator cannot support PWLE/Ramps effectively (no Frequency Control).
