# GeofenceHardwareImpl - Reverse Engineering Documentation

## Executive Summary
`GeofenceHardwareImpl` is the core implementation class that manages the logic for hardware geofencing. It sits between the `GeofenceHardwareService` (Binder stub) and the specific hardware interfaces (`IGpsGeofenceHardware`, `IFusedGeofenceHardware`). It manages callback lifecycles, permissions, and thread handling.

## Architecture Overview
- **Pattern**: Implementation / Coordinator.
- **Role**: The "Brain" of the service side.
- **Singleton**: `getInstance(Context)`.
- **Threading**: Uses multiple Handlers (`mGeofenceHandler`, `mCallbacksHandler`, `mReaperHandler`) to manage callbacks and death recipients asynchronously.

## Detailed Functionality

### Hardware Abstraction
- Manages connections to `IGpsGeofenceHardware` and `IFusedGeofenceHardware`.
- Updates availability status based on these services.

### Callback Management
- **SparseArray `mGeofences`**: Maps Geofence ID -> Callback.
- **Reaper**: Implements `IBinder.DeathRecipient` to clean up geofences if the calling process dies.
- **Wrappers**: Uses `GeofenceHardwareCallbackWrapper` to handle Binder IPC.

### Operations
- `addCircularFence`: Validates, registers callback, calls hardware, and handles failure.
- `reportGeofenceTransition`: Called by HAL/Hardware to notify of events. Dispatches to registered callback.
- `acquireWakeLock`: Holds a partial wake lock during transition processing.

## Data Model
- `mGeofences`: `SparseArray<IGeofenceHardwareCallback>`.
- `mCallbacks`: `ArrayList<IGeofenceHardwareMonitorCallback>[]`.
- `mReapers`: `ArrayList<Reaper>`.

## Java-to-C++ Translation Guide
### Architecture Mapping
- **C++ Class**: `GeofenceHardwareImpl` (Service-side logic).
- **Concurrency**: Use `std::mutex` for map access. Use a `Looper` or `WorkQueue` for dispatching callbacks if preserving the Handler model.
- **Death Recipient**: Use `linkToDeath` on the Binder objects.

### Key Logic
- The "Reaper" logic is critical for system stability (preventing leaks when apps crash).
- WakeLock usage must be preserved to ensure the device doesn't sleep while processing a transition.

## Questions for C++ Team
- Is this implementation moving to C++ entirely? This looks like the system service implementation.
