# GEMINI.md: Android Framework Core

This project is the core of the Android framework, containing the source code for fundamental components of the Android operating system.

## Project Overview

This is a project for developing the Android framework using modern C++ based on the Android Native Development Kit (NDK). It provides the core components of the Android operating system. The Java sources in the project serve as references for the C++ implementation. The code includes key classes that are central to the Android application model, UI, and component lifecycle.

**Key Technologies:**

*   **C++:** The primary language for the Android framework development, using modern C++ standards.
*   **Java:** Sources are included for reference to guide the C++ implementation.
*   **AIDL (Android Interface Definition Language):** Used for defining the programming interface that both client and service agree upon in order to communicate with each other using interprocess communication (IPC).
*   **CMAKE:** The build system used for compiling the C++ code.

**Architecture:**

The Android framework is a layered architecture. The C++ implementation provides the core functionality, with Java sources as references. The files are organized in the `frameworks/base/core` directory, focusing on the C++ API framework layer.

## Building and Running

The project uses CMAKE as the build system to compile the modern C++ code based on the Android NDK.

**Build System:**

**CMAKE:** Used for building the C++ components.

**Key Build Files:**

*   `CMakeLists.txt`: Defines the build configuration for the C++ project.

## Development Conventions

The codebase follows strict coding conventions and a well-defined structure.

*   **Namespace Structure:** The code is organized into namespaces that mirror the Android SDK structure (e.g., `android::app`, `android::view`, `android::widget`).
*   **Licensing:** The code is licensed under the Apache License, Version 2.0, as indicated in the file headers.
*   **Documentation:** The code is documented with comments suitable for C++ documentation tools.
*   **Testing:** The Android project has a comprehensive testing strategy, including unit tests, integration tests, and compatibility tests (CTS) for the C++ components.

## Key Files Examined

*   `core/cpp/android/view/SurfaceControl.aidl`: Interface for surface control in the UI layer.
*   `core/cpp/android/os/Bundle.cpp`: A general-purpose key-value store for passing data (C++ version).
*   `core/cpp/android/content/Intent.cpp`: A messaging object for requesting actions (C++ version).
*   `core/cpp/android/content/pm/PackageManager.cpp`: Class for retrieving package information (C++ version).
*   `core/cpp/android/content/Context.cpp`: Interface to application environment information (C++ version).
*   `CMakeLists.txt`: The build configuration file for the C++ project.
*   `core/java/overview.html`: A brief overview of the Android APIs (for reference).

This `GEMINI.md` file provides a high-level overview of the Android framework project developed in modern C++. Given the size and complexity of the codebase, this analysis is just a starting point for further exploration.
