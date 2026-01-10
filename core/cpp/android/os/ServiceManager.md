# ServiceManager - Reverse Engineering Documentation

## Executive Summary
`ServiceManager` is the static registry for system services. It allows clients to find services (by name) and services to register themselves. It caches references to avoid repeated lookups.

## Architecture Overview
-   **Role**: Service Directory Client.
-   **Backend**: `IServiceManager` (Binder interface to `servicemanager` native process).
-   **Caching**: `sCache` (Map<String, IBinder>) stores fetched services.

## Detailed Functionality
-   **`getService(String name)`**:
    1.  Checks `sCache`.
    2.  If missing, calls `rawGetService(name)` (Binder call).
    3.  Wraps result in `Binder.allowBlocking()` (usually).
    4.  Caches and returns.
-   **`addService(String name, IBinder service)`**: Registers a service. Restricted to system UID/root.
-   **`listServices()`**: Returns all registered service names.
-   **`waitForService()`**: Blocks until a service is registered (useful during boot).

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::defaultServiceManager()` returning `sp<IServiceManager>`.
-   **Usage**:
    -   `sm->getService(String16("name"))`
    -   `sm->addService(String16("name"), binder)`
-   **Native Header**: `binder/IServiceManager.h`.

## Implementation Risks
-   **Deadlock**: Waiting for a service that depends on you.
-   **Security**: Only privileged processes can add services.
