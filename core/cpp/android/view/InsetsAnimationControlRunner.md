# InsetsAnimationControlRunner - Reverse Engineering Documentation

## Executive Summary
`InsetsAnimationControlRunner` is a common interface for objects that run window inset animations. it abstracts the differences between different types of animations (app-driven, system-driven, or resizing animations) and provides a unified way to manage their lifecycle.

## Architecture Overview
*   **Role**: Animation runner abstraction.
*   **Key Interface**: Extends `WindowInsetsAnimationController` (via subclasses).

## Detailed Functionality
*   **`getTypes()`**: Returns the bitmask of `InsetsType` managed by this runner.
*   **`willUpdateSurface()`**: Indicates if the runner is still actively modifying `SurfaceControl` properties.
*   **`cancel()`**: Aborts the animation.
*   **`SurfaceParamsApplier`**: An inner interface used to batch surface updates (translation, alpha, crop) to the compositor.

## Java-to-C++ Translation Guide
*   **Hierarchy**: In C++, this should be a virtual base class for all native inset animation controllers.
*   **Parceling**: Defines `dumpDebug` for proto-based debugging output.

## Implementation Risks
*   **Multi-Type Contention**: If multiple runners try to control the same inset type, the system must correctly revoke control from the older runner.
