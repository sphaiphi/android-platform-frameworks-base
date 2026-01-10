# TouchCalibration - Reverse Engineering Documentation

## Executive Summary
`TouchCalibration` holds a 2x3 affine transformation matrix used to calibrate touch coordinates (scaling, rotation, translation).

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Identity**: Provides a default identity constant.

## Detailed Functionality
- Stores 6 floats: `XScale`, `XYMix`, `XOffset`, `YXMix`, `YScale`, `YOffset`.
- `X_out = X_in * XScale + Y_in * XYMix + XOffset`
- `Y_out = X_in * YXMix + Y_in * YScale + YOffset`

## API Reference
- `float[] getAffineTransform()`: Returns array of 6 floats.
- `equals/hashCode`.

## Java-to-C++ Translation Guide
- Struct of 6 floats.
- Mathematical operations usually handled by `InputReader` (native).

## Implementation Risks
- Precision issues (float vs double), though standard touch precision usually fits in float.
