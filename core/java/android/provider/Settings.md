# Settings - Reverse Engineering Documentation

## Executive Summary
`Settings` is the central provider and utility class for accessing and managing system-wide settings, preferences, and configurations in Android. It exposes three main tables: System, Secure, and Global, and defines a vast array of Intent actions for launching specific settings screens.

## Architecture Overview
- **Authority**: `settings`.
- **Type**: Contract / Utility.
- **Provider**: `SettingsProvider` (not in this package, but this is the contract).
- **Tables**:
    -   `Global`: Device-wide preferences that apply to all users.
    -   `System`: Legacy, user-specific preferences (mostly replaced by Global/Secure).
    -   `Secure`: Sensitive, user-specific preferences that apps cannot modify without permission.
-   **Config**: `Config` inner class (implied) for server-side flags (DeviceConfig).

## Detailed Functionality
-   **Intents**: Defines standard `ACTION_*_SETTINGS` intents (e.g., `ACTION_WIFI_SETTINGS`, `ACTION_SETTINGS`).
-   **Extras**: Keys for passing data to settings activities (e.g., `EXTRA_SUB_ID`).
-   **Permissions**: Many settings require `WRITE_SETTINGS` or `WRITE_SECURE_SETTINGS`.

## Data Model
-   **Keys**: String constants identifying individual settings.
-   **Values**: Stored as strings, but helper methods convert to/from int, long, float, boolean.

### Inner Classes (Partitions)

#### 1. Settings.System (Legacy)
Contains miscellaneous system preferences. Most settings here are legacy and have been moved to `Secure` or `Global`.
-   **URI**: `content://settings/system`
-   **Access**: User-specific.
-   **Examples**: `SCREEN_BRIGHTNESS`, `SCREEN_OFF_TIMEOUT`, `SOUND_EFFECTS_ENABLED`.

#### 2. Settings.Secure
Contains secure system settings. Applications can read these but usually cannot write them without `WRITE_SECURE_SETTINGS` permission (signature/privileged or granted via ADB).
-   **URI**: `content://settings/secure`
-   **Access**: User-specific.
-   **Examples**: `LOCATION_MODE`, `DEFAULT_INPUT_METHOD`, `ANDROID_ID`, `ACCESSIBILITY_ENABLED`.

#### 3. Settings.Global
Contains global system settings that apply to all users.
-   **URI**: `content://settings/global`
-   **Access**: Device-wide (read-only for most apps, write requires `WRITE_SECURE_SETTINGS`).
-   **Examples**: `AIRPLANE_MODE_ON`, `ADB_ENABLED`, `DATA_ROAMING`, `AUTO_TIME`.

#### 4. Settings.Config
Contract for the `config` table, often mapped to `DeviceConfig` for server-side flag updates.
-   **URI**: `content://settings/config`

## API Reference
-   `Settings.System.getString(...)`, `putString(...)`.
-   `Settings.Secure.getString(...)`, `putString(...)`.
-   `Settings.Global.getString(...)`, `putString(...)`.
-   `ACTION_SETTINGS`, `ACTION_WIFI_SETTINGS`, etc.

## Java-to-C++ Translation Guide
-   **Binder Interface**: Accessing Settings from C++ typically involves using the `ISettingsProvider` binder interface directly or `system_property` calls for some read-only values.
-   **ContentProvider**: Can be accessed via `IContentProvider::call` methods if needed.
-   **Partitioning**: Crucial to know which partition (System/Secure/Global) a key belongs to when querying via Binder.
