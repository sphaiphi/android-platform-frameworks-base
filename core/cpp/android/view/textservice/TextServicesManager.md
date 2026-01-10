# TextServicesManager - Reverse Engineering Documentation

## Executive Summary
The system service manager for Text Services (Spell Checking). It mediates between apps and the `TextServicesManagerService`.

## Architecture
*   **Service Wrapper**: `ITextServicesManager`.
*   **Session Creation**: `newSpellCheckerSession` binds to the service and creates a session.

## Java-to-C++ Translation Guide
*   **Binder**: Wraps `ITextServicesManager`.
