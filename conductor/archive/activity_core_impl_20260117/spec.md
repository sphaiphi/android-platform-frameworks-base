# Specification: Activity Component Implementation (Core)

## 1. Overview
Implement the core C++ components for Activity management as defined in the `core/cpp/specs/android/app/` specifications. This track focuses on establishing the foundational native infrastructure for activity lifecycles, application startup, and context management, mimicking the Android framework's internal architecture.

## 2. Functional Requirements
The implementation will cover the following classes and their key responsibilities:

### 2.1 Activity (`Activity.md`)
*   **Lifecycle Management:** Implementation of core lifecycle state transitions (`onCreate`, `onStart`, `onResume`, `onPause`, `onStop`, `onDestroy`).
*   **Intent Handling:** Mechanisms for retrieving and setting intents (`getIntent`, `setIntent`) and initiating activity starts (`startActivity`).
*   **Configuration Changes:** Support for handling system configuration changes via `onConfigurationChanged`.

### 2.2 ActivityThread (`ActivityThread.md`)
*   **Main Loop:** Implementation of the main execution loop and message handling (the `H` handler) for the process.
*   **Process Binding:** Support for `bindApplication` and the initialization sequence.
*   **Activity Scheduling:** Implementation of launch logic, including `handleLaunchActivity` and `performLaunchActivity`.

### 2.3 ContextImpl (`ContextImpl.md`)
*   **System Services:** Provision of access to system-level services via `getSystemService`.
*   **Resources:** Integration with resource and asset management systems.
*   **App Metadata:** Access to package names, application info, and local file/cache directories.

### 2.4 Instrumentation (`Instrumentation.md`)
*   **Factory Methods:** Implementation of `newActivity` and initialization hooks.
*   **Lifecycle Execution:** Methods to drive activity state changes (e.g., `callActivityOnCreate`, `callActivityOnResume`).
*   **Monitoring:** Support for synchronous activity starting and result checking.

## 3. Non-Functional Requirements
*   **Modern C++:** Adherence to C++23 standards and the project's safety-first guidelines (RAII, type safety).
*   **Performance:** Minimal overhead in lifecycle transitions compared to the Java framework.
*   **Parity:** Functional alignment with the referenced Java framework behavior (as described in the markdown specs).

## 4. Acceptance Criteria
1.  **Unit Tests:** All core classes must have unit tests covering the specified functional requirements (Lifecycle transitions, service access, etc.).
2.  **Lifecycle Flow:** A mock `ActivityThread` can successfully launch and drive an `Activity` through a full `onCreate` -> `onResume` cycle using `Instrumentation`.
3.  **Context Access:** An `Activity` can successfully retrieve "mock" system services and its own package name through its `Context`.
4.  **CTS Readiness:** The implementation passes preliminary native validation tests that mirror Android CTS behavior for these components.

## 5. Out of Scope
*   Full UI/View System integration (e.g., `setContentView` and layout inflation) is deferred to a future track.
*   Service and BroadcastReceiver management within `ActivityThread` (focused only on Activities for now).
*   Complex window management and multi-window support.
