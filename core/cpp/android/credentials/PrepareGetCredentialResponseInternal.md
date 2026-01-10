# PrepareGetCredentialResponseInternal - Reverse Engineering Documentation

## Executive Summary
Internal response object for `prepareGetCredential`, passed across Binder from the system service. It is then wrapped into `PrepareGetCredentialResponse` for the client.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: IPC Data transfer.

## Detailed Functionality
- **`mHasQueryApiPermission` (boolean)**: True if caller can query details.
- **`mCredentialResultTypes` (`Set<String>`)**: Available credential types.
- **`mHasAuthenticationResults` (boolean)**: True if auth actions exist.
- **`mHasRemoteResults` (boolean)**: True if remote options exist.
- **`mPendingIntent` (`PendingIntent`)**: The UI intent.

## Java-to-C++ Translation Guide
- **Set**: `std::set<std::string>`.
- **PendingIntent**: `android::app::PendingIntent`.
- **Logic**: This is an internal transport struct.
