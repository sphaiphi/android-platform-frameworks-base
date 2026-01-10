# NanoAppFilter - Reverse Engineering Documentation

## Executive Summary
`NanoAppFilter` is a deprecated class used for filtering nanoapp queries (by App ID, Version, Vendor, etc.).

## Architecture Overview
- **Status**: **DEPRECATED**.
- **Role**: Filter criteria object.

## Detailed Functionality
- Supports filtering by ID, Version (>, <, ==), and Vendor mask.

## Data Model
- `mAppId`, `mAppVersion`, `mVersionRestrictionMask`, `mAppIdVendorMask`.

## Java-to-C++ Translation Guide
- **Replacement**: Modern APIs typically return all nanoapps (`queryNanoApps`), and filtering happens on the client side, or via simple ID checks.

## Questions for C++ Team
- None.
