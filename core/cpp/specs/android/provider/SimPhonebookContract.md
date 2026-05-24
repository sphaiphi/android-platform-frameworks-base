# SimPhonebookContract - Reverse Engineering Documentation

## Executive Summary
`SimPhonebookContract` defines the contract for accessing contacts stored directly on SIM cards (ADN, FDN, SDN).

## Architecture Overview
- **Authority**: `com.android.simphonebook`.
- **Inner Classes**:
    -   `SimRecords`: Operations on specific records.
    -   `ElementaryFiles`: Discovery of supported files (EF_ADN, etc.) and capacities.

## Detailed Functionality
-   **Elementary Files**: ADN (Abbreviated Dialing Number - User contacts), FDN (Fixed Dialing Number), SDN (Service Dialing Number).
-   **Operations**:
    -   Query `ElementaryFiles` to find valid subscription IDs and capacities.
    -   Query/Insert/Update/Delete `SimRecords` to manage contacts.
-   **Constraints**: Names and numbers have strictly limited lengths and character sets (GSM 7-bit, etc.) managed by the SIM hardware.

## Data Model
-   **Columns**: `PHONE_NUMBER`, `NAME`, `RECORD_NUMBER`, `SUBSCRIPTION_ID`.

## API Reference
-   `SimRecords.getContentUri(subId, efType)`.
-   `SimRecords.getItemUri(...)`.
-   `ElementaryFiles.CONTENT_URI`.

## Java-to-C++ Translation Guide
-   **URI Structure**: `content://com.android.simphonebook/subid/<subId>/<efType>`.
