# FragmentHostCallback - Reverse Engineering Documentation

## Executive Summary
`FragmentHostCallback` acts as the bridge between the `FragmentManager` and the host system (Activity/Context). It abstracts the host's capabilities (like starting activities, finding views) for the fragments.

## Architecture Overview
*   **Inheritance**: `FragmentContainer`.
*   **Generics**: `<E>` (Type of the host object, e.g., Activity).

## Detailed Functionality
*   **Services**: Provides `LayoutInflater`, `Handler`, `WindowAnimations`.
*   **Actions**: `onStartActivityFromFragment`, `onRequestPermissionsFromFragment`.
*   **Manager Ownership**: Owns the `FragmentManagerImpl`.

## Java-to-C++ Translation Guide
*   **Bridge Pattern**: Connects the fragment system to the OS/App runtime.

## Implementation Risks
*   **Coupling**: Tightly coupled with Activity/Context.
