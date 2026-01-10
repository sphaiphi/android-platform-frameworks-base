# InputMethodServiceInternal - Reverse Engineering Documentation

## Executive Summary
`InputMethodServiceInternal` is a package-private interface that exposes internal methods of `InputMethodService` to other framework classes (specifically `IInputMethodWrapper` and `RemoteInputConnection`). It allows these helper classes to callback into the service implementation without exposing these methods as public APIs.

## API Reference
*   `getContext()`: Returns the context.
*   `exposeContent(InputContentInfo, InputConnection)`: Permission grant helper.
*   `notifyUserActionIfNecessary()`: User activity tracking (for rotation/timeout).
*   `dump(...)`: Debug dumping.
*   `triggerServiceDump(...)`: Proto dumping.
*   `isServiceDestroyed()`: Lifecycle check.

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual class / abstract base class.
*   **Usage**: Allows decoupling the Binder Stub (`IInputMethodWrapper`) from the concrete `InputMethodService` class while maintaining access to internals.
