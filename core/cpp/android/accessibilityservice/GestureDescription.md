
# GestureDescription - Reverse Engineering Documentation

## Executive Summary
`GestureDescription` is an immutable class used to describe a programmatic touch gesture that an `AccessibilityService` can dispatch to the screen. A gesture consists of one or more "strokes," where each stroke is a path traced over time by a simulated finger. This allows services to perform complex touch interactions like multi-finger swipes or taps.

## Architecture Overview
*   **Immutable Design**: Once a `GestureDescription` is created using its `Builder`, it cannot be changed. This makes it safe to pass around and use across threads without locking.
*   **Composition**: A `GestureDescription` is composed of one or more `StrokeDescription` objects. Each `StrokeDescription` defines a single continuous touch path.
*   **Builder Pattern**: `GestureDescription` objects are constructed using a `GestureDescription.Builder`, which allows for the sequential addition of strokes and setting the target display ID.
*   **Path-based Strokes**: Strokes are defined by a `android.graphics.Path` object, a start time, and a duration. This provides a powerful and flexible way to describe arbitrary touch movements, not just straight lines.
*   **Internal Generation**: The class contains internal logic (`MotionEventGenerator`) to convert the high-level description of paths and timings into a low-level sequence of `GestureStep` objects, which in turn can be converted into `MotionEvent`s by the system.

## Detailed Functionality

### `GestureDescription.Builder`
*   **Purpose**: The public-facing factory for creating `GestureDescription` objects.
*   **`addStroke(StrokeDescription)`**: Adds a new stroke to the gesture. It enforces system limits, throwing an `IllegalStateException` if the number of strokes exceeds `MAX_STROKE_COUNT` (20) or if the total gesture duration exceeds `MAX_GESTURE_DURATION_MS` (60 seconds).
*   **`setDisplayId(int)`**: Specifies which display the gesture should be dispatched to. Defaults to the primary display.
*   **`build()`**: Validates the configuration (e.g., must have at least one stroke) and returns the immutable `GestureDescription` object.

### `StrokeDescription`
This nested class defines a single "finger" touch.
*   **Constructor**: Takes a `Path`, a `startTime` (relative to the gesture's start), and a `duration`. It performs several validations:
    *   Duration must be positive.
    *   Start time must not be negative.
    *   Path must not be empty or have negative bounds.
    *   Path must have exactly one contour.
*   **Path Traversal**: It uses a `PathMeasure` object to calculate the position of the touch at any given time within the stroke's duration. For a zero-length path (a tap), it caches the single location.
*   **Continued Strokes**: A key feature is the ability to create "continued" strokes. A stroke can be created with `willContinue = true`. This tells the system not to lift the "finger" at the end of the gesture. A subsequent gesture can then provide a new `StrokeDescription` that continues the previous one, identified by its ID. This is how multi-part gestures (like drag-and-drop) can be constructed across multiple `dispatchGesture` calls. The `continueStroke()` method provides a convenient way to create a continuing stroke.

### `MotionEventGenerator` (Internal)
*   **Purpose**: This internal static class is responsible for converting the declarative `GestureDescription` into a series of discrete time slices (`GestureStep`). This is the core of the gesture dispatch process.
*   **Algorithm**:
    1.  It identifies all "key points" in time (start and end times of all strokes).
    2.  It iterates through time, starting from the earliest key point.
    3.  At each time slice (either a key point or a fixed `sampleTimeMs` interval), it calculates the `(x, y)` position of every active stroke using `getPointsForTime()`.
    4.  It bundles these points into a `GestureStep` object.
    5.  This list of `GestureStep`s is what gets sent via IPC to the system server, which then turns them into `MotionEvent`s.

## Data Model

### `GestureDescription`
*   `mStrokes`: A `List<StrokeDescription>` holding all the strokes of the gesture.
*   `mDisplayId`: The `int` ID of the target display.

### `StrokeDescription`
*   `mPath`: The `android.graphics.Path` defining the stroke's movement.
*   `mStartTime`, `mEndTime`: The `long` start and end times in milliseconds.
*   `mPathMeasure`: A `PathMeasure` instance used to calculate points along the path.
*   `mId`: A unique integer ID for the stroke, used for continuations.
*   `mContinued`: A `boolean` flag indicating if this stroke will be continued.
*   `mContinuedStrokeId`: The `int` ID of the stroke that this one continues.

## Java-to-C++ Translation Guide
*   **`GestureDescription` / `StrokeDescription`**: These would be translated into C++ classes or structs. The builder pattern should be replicated in C++ for safe and easy construction.
*   **`Path`**: C++ needs a path object equivalent. A library like Skia (which Android's `Path` is based on) provides `SkPath`, which would be a natural fit. If Skia is not available, a custom path class representing a series of segments (lines, curves) would be needed.
*   **`PathMeasure`**: Skia also provides `SkPathMeasure`, which has the same functionality. If not using Skia, this logic (calculating a point along a path at a given distance) would need to be implemented manually, which can be complex for bézier curves.
*   **Immutability**: The C++ `GestureDescription` should be made immutable by making its members `const` and providing only getter methods after construction.
*   **`MotionEventGenerator`**: The logic for time-slicing the gesture into steps needs to be ported. This is a pure algorithm and can be translated directly, assuming the C++ `PathMeasure` equivalent works similarly. The `GestureStep` and `TouchPoint` classes are `Parcelable` and would need C++ `Parcelable` equivalents for IPC.

## Implementation Risks
*   **Path Mathematics**: Correctly implementing the logic to find a point along a complex path (especially a curved one) at a specific time/distance is mathematically intensive. Relying on a robust graphics library like Skia is highly recommended to avoid this risk.
*   **IPC Format**: The `GestureStep` and `TouchPoint` classes are sent over IPC. The C++ `Parcelable` implementation must exactly match the wire format of the Java version.
*   **Floating Point Precision**: The path-following logic involves floating-point calculations. Care must be taken to handle potential precision and round-off errors, especially when comparing times or positions.

## Questions for C++ Team
*   Will a graphics library like Skia be available in the C++ environment to provide `Path` and `PathMeasure` functionality? If not, what is the plan for implementing path traversal?
*   How will the `GestureStep` and `TouchPoint` `Parcelable`s be defined in C++ to ensure compatibility with the Android system service?
