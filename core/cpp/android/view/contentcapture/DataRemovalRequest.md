# DataRemovalRequest - Reverse Engineering Documentation

## Executive Summary
Request object for removing content capture data. Can be "for everything" or for specific LocusIDs.

## Data Model
*   `mPackageName`.
*   `mForEverything`: boolean.
*   `mLocusIdRequests`: List of `LocusIdRequest` (LocusId + flags).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
