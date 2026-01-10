# ZygotePreload - Reverse Engineering Documentation

## Executive Summary
`ZygotePreload` is an interface to be implemented by a class specified in `AndroidManifest.xml` (`android:zygotePreloadName`). It is called by the `AppZygote` when it starts, allowing the application to preload code/data into the zygote process before it forks for isolated services.

## Architecture Overview
*   **Type**: Interface.
*   **Method**: `doPreload(ApplicationInfo appInfo)`.

## Java-to-C++ Translation Guide
*   Interface.
*   Relevant only for Zygote/Process management implementation.

## Implementation Risks
*   None.
