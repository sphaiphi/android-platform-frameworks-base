# CoolingDevice - Reverse Engineering Documentation

## Executive Summary
`CoolingDevice` represents a hardware cooling device (fan, passive heatsink throttling) managed by the `ThermalService`. It is part of the Thermal HAL interface.

## Architecture Overview
-   **Role**: Thermal Actuator State.
-   **Source**: Thermal HAL.

## Data Model
-   `mValue` (long): Current throttle state/level.
-   `mType` (int): Type (`FAN`, `BATTERY`, `CPU`, `GPU`, etc.).
-   `mName` (String): Device identifier.

## Java-to-C++ Translation Guide
-   **Parcelable**: Matches `CoolingDevice.aidl`.
-   **Enum**: `Type` corresponds to `android.hardware.thermal` types.
