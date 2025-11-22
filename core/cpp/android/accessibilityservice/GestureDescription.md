# GestureDescription - Reverse Engineering Documentation

## Executive Summary
The `GestureDescription` class encapsulates the description of a multi-stroke gesture for use by Android's accessibility services. It allows for the programmatic creation and dispatching of complex touch gestures, defined by one or more strokes. Each stroke is a path on the screen with a specific start time and duration. The class is designed to be immutable once created via its `Builder`.

This document provides a comprehensive analysis of the `GestureDescription.java` source code to guide its reimplementation in C++.

## Architecture Overview
The component is composed of a final outer class, `GestureDescription`, and several static inner classes that work together to define and process a gesture.

*   **`GestureDescription`**: The main immutable container for a gesture. It holds a list of `StrokeDescription` objects and the target display ID. It also contains logic to calculate touch points at specific times.
*   **`GestureDescription.Builder`**: A builder class used for the step-by-step construction of an immutable `GestureDescription` object. It validates constraints, such as the maximum number of strokes and total gesture duration.
*   **`StrokeDescription`**: Represents a single, continuous stroke in a gesture. It's defined by a `Path`, a `startTime`, and a `duration`. It can also be marked as "continued," allowing for the creation of gestures that span multiple `GestureDescription` dispatches.
*   **`TouchPoint`**: A simple data structure (and `Parcelable`) representing the position and state of a single touch point at a specific moment in time. It's marked as `@hide`, suggesting it is for internal framework use.
*   **`GestureStep`**: A `Parcelable` container for all `TouchPoint` objects at a specific timestamp, representing a single snapshot of the gesture. It's also marked as `@hide`.
*   **`MotionEventGenerator`**: A utility class with a static method to convert a `GestureDescription` into a `List<GestureStep>`, effectively discretizing the continuous gesture paths into a series of time-stamped touch events. This is also an internal utility (`@hide`).

The design relies on the Builder pattern to create an immutable `GestureDescription` object, ensuring that once a gesture is defined, it cannot be accidentally modified.

## Detailed Functionality

### `GestureDescription`
**Purpose**: To hold the complete, immutable description of a touch gesture.

**Algorithm**:
1.  A `GestureDescription` is instantiated via its `Builder`.
2.  It stores a `List<StrokeDescription>` and the target `displayId`.
3.  It provides methods to query the number of strokes (`getStrokeCount()`), retrieve a specific stroke (`getStroke(index)`), and get the display ID (`getDisplayId()`).
4.  The internal method `getPointsForTime(long time, TouchPoint[] touchPoints)` calculates the (x, y) coordinates for every active stroke at a given time. It iterates through all its strokes and, for each one that is active at that `time`, calculates the position along the stroke's `Path`.
5.  The `getNextKeyPointAtLeast(long offset)` method finds the earliest start or end time of any stroke that occurs at or after the given `offset`. This is used by `MotionEventGenerator` to identify significant time points in the gesture.

**Java-Specific Notes**:
*   The class is `final`, preventing inheritance. C++ can achieve this with the `final` keyword on the class definition.
*   It uses `java.util.ArrayList` to store strokes. A `std::vector` is a suitable C++ equivalent.
*   The use of `android.graphics.Path` is central. A C++ equivalent for 2D path representation is needed.

**C++ Implementation Guidance**:
*   The main C++ class should be immutable. Store the list of strokes in a `const std::vector<StrokeDescription>`.
*   Constructor should be private, and instantiation should be managed by a friend `Builder` class.
*   Implement methods for querying gesture properties.

### `GestureDescription.Builder`
**Purpose**: To construct a `GestureDescription` object safely, enforcing constraints.

**Algorithm**:
1.  The `Builder` maintains a mutable list of `StrokeDescription` objects.
2.  The `addStroke(StrokeDescription)` method adds a stroke to the list.
3.  After adding a stroke, it performs two validations:
    *   Checks if the number of strokes exceeds `MAX_STROKE_COUNT` (20).
    *   Checks if the total gesture duration (from time 0 to the end time of the latest stroke) exceeds `MAX_GESTURE_DURATION_MS` (60,000 ms).
    *   If validation fails, it throws an `IllegalStateException`.
4.  The `setDisplayId(int)` method allows specifying the target display.
5.  The `build()` method creates and returns a new `GestureDescription` instance, passing its list of strokes. It also checks that at least one stroke has been added.

**C++ Implementation Guidance**:
*   Implement `Builder` as a nested class within `GestureDescription`.
*   Use a `std::vector` to accumulate strokes.
*   The `build()` method should return a `GestureDescription` by value or a `std::unique_ptr<GestureDescription>`.

### `StrokeDescription`
**Purpose**: To define a single continuous touch movement.

**Algorithm**:
1.  A `StrokeDescription` is defined by a `Path`, a `startTime`, and a `duration`.
2.  The constructor validates its arguments: duration must be positive, start time must not be negative, path must not be empty, and path bounds must be within the screen (non-negative coordinates).
3.  It uses `android.graphics.PathMeasure` to calculate the position on the path for a given time. The position is determined by linear interpolation over the path's length based on the elapsed time.
4.  A special case exists for zero-length paths, which are treated as taps (a touch down and up at the same point).
5.  A stroke can be "continued" by calling `continueStroke(...)`, which creates a new `StrokeDescription` linked to the original. This is used for gestures that are dispatched in sequence but should be treated as a single continuous touch by the system.

**Java-Specific Notes**:
*   **`android.graphics.Path`**: A core dependency for defining the stroke's geometry.
*   **`android.graphics.PathMeasure`**: Used to translate a time value into a distance along the path, from which a coordinate can be found. C++ will need a library or custom implementation for this.
*   A `static int sIdCounter` is used to assign a unique ID to each stroke.

**C++ Implementation Guidance**:
*   This will be a key class in the C++ implementation.
*   A 2D path library will be required. Simple paths could be implemented with a vector of points, but for curves (Béziers), a more robust library is needed (e.g., Skia, Cairo, or a custom solution).
*   The `PathMeasure` functionality must be replicated. This involves calculating the total length of the path and being able to find the point at a certain distance along it.
*   A static integer member can be used for the ID counter, but care must be taken to ensure thread safety if strokes can be created from multiple threads (`std::atomic<int>`).

## Data Model
*   **`GestureDescription`**
    *   `mStrokes`: `List<StrokeDescription>` - The sequence of strokes.
    *   `mDisplayId`: `int` - The ID of the target display.
*   **`StrokeDescription`**
    *   `mPath`: `Path` - The geometry of the stroke.
    *   `mStartTime`: `long` - Start time in milliseconds from the gesture's beginning.
    *   `mEndTime`: `long` - Calculated as `mStartTime + duration`.
    *   `mDuration`: `long` (implicit) - The duration of the stroke.
    *   `mId`: `int` - A unique identifier for the stroke.
    *   `mContinued`: `boolean` - Flag indicating if this stroke will be continued in a subsequent gesture.
    *   `mContinuedStrokeId`: `int` - If this stroke continues another, this holds the ID of the previous stroke.

## API Reference
### `GestureDescription`
*   `static int getMaxStrokeCount()`: Returns the maximum number of strokes allowed in a gesture (20).
*   `static long getMaxGestureDuration()`: Returns the maximum duration of a gesture in milliseconds (60000).
*   `int getStrokeCount()`: Returns the number of strokes in the gesture.
*   `StrokeDescription getStroke(int index)`: Retrieves the stroke at the specified index.
    *   **Preconditions**: `index` must be between 0 and `getStrokeCount() - 1`.
*   `int getDisplayId()`: Returns the target display ID for the gesture.

### `GestureDescription.Builder`
*   `Builder()`: Constructs a new builder.
*   `Builder addStroke(StrokeDescription stroke)`: Adds a stroke.
    *   **Postconditions**: The stroke is added to the gesture.
    *   **Throws**: `IllegalStateException` if max stroke count or max duration is exceeded.
*   `Builder setDisplayId(int displayId)`: Sets the target display ID.
*   `GestureDescription build()`: Constructs the final `GestureDescription`.
    *   **Throws**: `IllegalStateException` if no strokes were added.

### `StrokeDescription`
*   `StrokeDescription(Path path, long startTime, long duration)`: Constructor for a non-continued stroke.
*   `StrokeDescription(Path path, long startTime, long duration, boolean willContinue)`: Constructor that specifies if the stroke can be continued.
    *   **Preconditions**: `duration > 0`, `startTime >= 0`, `path` is not empty, and path bounds are non-negative.
*   `Path getPath()`: Returns a copy of the stroke's path.
*   `long getStartTime()`: Returns the stroke's start time in ms.
*   `long getDuration()`: Returns the stroke's duration in ms.
*   `boolean willContinue()`: Returns true if the stroke is marked to be continued.
*   `StrokeDescription continueStroke(Path path, long startTime, long duration, boolean willContinue)`: Creates a new stroke that continues the current one.
    *   **Throws**: `IllegalStateException` if the current stroke is not marked with `willContinue()`.

## Java-to-C++ Translation Guide
*   **Memory Management**:
    *   Java's `GestureDescription` and `StrokeDescription` are heap-allocated objects managed by the GC.
    *   In C++, use smart pointers (`std::unique_ptr`, `std::shared_ptr`) or value semantics where appropriate. Since `GestureDescription` is immutable, returning it by value from the `Builder` is a good option. The `StrokeDescription` objects it contains could also be stored by value within a `std::vector`.
*   **Classes and Structs**:
    *   `final class GestureDescription` -> `class GestureDescription final`.
    *   Static inner classes like `Builder` and `StrokeDescription` can be implemented as nested classes in C++.
    *   `TouchPoint` and `GestureStep` can be simple C++ `structs`.
*   **Collections**:
    *   `java.util.ArrayList<StrokeDescription>` -> `std::vector<StrokeDescription>`.
*   **Exception Handling**:
    *   Java's `IllegalStateException` and `IllegalArgumentException` (both `RuntimeException`s) should be translated to C++ exceptions like `std::logic_error` or custom exception types derived from `std::exception`.
*   **Android-Specific Dependencies**:
    *   **`android.graphics.Path`**: This is the most significant dependency. The C++ implementation will need a 2D graphics path library. The choice depends on the project's existing dependencies. If none, a lightweight path library or a custom implementation for lines and simple curves might be sufficient.
    *   **`android.graphics.PathMeasure`**: This functionality needs to be replicated. It involves:
        1.  Calculating the length of a path segment.
        2.  Finding the `(x, y)` coordinate and tangent at a specific distance along the path.
    *   **`android.os.Parcelable`**: The `TouchPoint` and `GestureStep` classes implement `Parcelable` for inter-process communication (IPC). If the C++ version also needs IPC, a C++ serialization mechanism (like Protocol Buffers, FlatBuffers, or a custom one) must be used.
*   **Primitive Types**:
    *   Java's `long` is a 64-bit signed integer. Use `int64_t` in C++ for time values to ensure consistency.
    *   Java's `int` is 32-bit. Use `int32_t`.
    *   Java's `float` corresponds to C++ `float`.

## Test Cases & Validation
1.  **Builder Validation**:
    *   Attempt to build a gesture with no strokes. Expect an exception.
    *   Attempt to add more than `MAX_STROKE_COUNT` strokes. Expect an exception on the addition of the 21st stroke.
    *   Attempt to add a stroke that makes the total duration exceed `MAX_GESTURE_DURATION_MS`. Expect an exception.
2.  **Stroke Validation**:
    *   Create a stroke with a negative start time. Expect an exception.
    *   Create a stroke with zero or negative duration. Expect an exception.
    *   Create a stroke with an empty path. Expect an exception.
    *   Create a stroke with path coordinates in the negative space. Expect an exception.
3.  **Functionality**:
    *   **Single Tap**: Create a gesture with a single, zero-length path. Verify that `getPointsForTime` returns the correct point for the duration of the "tap".
    *   **Line Stroke**: Create a gesture with a single line. Call `getPointsForTime` at `startTime`, `startTime + duration / 2`, and `endTime`. Verify the points are the start, middle, and end of the line, respectively.
    *   **Multi-Stroke Gesture**: Create a two-finger swipe with two parallel line strokes starting at the same time. Verify `getPointsForTime` returns two `TouchPoint`s with correct coordinates.
    *   **Continued Stroke**: Create a stroke with `willContinue = true`. Then create a second gesture with a stroke that continues the first, using `continueStroke`. The system-level test would be to ensure the pointer stays down between these two dispatched gestures.

## Implementation Risks
*   **Path/PathMeasure Equivalence**: The biggest risk is inaccurately reimplementing `android.graphics.Path` and `PathMeasure`. Any deviation in how path lengths or intermediate points are calculated will lead to gestures that do not match the behavior of the original Android implementation. Thorough testing against the reference Java implementation is crucial.
*   **Floating Point Precision**: Path calculations involve floating-point math. Differences in precision between the Java and C++ floating-point units or math libraries could cause slight deviations.
*   **Concurrency**: The Java implementation is not explicitly thread-safe (e.g., the static `sIdCounter` in `StrokeDescription` and `sCurrentTouchPoints` in `MotionEventGenerator`). If the C++ implementation needs to be thread-safe, these static variables will need proper synchronization (e.g., using `std::atomic` or mutexes).

## Questions for C++ Team
1.  What 2D graphics or path manipulation library is available in the target C++ environment?
2.  Is there a requirement for IPC/serialization for the `GestureStep` and `TouchPoint` equivalents? If so, what serialization framework should be used?
3.  What are the thread-safety requirements for creating gestures in the C++ environment? Can multiple threads create gestures concurrently?