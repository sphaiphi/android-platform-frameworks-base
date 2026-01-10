# VirtualDisplayConfig - Reverse Engineering Documentation

## Executive Summary
`VirtualDisplayConfig` is a comprehensive Parcelable configuration object used to create a `VirtualDisplay`. It uses a Builder pattern to set numerous properties like size, flags, surface, and categories.

## Architecture Overview
- **Type**: Immutable Configuration Object.
- **Builder**: `VirtualDisplayConfig.Builder`.

## Data Model
- **Basic**: Name, Width, Height, Density.
- **Flags**: `int` (Public, Secure, etc.).
- **Surface**: `Surface` object (can be null).
- **Mirroring**: `displayIdToMirror`, `windowManagerMirroringEnabled`.
- **Properties**: `displayCategories` (Set<String>), `requestedRefreshRate`, `displayCutout`.
- **Brightness**: `defaultBrightness`, `dimBrightness`, `brightnessListener`.

## Java-to-C++ Translation Guide
- **Parcelable**: Large serialization payload. Must match Java write order exactly.
- **Surface**: Marshals a Surface (native `ANativeWindow` or `IGraphicBufferProducer`).
- **DisplayCutout**: Needs mapping to C++ equivalent of `DisplayCutout`.
- **Callback**: `IBrightnessListener` is a Binder interface.

## API Reference
- `Builder` setters for all fields.
- Validation logic in `Builder.build()` (e.g., dim brightness <= default brightness).
