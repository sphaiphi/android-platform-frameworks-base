# MotionPredictor - Reverse Engineering Documentation

## Executive Summary
`MotionPredictor` is a high-performance utility used to predict the future position of a touch or stylus pointer. By feeding past `MotionEvent`s into the predictor, it generates "synthetic" future events that can be used to reduce perceived latency in drawing applications or smooth out irregular sensor data.

## Architecture Overview
*   **Role**: Latency-reduction engine.
*   **JNI Centric**: Wraps a native C++ `MotionPredictor` object.
*   **Implementation**: Likely uses a Kalman filter or a similar predictive algorithm in native code.

## Detailed Functionality

### 1. Recording
*   **`record(MotionEvent)`**: Ingests historical data. It requires a consistent stream of events from a single input device to produce accurate results.

### 2. Prediction
*   **`predict(long timeNanos)`**: Generates a synthetic `MotionEvent` for the requested future timestamp. It includes historical samples to allow for smooth interpolation curves.

### 3. Capability Check
*   **`isPredictionAvailable()`**: Checks if the specific hardware/source combination supports prediction.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly wraps `android::MotionPredictor`.
*   **Memory Management**: Managed by `NativeAllocationRegistry`. Ensure the native destructor is called promptly.

## Implementation Risks
*   **Confidence**: The predictor may return `null` if the user's movement is too erratic (e.g., sudden changes in direction) where confidence in the prediction is low.
*   **Inconsistent Streams**: Passing events from multiple pointers or devices into a single predictor will lead to `IllegalArgumentException` or nonsensical results.
