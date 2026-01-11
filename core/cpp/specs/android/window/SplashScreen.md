# SplashScreen - Reverse Engineering Documentation

## Executive Summary
`SplashScreen` is the client-facing interface for controlling the startup splash screen of an Activity. It allows setting a custom exit animation listener and clearing it.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `interface`
*   **Role**: Public API.
*   **Inner Implementation**: `SplashScreenImpl` handles the actual logic and communication with `SplashScreenManagerGlobal`.

## Detailed Functionality

### `SplashScreenImpl`
*   Holds `mActivityToken` (IBinder).
*   **Exit Listener**: When an app sets an exit listener, it registers with the global manager.
*   **Theme Persistence**: `setSplashScreenTheme` calls `AppGlobals.getPackageManager().setSplashScreenTheme`.

### `SplashScreenManagerGlobal`
*   Singleton.
*   Manages a list of `SplashScreenImpl`s.
*   **Dispatch**: `handOverSplashScreenView` -> finds impl -> calls listener.

## Java-to-C++ Translation Guide
*   This is high-level app logic. C++ translation is only relevant if implementing the Activity/App framework itself.
*   **Data Structures**: `std::map<IBinder, SplashScreenImpl*>`.

## Implementation Risks
*   **Thread Safety**: Access to global lists must be synchronized.
