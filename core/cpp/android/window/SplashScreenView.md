# SplashScreenView - Reverse Engineering Documentation

## Executive Summary
`SplashScreenView` is the Android View that displays the splash screen content. It can be passed to the application to run a custom exit animation. It encapsulates the icon (which might be animated), branding image, and background.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` extends `FrameLayout`
*   **Role**: UI Component.
*   **Parcelable**: `SplashScreenViewParcelable` (Nested class) allows transferring the view state (bitmaps) across processes (from Shell to App).

## Data Model
*   `mIconView`: The center icon (`ImageView` or `SurfaceView`).
*   `mBrandingImageView`: Branding image at bottom.
*   `mSurfacePackage`: `SurfaceControlViewHost.SurfacePackage` (for cross-process rendering of animated icons).

## Detailed Functionality

### Parceling (`SplashScreenViewParcelable`)
*   Instead of parceling the View itself, it parcels bitmaps (`copyDrawable`) and the `SurfacePackage`.
*   **Reconstruction**: The Builder reconstructs the view using these bitmaps/surfaces.

### Icon Animation
*   If the icon is an `IconAnimateListener` (e.g., `AnimatedVectorDrawable`), it sets up a listener to track animation start/end for jank monitoring.

## Java-to-C++ Translation Guide
*   **UI Toolkit**: This is a standard Android View. C++ translation is not applicable unless reimplementing the Android UI toolkit.
*   **SurfacePackage**: `SurfaceControlViewHost.SurfacePackage` maps to `ASurfaceControl` transfer mechanisms.

## Implementation Risks
*   **Bitmap Memory**: Bitmaps are created in shared memory (`createAshmemBitmap`) for IPC.
