# DynamicSystemClient - Reverse Engineering Documentation

## Executive Summary
`DynamicSystemClient` provides a high-level API for applications to interact with the Dynamic System installation service. It facilitates the installation of "Dynamic Systems" (certified system images run safely alongside the main OS), allowing users to test system updates without overwriting their primary data. It manages the connection to the underlying `DynamicSystemInstallationService`, handles status updates via `Messenger` IPC, and initiates the installation process via `VerificationActivity`.

## Architecture Overview
-   **Pattern:** Service Client / Messenger Callback
-   **Components:**
    -   `DynamicSystemClient`: Main entry point.
    -   `DynSystemServiceConnection`: Handles the `ServiceConnection` lifecycle (bind/unbind).
    -   `IncomingHandler`: Receives status messages from the service.
    -   `OnStatusChangedListener`: Client-provided callback interface.
-   **IPC Mechanism:** `Messenger` based. The client sends messages to register/unregister, and the service sends status messages back to the client's `IncomingHandler`.
-   **Interaction Flow:**
    1.  Client creates `DynamicSystemClient`.
    2.  Client calls `bind()` to connect to `com.android.dynsystem.DynamicSystemInstallationService`.
    3.  Client calls `start()` which launches `VerificationActivity` (to confirm credentials).
    4.  Service communicates progress back via `MSG_POST_STATUS`.

## Detailed Functionality

### Initialization & Binding
-   **Constructor**: Initializes the `Messenger` with an `IncomingHandler` pointing to the main looper.
-   **`bind()`**:
    -   Binds to `com.android.dynsystem.DynamicSystemInstallationService`.
    -   Sets `mBound = true`.
    -   On connection (`onServiceConnected`), sends `MSG_REGISTER_LISTENER` to the service, including the client's `Messenger` (`replyTo`) so the service can send messages back.
-   **`unbind()`**:
    -   Sends `MSG_UNREGISTER_LISTENER` if connected.
    -   Unbinds the context from the service.

### Installation Management
-   **`start(Uri systemUrl, long systemSize, long userdataSize)`**:
    -   Constructs an `Intent` for `com.android.dynsystem.VerificationActivity`.
    -   Action: `android.os.image.action.START_INSTALL`.
    -   Extras: System URL, System Size, Userdata Size.
    -   Starts the Activity. This delegates the actual "start" logic to the trusted activity which verifies the user (Keyguard) before instructing the service to proceed.

### Status Updates
-   **`handleMessage(Message msg)`**:
    -   Handles `MSG_POST_STATUS` (3).
    -   Extracts:
        -   `status` (arg1)
        -   `cause` (arg2)
        -   `progress` (Bundle key `KEY_INSTALLED_SIZE`)
        -   `detail` (Bundle key `KEY_EXCEPTION_DETAIL` -> `ParcelableException`)
    -   Invokes the registered `OnStatusChangedListener`.
-   **Listener Dispatch**: Supports executing the callback on a user-provided `Executor` or directly on the handler thread (Main Looper).

## Data Model

### Constants & Enums
**InstallationStatus** (`int`)
| Value | Name | Description |
| :--- | :--- | :--- |
| 0 | `STATUS_UNKNOWN` | Bound but status unknown |
| 1 | `STATUS_NOT_STARTED` | Idle |
| 2 | `STATUS_IN_PROGRESS` | Downloading/Installing |
| 3 | `STATUS_READY` | Install done, awaiting reboot |
| 4 | `STATUS_IN_USE` | Currently running the Dynamic System |

**StatusChangedCause** (`int`)
| Value | Name | Description |
| :--- | :--- | :--- |
| 0 | `CAUSE_NOT_SPECIFIED` | No specific cause |
| 1 | `CAUSE_INSTALL_COMPLETED` | Success |
| 2 | `CAUSE_INSTALL_CANCELLED` | User cancelled |
| 3 | `CAUSE_ERROR_IO` | IO Failure |
| 4 | `CAUSE_ERROR_INVALID_URL` | Bad URL |
| 5 | `CAUSE_ERROR_IPC` | RemoteException |
| 6 | `CAUSE_ERROR_EXCEPTION` | Generic Exception |

### IPC Protocol
-   **Messages to Service**:
    -   `MSG_REGISTER_LISTENER` (1)
    -   `MSG_UNREGISTER_LISTENER` (2)
-   **Messages from Service**:
    -   `MSG_POST_STATUS` (3)
-   **Bundle Keys**:
    -   `KEY_INSTALLED_SIZE`: `long` (bytes installed)
    -   `KEY_EXCEPTION_DETAIL`: `ParcelableException`

## API Reference
-   `setOnStatusChangedListener(Executor, OnStatusChangedListener)`: Register callback.
-   `bind()`: Connect to service.
-   `unbind()`: Disconnect.
-   `start(Uri, long, long)`: Begin installation flow via Verification Activity.

## Java-to-C++ Translation Guide

### Architecture
-   This class is a client wrapper. In C++, if acting as the client, you would interact with the Binder interface directly or implement a similar Messenger/Handler pattern if the service strictly requires it.
-   However, since `DynamicSystemInstallationService` seems to be the logic holder, this class is mostly UI/App facing.
-   **Core C++ Equivalent**: Likely interacts with `android::os::image::IDynamicSystemService` (Binder) or the underlying `gsi` service. This Java class uses `Messenger`, which wraps a `Handler` Binder.

### IPC Translation
-   **Messenger**: In C++, `Messenger` effectively wraps an `IMessenger` Binder interface. Sending a `Message` involves constructing a Parcel.
-   **Handlers**: C++ `Looper` and `Handler` (libutils/libstagefright foundation) or `ALooper` (NDK) are equivalents.

### Key Mapping
| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `Context.bindService` | `IServiceManager::getService` (if system service) | This binds to an app service, so standard Binder connection logic applies. |
| `Messenger` | `android::os::IMessenger` | AIDL definition for Messenger exists in framework. |
| `Bundle` | `android::os::Bundle` | C++ implementation exists in `frameworks/native/libs/binder`. |
| `ParcelableException` | Error propagation | Serialize exception details into Parcel. |

## Questions for C++ Team
1.  Does the C++ layer need to initiate these installations, or is this strictly an Android App (Settings/SystemUI) feature?
2.  The `Messenger` protocol seems designed for high-level UI feedback. Does the C++ layer need to intercept this, or just interact with `IDynamicSystemService` directly?
