# Context - Reverse Engineering Documentation

## Executive Summary
`Context` is an abstract class whose implementation is provided by the Android system. It allows access to application-specific resources and classes, as well as up-calls for application-level operations such as launching activities, broadcasting and receiving intents, etc.

## Architecture Overview
- **Inheritance:** `Object`.
- **Implementers:** `ContextImpl` (Internal), `ContextWrapper`, `Activity`, `Service`, `Application`.
- **Pattern:** Decorator (`ContextWrapper`) and Facade.

## Detailed Functionality

### Resource Access
- **`getResources()`, `getAssets()`, `getTheme()`**: Access to APK assets, compiled resources, and styling.
- **`getSharedPreferences(String, int)`**: Access to persistent key-value storage.

### Component Lifecycle & Activation
- **`startActivity(Intent)`**: Launches a new Activity.
- **`sendBroadcast(Intent)`**: Dispatches an intent to all interested `BroadcastReceiver`s.
- **`startService(Intent)`, `bindService(...)`**: Manages background services.

### System Service Discovery
- **`getSystemService(String)`**: The gateway to all system-level features (Window Manager, Notification Manager, Location Manager, etc.).

### Filesystem & Database Management
- **`getFilesDir()`, `getCacheDir()`**: Provides paths to private app storage.
- **`openOrCreateDatabase(...)`**: Manages SQLite databases.

### Permission and Security
- **`checkPermission(...)`, `enforcePermission(...)`**: Validates whether the caller or the app itself has specific rights.
- **`grantUriPermission(...)`, `revokeUriPermission(...)`**: Fine-grained access control for `content://` URIs.

### Attribution and Contextualization
- **`createAttributionContext(String)`**: Creates a context tagged for specific feature auditing.
- **`createDeviceProtectedStorageContext()`**: Redirects file IO to encrypted storage available before user unlock.
- **`isUiContext()`**: Identifies if the context is safe for UI operations (has a WindowManager/Display).

## Data Model
- **`mPackageName`**: The package ID.
- **`mUser`**: The `UserHandle` (for multi-user support).
- **`mDisplayId`**: The associated display.

## API Reference
- `public abstract Object getSystemService(String name)`
- `public abstract void startActivity(Intent intent)`
- `public abstract Resources getResources()`
- `public abstract File getFilesDir()`

## Java-to-C++ Translation Guide
- **Abstract Interface**: In C++, `Context` should be a pure virtual class or a handle-based interface.
- **Singleton Services**: Many system services in Java are cached in `ContextImpl`. C++ should use a similar caching mechanism or a global service registry.
- **RAII**: File paths and database handles should be managed with RAII.

## Implementation Risks
- **Memory Leaks**: `Context` objects (especially Activities) are large and easily leaked if held in static variables or long-lived background threads.
- **Context Misuse**: Using a non-UI `Context` (like `Application`) to inflate views or show dialogs leads to crashes or incorrect styling.
