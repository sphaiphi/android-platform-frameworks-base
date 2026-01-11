# RadioAlert - Reverse Engineering Documentation

## Executive Summary
`RadioAlert` represents an Emergency Alert Message (EAS), typically received via HD Radio. It contains details like status, urgency, severity, certainty, and the affected geographic area.

## Architecture Overview
-   **Type**: Parcelable, System API, Flagged (`hd_radio_emergency_alert_system`).
-   **Package**: `android.hardware.radio`.
-   **Role**: Carries EAS data within `RadioManager.ProgramInfo`.

## Detailed Functionality

### Core Fields
-   `mStatus`: `STATUS_ACTUAL`, `STATUS_EXERCISE`, `STATUS_TEST`.
-   `mMessageType`: `ALERT`, `UPDATE`, `CANCEL`.
-   `mInfoList`: List of `AlertInfo` objects.

### Inner Classes (Data Structures)
1.  **AlertInfo**:
    -   `mCategories`: Array of ints (Geo, Met, Safety, etc.).
    -   `mUrgency`: Immediate, Expected, Future, Past, Unknown.
    -   `mSeverity`: Extreme, Severe, Moderate, Minor, Unknown.
    -   `mCertainty`: Observed, Likely, Possible, Unlikely, Unknown.
    -   `mTextualMessage`: String description.
    -   `mAreaList`: List of `AlertArea`.
    -   `mLanguage`: ISO 3066 language code.
2.  **AlertArea**:
    -   `mPolygons`: List of `Polygon`.
    -   `mGeocodes`: List of `Geocode`.
3.  **Polygon**:
    -   `mCoordinates`: List of `Coordinate` (Lat/Lon). Enforces loop (first == last).
4.  **Coordinate**:
    -   `mLatitude`, `mLongitude` (Double). Validates ranges.
5.  **Geocode**:
    -   `mValueName` (e.g., "SAME", "FIPS"), `mValue`.

## Data Model
-   **Enums**: Extensive use of `IntDef` for Status, Urgency, Severity, Certainty, Category.
-   **Geometry**: Polygons defined by WGS 84 coordinates.

## Java-to-C++ Translation Guide
-   **Data Classes**: Direct mapping to C++ structs/classes.
-   **Validation**: Replicate constructor checks (e.g., latitude -90 to 90, polygon closure).
-   **Collections**: `std::vector` for lists.
-   **Strings**: `std::string`.

## Implementation Risks
-   **Validation Logic**: Ensure the coordinate and polygon validation logic is preserved to prevent invalid geometry data.
-   **Nested Parcelables**: Deep structure (Alert -> Info -> Area -> Polygon -> Coordinate) requires careful serialization/deserialization logic.

---
