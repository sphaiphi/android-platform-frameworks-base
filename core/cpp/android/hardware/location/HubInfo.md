# HubInfo - Reverse Engineering Documentation

## Executive Summary
`HubInfo` is a unified container (Parcelable) that can hold either `ContextHubInfo` or `VendorHubInfo`. It serves as a polymorphic wrapper for discovering different types of hubs via the Offload API.

## Architecture Overview
- **Pattern**: Union / Variant Wrapper.
- **Inheritance**: Implements `android.os.Parcelable`.

## Detailed Functionality
- **Types**: `TYPE_CONTEXT_HUB` (0), `TYPE_VENDOR_HUB` (1).
- **Storage**: Holds references to both info types, but only one is populated based on `mType`.

## Data Model
- `mId`: `long` (Common ID).
- `mType`: `int`.
- `mContextHubInfo`: `ContextHubInfo` (Nullable).
- `mVendorHubInfo`: `VendorHubInfo` (Nullable).

## Java-to-C++ Translation Guide
- **Data Structure**: `std::variant<ContextHubInfo, VendorHubInfo>` or a struct with a union.
- **Serialization**: Write type, then write the active member.

## Questions for C++ Team
- None.
