# VendorHubInfo - Reverse Engineering Documentation

## Executive Summary
`VendorHubInfo` contains information about a "Vendor Hub," which is similar to a Context Hub but does not run CHRE (Context Hub Runtime Environment). It uses the ContextHub V4 HAL for messaging but implies a different capability set.

## Architecture Overview
- **Pattern**: DTO.
- **Inheritance**: Implements `android.os.Parcelable`.

## Detailed Functionality
- **Fields**: Name, Version, and `ExtendedInfo` (ParcelableHolder for vendor-specific extensions).

## Data Model
- `mName`: `String`.
- `mVersion`: `int`.
- `mExtendedInfo`: `ParcelableHolder`.

## Java-to-C++ Translation Guide
- **Extended Info**: `ParcelableHolder` is an Android construct. In C++, this might map to an opaque blob or a specific AIDL union/parcelable depending on the HAL definition.

## Questions for C++ Team
- How is `ExtendedInfo` handled in the native HAL?
