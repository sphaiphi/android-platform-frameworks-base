# AppZygote - Reverse Engineering Documentation

## Executive Summary
`AppZygote` manages a specialized Zygote process for a specific application. Unlike the system-wide Zygote, this process is spawned on demand to pre-load application-specific code and data, improving startup time for isolated services.

## Architecture Overview
-   **Role**: Process Controller.
-   **Dependencies**: `ZygoteProcess`, `ChildZygoteProcess`.
-   **Lifecycle**: One instance per application/UID. Connects to the main Zygote to spawn the App Zygote, then manages the connection to that child process.

## Detailed Functionality
-   **Startup**: Uses `Process.ZYGOTE_PROCESS.startChildZygote(...)` to launch `com.android.internal.os.AppZygoteInit`.
-   **Preloading**: Calls `mZygote.preloadApp(mAppInfo, abi)` to load APK code into the new Zygote.
-   **Process Spawning**: The `startProcess` method proxies to the child Zygote's socket to fork new isolated services.

## Data Model
-   **Identity**: `mZygoteUid`, `mZygoteUidGidMin`, `mZygoteUidGidMax` define the UID range for the isolated processes.
-   **Connection**: Maintains a `ChildZygoteProcess` reference (`mZygote`).

## Java-to-C++ Translation Guide
-   **Process Management**: Corresponds to `app_zygote` logic in `frameworks/base/cmds/app_process`.
-   **Socket Protocol**: Uses standard Zygote socket commands (`--start-child-zygote`, `--preload-app`).
