# WearableSensingService - Reverse Engineering Documentation

## Executive Summary
`WearableSensingService` is an abstract base class for processing sensor and audio data originating from wearable devices (like smartwatches). It is a security-hardened service that runs in a highly restricted isolated process, ensuring that sensitive wearable data (e.g., microphone streams) is processed privately before being elevated to other system components.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **Sandboxing**: MUST be declared with `android:isolatedProcess="true"`. It has no direct access to the network, filesystem, or other system services unless explicitly proxied.
*   **IPC**: Implements `IWearableSensingService.Stub`. It receives connections and data streams from the `WearableSensingManagerService`.
*   **Connectivity**: Data from the wearable is delivered via `ParcelFileDescriptor` objects, which represent secure encrypted channels or raw data streams.
*   **Permission**: Requires `android.permission.BIND_WEARABLE_SENSING_SERVICE`.

## Detailed Functionality

### Connection Management
*   **`onSecureConnectionProvided(ParcelFileDescriptor, PersistableBundle, Consumer)`**: Handles a secure, encrypted link to the remote wearable.
*   **`onDataStreamProvided(ParcelFileDescriptor, Consumer)`**: Receives a raw data stream from the wearable.

### Detection & Recognition
*   **`onStartDetection(AmbientContextEventRequest, ...)`**: Starts detecting specific ambient events (e.g., sound detection) using wearable sensors.
*   **`onStartHotwordRecognition(Consumer<HotwordAudioStream>, Consumer<Integer>)`**: Handles hotword detection where the initial trigger or audio stream comes from the wearable microphone.

### Data & State
*   **`onDataProvided(PersistableBundle, SharedMemory, Consumer)`**: Receives models (e.g., neural network weights) or configuration data from the non-isolated assistant process.
*   **Proxied File Access**: Since the process is isolated, `openFileInput` is overridden to request files from the parent application process via an internal `IWearableSensingCallback`.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.wearable.WearableSensingService"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IWearableSensingService.Stub`.
*   **C++**: `BnWearableSensingService`.

### Security Constraints
*   **Isolated Process**: C++ implementation must be compatible with Android's isolated process restrictions (SELinux, restricted syscalls).
*   **Data Marshalling**: Large data blobs (models) are passed via `SharedMemory`, which should be mapped in C++ using `mmap`.
*   **File Descriptors**: Connection channels are raw FDs. In C++, these are typically used with `read()`/`write()` or integrated into a `poll()`/`epoll()` loop for asynchronous processing.

## Implementation Risks
*   **Resource Management**: Isolated processes have strict memory limits. Processing high-frequency sensor data or audio requires optimized native code.
*   **Privacy**: This service is a primary gatekeeper for wearable privacy. It must ensure that no raw data is leaked outside the isolated process until a high-confidence event (like a hotword) is detected.
*   **Latency**: Real-time sensing requires low-latency processing to remain effective for features like gesture recognition or immediate voice response.
