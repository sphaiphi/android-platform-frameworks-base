# ServiceConnection - Reverse Engineering Documentation

## Executive Summary
`ServiceConnection` is an interface for monitoring the state of a bound service. It receives callbacks when the service connects, disconnects (crashes), or the binding dies.

## Architecture Overview
- **Type:** Interface.
- **Usage:** Passed to `Context.bindService`.

## API Reference
- `void onServiceConnected(ComponentName name, IBinder service)`
- `void onServiceDisconnected(ComponentName name)`
- `void onBindingDied(ComponentName name)`
- `void onNullBinding(ComponentName name)`

## Java-to-C++ Translation Guide
- **Interface**: Abstract class.
- **Binder**: `onServiceConnected` receives an `IBinder`, which is `sp<IBinder>`.

## Implementation Risks
- **Deadlocks**: Callbacks happen on the main thread (usually). Blocking in these callbacks hangs the app.