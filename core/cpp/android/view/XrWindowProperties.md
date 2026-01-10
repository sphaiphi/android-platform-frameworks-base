# XrWindowProperties - Reverse Engineering Documentation

## Executive Summary
`XrWindowProperties` defines a set of property keys and constants used in application manifests to inform the system about XR (Extended Reality) specific windowing behaviors. it controls launch modes, safety boundaries, and animation styles for immersive XR activities.

## Data Model

### 1. Launch Modes
*   **`XR_ACTIVITY_START_MODE_FULL_SPACE_UNMANAGED`**: The app renders the entire 3D space (e.g., via OpenXR).
*   **`XR_ACTIVITY_START_MODE_FULL_SPACE_MANAGED`**: The system renders the activity from a provided scene graph.
*   **`XR_ACTIVITY_START_MODE_HOME_SPACE`**: Standard 2D window in the XR home environment.

### 2. Safety Boundaries
*   **`XR_BOUNDARY_TYPE_LARGE`**: Recommends a large clear space for the user.
*   **`XR_BOUNDARY_TYPE_NO_RECOMMENDATION`**: Standard system boundary behavior.

## Detailed Functionality
*   **Manifest Integration**: Keys like `PROPERTY_ACTIVITY_XR_START_MODE` are read by the `ActivityTaskManager` during process startup to configure the XR environment.

## Java-to-C++ Translation Guide
*   **Constants**: Map these strings to a C++ header for use in the system-level window manager.

## Implementation Risks
*   **Mode Conflict**: Incorrectly specifying `UNMANAGED` for a standard 2D app will lead to a black screen or crash, as the system expects the app to drive the scene graph.
