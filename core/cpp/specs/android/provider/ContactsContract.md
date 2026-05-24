# ContactsContract - Reverse Engineering Documentation

## Executive Summary
`ContactsContract` is the massive, central contract for the `ContactsProvider2`. It defines the 3-tier data model (Accounts -> RawContacts -> Contacts) and all associated data tables (Data, Phone, Email, etc.), as well as directories, aggregation, and profile information.

## Architecture Overview
- **Authority**: `com.android.contacts`.
- **Data Model**:
    1.  **Contacts**: Aggregate level. Read-only mostly.
    2.  **RawContacts**: Account level.
    3.  **Data**: Details (Phone, Email, etc.) linked to RawContact.
-   **Inner Classes**: Hundreds of classes defining specific tables (`Data`, `RawContacts`, `Contacts`) and data kinds (`CommonDataKinds.Phone`, etc.).

## Detailed Functionality
-   **URIs**:
    -   `AUTHORITY_URI`: `content://com.android.contacts`.
    -   `Contacts.CONTENT_URI`: Aggregate contacts.
    -   `RawContacts.CONTENT_URI`: Raw contacts.
    -   `Data.CONTENT_URI`: All data rows.
    -   `Profile.CONTENT_URI`: User's profile.
-   **Querying**: Supports complex filtering (`CONTENT_FILTER_URI`), lookup keys (`CONTENT_LOOKUP_URI`), and directories (`Directory`).
-   **Aggregation**: Automatic and manual (`AggregationExceptions`) aggregation of RawContacts into Contacts.
-   **Display Name**: Computed from various name fields based on locale.

## Key Sub-components
-   **CommonDataKinds**: Definitions for `Phone`, `Email`, `Photo`, `StructuredName`, `Organization`, etc.
-   **Directory**: Interface for external directories (e.g., Exchange GAL).
-   **Intents**: Helpers for creating contact-related intents.
-   **QuickContact**: UI helpers.

## Java-to-C++ Translation Guide
-   **Complexity**: This is one of the largest contracts in Android. Implementing a full client in C++ requires mapping dozens of tables and hundreds of columns.
-   **Focus**: Focus on the specific tables needed (usually `Data` view joined with `RawContacts`/`Contacts`).
-   **Constants**: Map the authority and column names.
-   **Data Kinds**: Map MIME types (`vnd.android.cursor.item/phone_v2`, etc.) to identify data rows.
