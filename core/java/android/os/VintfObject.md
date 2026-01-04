# VintfObject - Reverse Engineering Documentation

## Executive Summary
`VintfObject` provides Java access to the Device Manifest and Compatibility Matrix (VINTF). It checks if the device's HALs and Kernel meet the framework's requirements (and vice versa) for Treble compliance.

## Architecture Overview
-   **Role**: Treble Compliance Checker.
-   **Native**: JNI wrapper around `libvintf`.

## API Reference
-   `report()`: Returns all VINTF data.
-   `verifyBuildAtBoot()`: Checks compatibility.
-   `getHalNamesAndVersions()`: Lists supported HALs.
-   `getSepolicyVersion()`: Returns supported SELinux policy version.

## Java-to-C++ Translation Guide
-   **Equivalent**: `vintf::VintfObject` (C++ library).
-   **JNI**: `android_os_VintfObject.cpp`.
-   **Usage**: In C++, include `<vintf/VintfObject.h>`.

## Implementation Risks
-   **Boot Time**: Used during boot to verify OTA compatibility. Failures here can stop the boot process.
