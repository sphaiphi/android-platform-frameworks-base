# LocaleManager - Reverse Engineering Documentation

## Executive Summary
`LocaleManager` is a system service that provides access to granular locale settings for applications. It allows apps to set their own language preferences (per-app locales) and override their list of supported locales dynamically. It acts as a client-side wrapper around the `ILocaleManager` AIDL interface.

## Architecture Overview
- **Service Integration**: Managed by `SystemServiceRegistry` and accessible via `Context.getSystemService(Context.LOCALE_SERVICE)`.
- **Backend Communication**: Uses `ILocaleManager` for IPC with the system server.
- **Scope**: Supports operations for the calling app and, with appropriate permissions, for other packages.

## Detailed Functionality

### setApplicationLocales(LocaleList locales)
**Purpose**: Configures the UI locales for the calling app.
**Mechanism**: Calls `mService.setApplicationLocales` with the app's package name and current user ID. This triggers a configuration change in the application and optionally restarts activities.

### getApplicationLocales(String appPackageName)
**Purpose**: Retrieves the current UI locales for a specific app.
**Logic**: Proxies the request to `mService.getApplicationLocales`. Requires `READ_APP_SPECIFIC_LOCALES` permission for reading other apps' locales.

### setOverrideLocaleConfig(LocaleConfig localeConfig)
**Purpose**: Dynamically updates the list of supported locales for an app without a software update.
**Mechanism**: Persists the provided `LocaleConfig` in a system file for future access.

### getSystemLocales()
**Purpose**: Returns the overall system locales, ignoring any app-specific overrides.
**Mechanism**: Calls `mService.getSystemLocales`.

## API Reference
- `public void setApplicationLocales(LocaleList locales)`: Sets app-specific locales.
- `public LocaleList getApplicationLocales()`: Gets app-specific locales.
- `public LocaleList getSystemLocales()`: Gets the global system locales.
- `public void setOverrideLocaleConfig(LocaleConfig localeConfig)`: Updates supported languages metadata.
- `public LocaleConfig getOverrideLocaleConfig()`: Retrieves the current override configuration.

## Java-to-C++ Translation Guide
- **AIDL Integration**: Use the AIDL-generated C++ interface `android::app::ILocaleManager`.
- **System Service Lookup**: Use `android::ServiceManager` to retrieve the `locale` service binder.
- **LocaleList**: Map to `android::os::LocaleList` in C++.
- **Permissions**: Ensure the native caller has the necessary permissions (e.g., `CHANGE_CONFIGURATION` or `READ_APP_SPECIFIC_LOCALES`) if performing privileged operations.

## Implementation Risks
- **Remote Exceptions**: All methods that call into the service must handle `RemoteException` and potentially rethrow as `RuntimeException` or return an error code.
- **Configuration Changes**: Setting locales triggers a system-wide configuration update for the package. The C++ layer must ensure it is prepared for `onConfigurationChanged` callbacks if it is part of an active process.
- **State Persistence**: Per-app locales are persisted by the system across reboots and handled by backup/restore. The C++ implementation should not attempt to manage its own persistence for this data.
