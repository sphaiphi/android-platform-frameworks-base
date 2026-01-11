# RadioMetadata - Reverse Engineering Documentation

## Executive Summary
`RadioMetadata` allows the transfer of metadata (RDS, ID3 tags, DAB info) from the radio hardware to the client. It uses a `Bundle` to store key-value pairs, supporting Strings, Integers, Bitmaps, and Clocks.

## Architecture Overview
-   **Type**: Parcelable, System API.
-   **Package**: `android.hardware.radio`.
-   **Role**: Container for station metadata (Title, Artist, Station Name, Icons).

## Detailed Functionality

### Core Storage
-   `mBundle`: A `android.os.Bundle` holding the raw data.
-   `METADATA_KEYS_TYPE`: Static map defining the expected type (`INT`, `TEXT`, `BITMAP`, `CLOCK`) for each key.

### Supported Keys (`METADATA_KEY_*`)
-   **RDS/RBDS**: `RDS_PI`, `RDS_PS` (Program Service), `RDS_PTY` (Program Type), `RDS_RT` (Radio Text).
-   **Media**: `TITLE`, `ARTIST`, `ALBUM`, `GENRE`.
-   **Visuals**: `ICON`, `ART` (Bitmaps).
-   **DAB**: `DAB_ENSEMBLE_NAME`, `DAB_SERVICE_NAME`, `DAB_COMPONENT_NAME`.
-   **HD Radio**: `HD_STATION_NAME_SHORT`, `HD_STATION_NAME_LONG`, `HD_SUBCHANNELS_AVAILABLE`.
-   **Misc**: `CLOCK`, `PROGRAM_NAME`, `COMMERCIAL`, `UFIDS`.

### Data Types
-   `INT`: Integer values (e.g., PTY, PI).
-   `TEXT`: Strings (e.g., Title, Artist).
-   `BITMAP`: `android.graphics.Bitmap`.
-   `CLOCK`: `RadioMetadata.Clock` (UTC seconds + timezone offset).
-   `TEXT_ARRAY`: String arrays (e.g., UFIDs).

### Inner Classes
-   **Clock** (Parcelable):
    -   `mUtcEpochSeconds` (long).
    -   `mTimezoneOffsetMinutes` (int).
-   **Builder**:
    -   Helper to construct `RadioMetadata`.
    -   Validates types against `METADATA_KEYS_TYPE` before insertion.
    -   Can scale bitmaps if they exceed a max size.

## Java-to-C++ Translation Guide
-   **Storage**: `Bundle` roughly maps to `android::os::PersistableBundle` or a custom `std::map<std::string, std::variant<...>>`. Since `Bitmap` is involved, a simple map might not suffice; you might need a custom parcelable structure or use the NDK's `ABundle` if available/suitable, or manually implement the serialization format.
-   **Bitmaps**: Handle `Bitmap` serialization/deserialization carefully (blob data).
-   **Type Safety**: Enforce the key-type mapping defined in `METADATA_KEYS_TYPE`.

## Implementation Risks
-   **Bitmap Overhead**: Bitmaps can be large. The Builder has logic to scale them; C++ implementation should consider similar safeguards or ensure efficient transport (e.g., SharedMemory) if blobs are large, though standard Parcelable is used here.
-   **Bundle Compatibility**: Replicating `Bundle` serialization exactly in C++ to talk to Java services requires matching the specific binary format of Android Bundles.

---
