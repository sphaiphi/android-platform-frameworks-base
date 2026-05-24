# MultiVibratorInfo - Reverse Engineering Documentation

## Executive Summary
`MultiVibratorInfo` represents the aggregate capabilities of multiple physical vibrators treated as a single logical entity. It calculates the *intersection* of features (what is supported by *all* vibrators) to determine the capabilities of the combined group. This is crucial for devices with multiple vibrators (e.g., dual-haptic game controllers or phones with top/bottom haptics) where the app sees a single `Vibrator` instance.

## Architecture Overview
-   **Inheritance**: Extends `VibratorInfo`.
-   **Logic**: "Intersection" logic. A feature is supported only if *all* individual vibrators support it.
-   **Frequency Profiles**: Calculates merged frequency profiles by intersecting supported frequency ranges and taking the minimum acceleration at common frequencies.

## Detailed Functionality

### Capability Intersection
-   **Bitwise AND**: `capabilitiesIntersection` performs `&` on capabilities bitmaps.
-   **Frequency Control**: If the merged frequency profile is empty (no common frequency range), `CAP_FREQUENCY_CONTROL` is removed even if individual vibrators support it.

### Feature Intersection
-   **Effects/Braking**: Uses `SparseBooleanArray`. Iterates through supported IDs of the first vibrator and checks if others support them.
-   **Primitives**: Uses `SparseIntArray` (ID -> Duration). If a primitive is supported by all, the *maximum* duration among them is used (pessimistic estimation for completion).

### Limits Intersection
-   **Integer Limits** (e.g., `compositionSizeMax`): Takes the *minimum* non-zero limit across all vibrators. (Smallest buffer rules).
-   **Float Properties** (e.g., `QFactor`, `ResonantFreq`): Returns the value only if *all* vibrators have the exact same value; otherwise returns `NaN`.

### Frequency Profile Intersection
-   **Range**: Intersection of [Min, Max] ranges.
-   **Resolution**: Must match across all vibrators (implied by equality check).
-   **Amplitudes/Accelerations**: For each common frequency point, takes the *minimum* supported acceleration/amplitude across devices. This ensures safe operation within the limits of the weakest vibrator.

## API Reference
-   **Constructor**: `MultiVibratorInfo(int id, VibratorInfo[] vibrators)`. Private, accessed via `VibratorInfoFactory`.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: Likely a logic block within `VibratorManager` or a native `MultiVibratorInfo` class if logic is pushed down.
-   **Logic Replication**: The intersection logic (Bitwise AND for capabilities, Min/Max for ranges, Set intersection for discrete IDs) is purely algorithmic and should be ported directly.
-   **Math**: Use standard `std::min`, `std::max`, `std::abs`. Note the `EPSILON` (1e-5f) for float comparisons.

## Implementation Risks
-   **Empty Intersection**: If vibrators are too different, the resulting info might claim "no support" for features, downgrading user experience.
-   **Float Comparison**: Strict equality checks for properties like Resonant Frequency might be too aggressive if hardware varies slightly.
