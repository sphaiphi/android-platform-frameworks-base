# AutofillId - Reverse Engineering Documentation

## Executive Summary
A unique identifier for an autofill node. It can represent a real View (using view ID) or a virtual view (using virtual child ID). It also tracks the autofill session ID.

## Data Model
*   `mViewId`: int.
*   `mVirtualIntId` / `mVirtualLongId`: Virtual IDs.
*   `mSessionId`: int.
*   `mFlags`: Bitmask indicating if virtual, has session, etc.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Identifier**: Primary key logic for autofill maps.
