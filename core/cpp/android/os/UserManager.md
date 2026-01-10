# UserManager - Reverse Engineering Documentation

## Executive Summary
`UserManager` manages users and profiles. It allows creating, removing, and querying users, checking restrictions (`DISALLOW_CONFIG_WIFI`, etc.), and handling user lifecycle events.

## Architecture Overview
-   **Role**: User Management Client.
-   **Service**: `IUserManager` (Binder).
-   **Concepts**:
    -   **User**: Distinct environment.
    -   **Profile**: Linked user (e.g., Work Profile) sharing some UI/Apps with a parent.
    -   **Guest**: Ephemeral user.

## Detailed Functionality
-   **Creation**: `createUser`, `createProfile`.
-   **Querying**: `getUsers()`, `getProfiles(int userId)`, `getUserInfo(int userId)`.
-   **Restrictions**: `hasUserRestriction(String key)`. Checks `Bundle` of restrictions propagated from `DevicePolicyManager`.
-   **Quiet Mode**: `requestQuietModeEnabled` (pauses work profile).

## Java-to-C++ Translation Guide
-   **Binder**: Interact with `IUserManager`.
-   **UserInfo**: The `UserInfo` parcelable (defined in `android.content.pm`) maps to a C++ struct containing id, name, flags, etc.
