# VideoView - Reverse Engineering Documentation

## Executive Summary
`VideoView` is a high-level UI component that wraps `MediaPlayer` and `SurfaceView` to simplify video playback. It manages the underlying `Surface`, handles aspect ratio-aware measurement, coordinates with `AudioManager` for audio focus, and provides a bridge to `MediaController` for playback controls. It also supports subtitle rendering (WebVTT, TTML, CEA-708, etc.) via a nested `SubtitleController`.

## Architecture Overview
- **Inheritance**: Extends `android.view.SurfaceView`.
- **Interfaces**:
    - `MediaController.MediaPlayerControl`: Provides the API for `MediaController` to control playback (play, pause, seek).
    - `SubtitleController.Anchor`: Allows it to act as the rendering site for subtitles.
- **Internal State Machine**: Tracks `mCurrentState` and `mTargetState` (e.g., IDLE, PREPARING, PLAYING, PAUSED) to ensure `MediaPlayer` commands are only issued in valid states.
- **Composition**:
    - `MediaPlayer`: The engine for decoding and rendering.
    - `AudioManager`: Manages audio focus.
    - `SubtitleController`: Manages subtitle tracks and rendering widgets.

## Detailed Functionality

### Measurement (`onMeasure`)
**Purpose**: Calculates the view dimensions while preserving the video's aspect ratio.
**Algorithm**:
1.  Resolves default width/height using `getDefaultSize`.
2.  If video dimensions are known:
    - Analyzes `MeasureSpec` modes (EXACTLY, AT_MOST).
    - If width is fixed (EXACTLY), height is calculated as `width * mVideoHeight / mVideoWidth`.
    - If both are flexible, it attempts to use the actual video size, scaling down to fit within the spec if necessary.
    - Cross-multiplication (`mVideoWidth * height < width * mVideoHeight`) is used to detect and correct aspect ratio mismatches.

### Video Initialization (`openVideo`)
**Purpose**: Sets up the `MediaPlayer` and prepares it for playback.
**Algorithm**:
1.  Validates that `mUri` and `mSurfaceHolder` are available.
2.  Requests audio focus via `mAudioManager` (unless configured otherwise).
3.  Instantiates `MediaPlayer`.
4.  Configures `SubtitleController` with standard renderers (WebVTT, TTML, etc.) and anchors it to `this`.
5.  Sets data source (`mUri`), display surface, and audio attributes.
6.  Registers various listeners (OnPrepared, OnCompletion, OnError, etc.).
7.  Calls `prepareAsync()`.
8.  Enqueues any `mPendingSubtitleTracks`.

### State Management
- **`start()` / `pause()` / `seekTo()`**: These methods check `isInPlaybackState()` (not ERROR, IDLE, or PREPARING) before delegating to `mMediaPlayer`.
- **`mTargetState`**: Stores the desired state even if the player is still preparing. Once preparation is complete, the `mPreparedListener` checks `mTargetState` to auto-start playback if requested.

### Error Handling
- **`mErrorListener`**:
    - Switches state to `STATE_ERROR`.
    - If the app provided an `OnErrorListener`, it is called.
    - Otherwise, it displays a standard `AlertDialog` with localized error messages (e.g., "Sorry, this video cannot be played").

### Subtitle Rendering
- **`setSubtitleWidget`**: Attaches a `RenderingWidget` provided by the `SubtitleController`.
- **`draw`**: Overridden to call `mSubtitleWidget.draw(canvas)` after the base `SurfaceView` drawing. This ensures subtitles are overlaid on the video surface.
- **`onLayout`**: Ensures the subtitle widget size matches the `VideoView` content area.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mCurrentState` | `int` | Internal state of the `VideoView`. |
| `mTargetState` | `int` | Desired state (used to resume actions after preparation). |
| `mMediaPlayer` | `MediaPlayer` | Native media player wrapper. |
| `mSurfaceHolder` | `SurfaceHolder` | Handle to the drawing surface. |
| `mUri` | `Uri` | Source of the video. |
| `mVideoWidth/Height`| `int` | Dimensions reported by `MediaPlayer`. |
| `mCanPause/Seek` | `boolean` | Capabilities queried from media metadata. |

## API Reference
- `setVideoPath(String)` / `setVideoURI(Uri)`: Sets the source.
- `start()` / `pause()` / `stopPlayback()`: Basic transport controls.
- `suspend()` / `resume()`: Used for lifecycle management (releasing/re-opening resources).
- `setMediaController(MediaController)`: Attaches an on-screen controller.
- `setAudioAttributes(AudioAttributes)`: Configures audio routing/usage.
- `addSubtitleSource(InputStream, MediaFormat)`: Adds external side-car subtitle files.

## Java-to-C++ Translation Guide

### Surface Management
- **SurfaceView**: Translates to a native component that interacts with `SurfaceComposerClient` (to create a sub-layer) and `ANativeWindow`.
- **SurfaceHolder.Callback**: Needs to be mapped to native surface lifecycle events.

### Media Engine
- **MediaPlayer**: In native code, this maps to the `MediaPlayer` service (Stagefright/NuPlayer). Use `libmedia` or `libmediaplayer2`.
- **MediaController**: This is a complex Java widget. In a native-only framework, this would need to be reimplemented using native UI primitives.

### Subtitles
- **Renderers**: `WebVTT`, `CEA-708`, etc., have complex logic in Java. For a C++ port, these would likely be delegated to a native library like `libstagefright_soft_vpx` or a dedicated subtitle engine.

### Threading
- **prepareAsync**: The async nature of media preparation is critical. The C++ implementation must use an event loop (e.g., `android::ALooper`) to handle `MediaPlayer` callbacks without blocking the UI thread.

## Implementation Risks
- **Resource Management**: Failing to call `release()` on `mMediaPlayer` can lead to native memory leaks and hardware decoder exhaustion.
- **Surface Lifecycle**: Accessing the `Surface` after `surfaceDestroyed` or before `surfaceCreated` will cause a crash or native exception.
- **Aspect Ratio Math**: Integer division in `onMeasure` can lead to rounding errors. Use floating point or careful rounding logic to avoid jitter.
- **Audio Focus**: Audio focus logic varies by Android version. The C++ implementation should adhere strictly to the latest `AudioManager` native protocols.
