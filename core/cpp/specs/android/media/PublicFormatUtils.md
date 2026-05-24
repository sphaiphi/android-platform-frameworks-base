# PublicFormatUtils - Reverse Engineering Documentation

## Executive Summary
`PublicFormatUtils` is a package-private utility for converting between public API image formats (Java `ImageFormat`/`PixelFormat`) and internal HAL (Hardware Abstraction Layer) formats/dataspaces.

## Detailed Functionality
- **`getHalFormat(int)`**: Converts public format to HAL format (native call).
- **`getHalDataspace(int)`**: Converts public format to HAL dataspace (native call).
- **`getPublicFormat(int, int)`**: Converts HAL format + dataspace back to a public format.

## Java-to-C++ Translation Guide
- **JNI Wrapper**: This class is purely a JNI wrapper around native format conversion logic (likely in `libandroid_runtime` or `libmedia`). The C++ implementation would directly call the underlying platform utility functions.

## Source Reference
Defined in `PublicFormatUtils.java`.
