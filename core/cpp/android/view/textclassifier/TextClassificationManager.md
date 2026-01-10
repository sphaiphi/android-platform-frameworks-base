# TextClassificationManager - Reverse Engineering Documentation

## Executive Summary
System service manager for Text Classification. Provides access to `TextClassifier` instances (system, local, or custom). Manages sessions via `TextClassificationSessionFactory`.

## Architecture
*   **Service Access**: Determines which classifier to return based on settings.
*   **Session Factory**: Creates `TextClassificationSession`.

## Java-to-C++ Translation Guide
*   **Manager**: Client-side manager logic.
