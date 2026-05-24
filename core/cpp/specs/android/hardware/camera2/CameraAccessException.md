# CameraAccessException.java - Reverse Engineering Documentation

## Executive Summary
`CameraAccessException` is a specialized exception thrown when a camera device cannot be queried, opened, or if a connection to an opened camera becomes invalid. It provides specific reason codes to help applications diagnose the cause of failure.

## Architecture Overview
- **Type**: Exception Class
- **Package**: `android.hardware.camera2`
- **Extends**: `android.util.AndroidException`.

## Detailed Functionality

### Access Error Codes
The exception defines several integer constants indicating the reason for the failure:
1.  **`CAMERA_DISABLED` (1)**: The camera is disabled due to a device policy (e.g., enterprise management).
2.  **`CAMERA_DISCONNECTED` (2)**: The camera has been physically disconnected or the service has shut down the connection due to a higher-priority request.
3.  **`CAMERA_ERROR` (3)**: The camera device is in a fatal error state.
4.  **`CAMERA_IN_USE` (4)**: The camera is already opened by another client.
5.  **`MAX_CAMERAS_IN_USE` (5)**: System-wide limit reached.
6.  **`CAMERA_DEPRECATED_HAL` (1000)**: Internal code for old HAL versions.

### API Reference
- `getReason()`: Returns one of the `CAMERA_*` constants.

## Java-to-C++ Translation Guide

### Enum Mapping
Translate the constants into a C++ `enum class`.

```cpp
namespace android::hardware::camera2 {

enum class CameraAccessError : int32_t {
    DISABLED = 1,
    DISCONNECTED = 2,
    DEVICE_ERROR = 3,
    IN_USE = 4,
    MAX_IN_USE = 5,
    DEPRECATED_HAL = 1000
};

}
```

### Exception Implementation
In C++, use a class inheriting from `std::exception` or a custom base like `android::status_t` returning specific error codes.

```cpp
class CameraAccessException : public std::exception {
public:
    explicit CameraAccessException(CameraAccessError reason, std::string message = "")
        : mReason(reason), mMessage(std::move(message)) {}
    
    CameraAccessError getReason() const { return mReason; }
    const char* what() const noexcept override { return mMessage.c_str(); }

private:
    CameraAccessError mReason;
    std::string mMessage;
};
```
