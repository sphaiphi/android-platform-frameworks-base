# SystemService - Reverse Engineering Documentation

## Executive Summary
`SystemService` provides low-level control over `init` services (native daemons) via system properties (`ctl.start`, `ctl.stop`).

## Architecture Overview
-   **Mechanism**: Android Init Property Triggers.
-   **State**: Reads `init.svc.<name>` to check status (`running`, `stopped`).

## API Reference
-   `start(name)`: Sets `ctl.start`.
-   `stop(name)`: Sets `ctl.stop`.
-   `restart(name)`: Sets `ctl.restart`.
-   `waitForState(name, state, timeout)`: Polling loop checking `init.svc.<name>`.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::base::SetProperty`.
-   **Constants**: The state strings ("running", "stopping") are defined by `init`.

## Implementation Risks
-   **Blocking**: `waitForState` uses `SystemProperties` change callbacks to avoid busy waiting, but it blocks the calling thread.
