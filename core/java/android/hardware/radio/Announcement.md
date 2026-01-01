# Announcement - Reverse Engineering Documentation

## Executive Summary
`Announcement` is a Parcelable class representing a radio announcement, such as a traffic update, emergency alert, or news flash. It encapsulates the type of announcement, the program selector for the station broadcasting it, and vendor-specific information.

## Architecture Overview
-   **Type**: Parcelable Data Transfer Object (DTO).
-   **Package**: `android.hardware.radio`.
-   **Role**: Used by `RadioManager` and `IAnnouncementListener` to notify clients of available announcements.

## Detailed Functionality

### Core Fields
-   `mSelector`: A `ProgramSelector` identifying the station making the announcement.
-   `mType`: An integer representing the type of announcement (e.g., Traffic, Emergency). Defined by `@Type` IntDef.
-   `mVendorInfo`: A `Map<String, String>` containing vendor-specific metadata.

### Constants (Announcement Types)
-   `TYPE_EMERGENCY` (1): DAB alarm, RDS emergency.
-   `TYPE_WARNING` (2): DAB warning.
-   `TYPE_TRAFFIC` (3): DAB road traffic, RDS TA, HD Radio transportation.
-   `TYPE_WEATHER` (4): Weather.
-   `TYPE_NEWS` (5): News.
-   `TYPE_EVENT` (6): DAB event, special event.
-   `TYPE_SPORT` (7): DAB sport report, RDS sports.
-   `TYPE_MISC` (8): All others.

### Inner Interfaces
-   `OnListUpdatedListener`: Listener interface for announcement list updates.
    -   `onListUpdated(Collection<Announcement> activeAnnouncements)`: Called when the list of active announcements changes.

## Data Model
-   **ProgramSelector**: Used to identify the station.
-   **Type**: Integer (1-8).
-   **Vendor Info**: Key-value pairs (String -> String).

## API Reference
-   `getSelector()`: Returns the `ProgramSelector`.
-   `getType()`: Returns the announcement type.
-   `getVendorInfo()`: Returns the vendor info map.

## Java-to-C++ Translation Guide
-   **Parcelable**: Implement `Parcelable` (or AIDL-generated C++ equivalent) for serialization.
-   **Maps**: Use `std::map<std::string, std::string>` or `android::os::PersistableBundle` equivalent for `mVendorInfo`.
-   **IntDef**: Map `TYPE_*` constants to a C++ `enum class`.

---
