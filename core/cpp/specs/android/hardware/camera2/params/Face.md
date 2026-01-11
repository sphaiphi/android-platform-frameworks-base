# Face - Reverse Engineering Documentation

## Executive Summary
`Face` describes a face detected by the camera's face detection unit. It includes information about the face's location (bounds), detection confidence (score), and optional features like landmarks (eyes and mouth) and a unique tracking ID.

## Architecture Overview
- **Storage**: Immutable data class.
- **Coordinate System**: All coordinates (bounds and landmarks) are relative to the sensor's active pixel array (`SENSOR_INFO_ACTIVE_ARRAY_SIZE`).
- **Discovery**: Detected faces are returned in `CaptureResult` under the `STATISTICS_FACES` key.

## Detailed Functionality

### Face Detection Levels
**Purpose**: To support different levels of detection complexity.
**Levels**:
- **SIMPLE**: Provides `bounds` and `score`. `id` is `-1`, and landmarks are `null`.
- **FULL**: Provides `bounds`, `score`, `id`, and landmarks (`leftEye`, `rightEye`, `mouth`).

### Landmark Constraints
**Java-Specific Notes**: The constructor enforces that if any landmark (eye or mouth) is non-null, all three must be non-null. This ensures consistency in the facial structure data.

## Data Model

### Members
- `mBounds` (`Rect`): The bounding box of the face on the sensor.
- `mScore` (`int`): Confidence level from 1 to 100.
- `mId` (`int`): Unique tracking ID. Persistent as long as the face is in view.
- `mLeftEye`, `mRightEye`, `mMouth` (`Point`): Coordinates of facial features.

## API Reference

### Public Methods
- `Rect getBounds()`: Get face rectangle.
- `int getScore()`: Get confidence.
- `int getId()`: Get tracking ID or `ID_UNSUPPORTED`.
- `Point getLeftEyePosition()`: Optional landmark.
- `Point getRightEyePosition()`: Optional landmark.
- `Point getMouthPosition()`: Optional landmark.

### Constants
- `ID_UNSUPPORTED`: `-1`.
- `SCORE_MIN`: `1`.
- `SCORE_MAX`: `100`.

## Java-to-C++ Translation Guide

### Data Structure
- **Java**: Uses `android.graphics.Rect` and `android.graphics.Point`.
- **C++**: Use `struct Rect { int32_t left, top, right, bottom; }` and `struct Point { int32_t x, y; }`.

### Optionality
- **Java**: Uses `null` for missing landmarks.
- **C++**: Use `std::optional<Point>` for landmarks and `std::optional<int32_t>` for the ID to avoid magic numbers like `-1`.

## Test Cases & Validation
1. **Range Validation**: Ensure `score` is always between 1 and 100.
2. **Coordinate Mapping**: Verify that face coordinates map correctly to the preview UI after considering sensor orientation and crop regions.
3. **ID Persistence**: Verify that the same `id` is returned for a face across consecutive frames in a stable scene.
