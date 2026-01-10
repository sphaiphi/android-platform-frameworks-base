# VirtualDisplay - Reverse Engineering Documentation

## Executive Summary
`VirtualDisplay` represents a virtual display created by an application. It holds a reference to the `Display` object and the backing `Surface`. It allows resizing, surface replacement, and releasing.

## Architecture Overview
- **Type**: Handle / Client Object.
- **Creation**: Returned by `DisplayManager.createVirtualDisplay`.
- **Token**: Holds `IVirtualDisplayCallback` token, which identifies this display in the system server.

## Detailed Functionality
- `setSurface(Surface)`: Changes the output destination.
- `resize(w, h, dpi)`: Changes resolution.
- `release()`: Destroys the display.
- `setRotation(int)`: Sets the projection rotation.

## Java-to-C++ Translation Guide
- **Handle**: This object is essentially a handle to a remote resource.
- **Token**: The `IVirtualDisplayCallback` (Binder) is the key identity. The C++ implementation must retain this binder to keep the display alive and to perform operations.
- **Surface**: Manipulating the surface involves generic `Surface` / `IGraphicBufferProducer` APIs.
