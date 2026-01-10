# AppWidgetProviderInfo - Reverse Engineering Documentation

## Executive Summary
`AppWidgetProviderInfo` is a `Parcelable` metadata class that describes an installed AppWidget. It corresponds directly to the attributes defined in the `<appwidget-provider>` XML resource file in an APK.

## Data Model (Fields)

### Dimensions & Resizing
- `minWidth`, `minHeight`: Default size (dp -> px).
- `minResizeWidth`, `minResizeHeight`: Minimum resize limits.
- `maxResizeWidth`, `maxResizeHeight`: Maximum resize limits.
- `targetCellWidth`, `targetCellHeight`: Grid cell size (launcher specific).
- `resizeMode`: Bitmask (`RESIZE_HORIZONTAL`, `RESIZE_VERTICAL`, `RESIZE_NONE`).

### Identification & Launching
- `provider`: `ComponentName` of the BroadcastReceiver.
- `configure`: `ComponentName` of the configuration Activity.
- `label`: Display name.
- `icon`: Icon resource ID.

### Preview
- `previewImage`: Drawable resource ID (static image).
- `previewLayout`: Layout resource ID (XML layout for better fidelity).

### Configuration
- `updatePeriodMillis`: Update frequency.
- `initialLayout`: Default layout resource ID.
- `initialKeyguardLayout`: Default layout for lockscreen.
- `widgetCategory`: Bitmask (`HOME_SCREEN`, `KEYGUARD`, `SEARCHBOX`).
- `widgetFeatures`: Flags (`RECONFIGURABLE`, `HIDE_FROM_PICKER`).

### Internal
- `providerInfo`: `ActivityInfo` of the receiver.

## API Reference
- `loadLabel`, `loadIcon`, `loadPreviewImage`: Helper methods to load resources using the provider's `PackageManager`.
- `updateDimensions`: Converts the internal raw dimensions (potentially complex units) to pixels based on display metrics.

## Java-to-C++ Translation Guide
- **Struct Definition**: Direct mapping to a C++ struct or class.
- **Serialization**: Standard Parcelable implementation.
- **Resource Loading**: Methods like `loadIcon` rely on `PackageManager` and `Resources`, which may need C++ equivalents or callbacks to Java.

## Notes
- **Mutable Fields**: Some fields like `maxResizeWidth` are noted as `@SuppressLint("MutableBareField")`, implying they might be modified by the system or launcher after loading.
