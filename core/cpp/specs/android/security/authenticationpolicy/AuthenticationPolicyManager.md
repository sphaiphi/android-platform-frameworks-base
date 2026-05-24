# AuthenticationPolicyManager - Reverse Engineering Documentation

## Executive Summary
`AuthenticationPolicyManager` manages authentication-related policies, specifically the "Secure Lock" feature (remotely locking the device to restrict access).

## Architecture Overview
*   **Package**: `android.security.authenticationpolicy`
*   **Type**: Class (System Service, System API)
*   **Service Name**: `Context.AUTHENTICATION_POLICY_SERVICE`
*   **Dependencies**: `IAuthenticationPolicyService`.

## Detailed Functionality

### 1. Enable Secure Lock
*   **Method**: `enableSecureLockDevice(EnableSecureLockDeviceParams params)`
*   **Purpose**: Remotely locks the device, restricting notifications and requiring strong auth.
*   **Permissions**: `MANAGE_SECURE_LOCK_DEVICE`.

### 2. Disable Secure Lock
*   **Method**: `disableSecureLockDevice(DisableSecureLockDeviceParams params)`
*   **Purpose**: Unlocks/restores the device state.

## Data Model
*   **Status Codes**: `SUCCESS`, `ERROR_UNKNOWN`, `ERROR_UNSUPPORTED`, `ERROR_NO_BIOMETRICS`, etc.

## Java-to-C++ Translation Guide
*   Wrapper around `IAuthenticationPolicyService`.
*   Straightforward mapping of AIDL calls.
