
# MagnificationConfig - Reverse Engineering Documentation

## Executive Summary
`MagnificationConfig` is a `Parcelable` data class that holds the configuration for screen magnification. It is used by an `AccessibilityService` to query the current magnification state and to apply new settings (like scale and center position) by sending an instance of this class to the system. It supports different magnification modes, such as full-screen and windowed.

## Architecture Overview
*   **Data Container**: This is a pure data-holding class. It encapsulates the properties of a magnification setup: mode, activation state, scale, and center coordinates.
*   **Parcelable**: It implements `Parcelable` and is declared in an `.aidl` file, which is essential for it to be passed across the Binder IPC boundary between an accessibility service and the system's `AccessibilityManagerService`.
*   **Builder Pattern**: An inner `Builder` class is provided for safe and convenient construction of `MagnificationConfig` objects. This allows for setting only the desired properties while the others retain default values.
*   **Immutable-like**: While the fields are not strictly `final`, the class is designed to be treated as immutable once created by the builder. It has no setter methods, only getters.

## Detailed Functionality

### `MagnificationConfig.Builder`
*   **Purpose**: The public API for constructing a `MagnificationConfig` object.
*   **Methods**:
    *   `setMode(int mode)`: Sets the magnification mode (e.g., `MAGNIFICATION_MODE_FULLSCREEN`).
    *   `setActivated(boolean activated)`: Sets whether the magnifier should be active.
    *   `setScale(float scale)`: Sets the magnification scale factor.
    *   `setCenterX(float centerX)` / `setCenterY(float centerY)`: Sets the coordinates of the center of the magnified viewport.
*   **`build()`**: Returns a new `MagnificationConfig` instance populated with the values from the builder.

### `MagnificationConfig` Getters
*   `getMode()`: Returns the magnification mode.
*   `isActivated()`: Returns `true` if the magnifier is intended to be active.
*   `getScale()`: Returns the scale factor.
*   `getCenterX()` / `getCenterY()`: Returns the center coordinates.

### Parcelable Implementation
*   **Purpose**: To enable the object to be sent over IPC.
*   **`writeToParcel(...)`**: Writes the fields (`mMode`, `mActivated`, `mScale`, `mCenterX`, `mCenterY`) to the parcel in a fixed order.
*   **`MagnificationConfig(Parcel)` constructor**: Reads the fields from the parcel in the same fixed order.
*   **C++ Implementation Guidance**: The C++ version must implement `readFromParcel` and `writeToParcel` methods that read and write the exact same data types (`int`, `bool`, `float`, `float`, `float`) in the same order to ensure compatibility. The `ndk_header` in the AIDL file suggests a C++ counterpart is intended for NDK use.

## Data Model
*   `mMode`: An `int` representing the magnification mode, validated by the `@MagnificationMode` IntDef.
*   `mActivated`: A `boolean` indicating if the magnifier is active.
*   `mScale`: A `float` for the zoom level. `Float.NaN` is used as a sentinel value to indicate "unchanged" when building the config.
*   `mCenterX`, `mCenterY`: `float` coordinates for the viewport center. `Float.NaN` is also used as a sentinel value here.

## Java-to-C++ Translation Guide
*   **Class/Struct**: This translates directly to a C++ `class` or `struct`.
*   **Parcelable**: The C++ class must implement the `android::Parcelable` or `AParcelable` interface, with `writeToParcel` and `readFromParcel` methods matching the Java wire format.
*   **Builder Pattern**: The builder pattern is easily replicated in C++ and is a good practice for constructing complex objects with multiple optional parameters.
*   **Enums/Constants**: The `MAGNIFICATION_MODE_*` constants can be defined as a C++ `enum class` for type safety.
*   **Sentinel Values**: The use of `Float.NaN` as a sentinel value to mean "unspecified" is a convention that can be carried over to C++. The C++ code that interprets this object would need to check for `std::isnan()`.

    ```cpp
    // Example C++ skeleton
    class MagnificationConfig : public android::Parcelable {
    public:
        // Builder, getters, etc.

        status_t writeToParcel(Parcel* parcel) const override;
        status_t readFromParcel(const Parcel* parcel) override;

    private:
        int32_t mMode = MAGNIFICATION_MODE_DEFAULT;
        bool mActivated = false;
        float mScale = std::numeric_limits<float>::quiet_NaN();
        float mCenterX = std::numeric_limits<float>::quiet_NaN();
        float mCenterY = std::numeric_limits<float>::quiet_NaN();
    };
    ```

## Implementation Risks
*   **Parcel Mismatch**: This is the primary risk. The C++ `Parcelable` implementation's data layout must be identical to the Java version's. Any discrepancy will lead to data corruption or crashes during IPC.
*   **Sentinel Value Handling**: The logic that consumes this object must correctly handle the `NaN` sentinel values. If it fails to check for `NaN` and uses the value directly in calculations, it will lead to incorrect behavior.

## Questions for C++ Team
*   Is the use of `NaN` as a sentinel value acceptable in our C++ coding standards, or should we use a different mechanism (e.g., `std::optional` for C++17 and later, or separate boolean flags)?
*   How will the `MAGNIFICATION_MODE_*` constants be defined and shared to ensure they do not diverge from the Java definitions?
