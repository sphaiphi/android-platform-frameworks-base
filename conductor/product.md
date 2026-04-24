# Initial Concept
The Android Framework Core project aims to provide a modern C++ implementation of fundamental Android operating system components. By leveraging C++23, it offers high-performance, type-safe, and low-overhead alternatives to traditional Java-based framework APIs, specifically targeting NDK developers who require direct, efficient access to system services.

# Product Vision
To establish a premier native framework for Android system development that eliminates JNI overhead, minimizes memory footprint, and provides developers with a robust, modern C++ API surface for building core system components and performance-critical applications.

# Target Users
*   **NDK Developers:** Developers building performance-sensitive applications or libraries who require low-level system API access without the complexity and overhead of JNI.

# Core Goals
*   **Native API Parity:** Implement C++ equivalents for essential Java framework classes such as `Intent` (including `ComponentName`, `Uri`, `ClipData`), `Bundle`, `Context`, `IntentFilter`, and others.
*   **Performance & Efficiency:** Reduce system memory overhead and improve execution speed for core services by utilizing native implementation of structures like `Rect` and `Intent`.
*   **JNI Reduction:** Enable seamless interaction with Android system services directly from C++, removing the need for bridge code.

# Functional Priorities
*   **Component Lifecycle & IPC:** Implementation of `Activity`, `NativeActivity`, `ActivityThread`, `ActivityManager`, `Instrumentation`, `Application`, `Notification`, `AppOpsManager`, `Fragment`, `Intent`, `Bundle`, `IntentFilter`, and `Context` for robust communication, alongside deep integration with AIDL and `ServiceManager`.
*   **UI & Window Management:** High-performance surface control and view system abstractions using `SurfaceControl` and related native APIs. Includes foundational UI widgets (`TextView`, `Button`), layout systems (`LinearLayout`, `FrameLayout`, `RelativeLayout`), and a configuration-aware resource resolution system (`Resources`, `AssetManager`, `Configuration`, `DisplayMetrics`) for building complex native interfaces.
*   **System Services:** Providing native access to core system functionality through well-defined IPC interfaces.

# Key Requirements
*   **Modern C++ Excellence:** Strict adherence to C++23 standards, utilizing safety-first idioms and the C++ Core Guidelines.
*   **Performance-First Design:** Implementation of zero-cost abstractions to maintain maximum performance.
*   **Reliability:** Mandatory high test coverage, validated through the Android Compatibility Test Suite (CTS).
*   **Compatibility:** Maintaining binary compatibility with existing NDK libraries to ensure broad ecosystem support.
