# UserHandle - Reverse Engineering Documentation

## Executive Summary
`UserHandle` represents a user on the system. It encapsulates a `userId` (integer) and provides utilities to convert between UIDs (which contain user and app ID) and user IDs.

## Architecture Overview
-   **Pattern**: Value Object / Identifier.
-   **Multi-User**: Android UIDs are composed: `uid = userId * 100000 + appId`. `UserHandle` helps manipulate this.

## Data Model
-   **Constants**: `USER_SYSTEM` (0), `USER_ALL` (-1), `USER_CURRENT` (-2).
-   **Ranges**: `PER_USER_RANGE` (100000).

## API Reference
-   `getUserId(int uid)`: Extracts user ID from kernel UID.
-   `getAppId(int uid)`: Extracts app ID (base UID) from kernel UID.
-   `getUid(int userId, int appId)`: Composes kernel UID.
-   `isSystem()`: Checks if user is 0.

## Java-to-C++ Translation Guide
-   **Equivalent**: `cutils/multiuser.h` provides C macros and functions (`multiuser_get_user_id`, `multiuser_get_app_id`).
-   **Binder**: Passed as an integer in Parcels.
