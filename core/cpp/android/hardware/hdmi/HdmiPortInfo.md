# HdmiPortInfo - Reverse Engineering Documentation

## Executive Summary
`HdmiPortInfo` encapsulates capabilities and configuration of an HDMI port.

## Architecture Overview
- **Type**: Immutable Data Class / Parcelable.
- **System API**: `@SystemApi`.

## Detailed Functionality
- **Fields**:
    - `mId`: Port ID.
    - `mType`: `PORT_INPUT` (0) or `PORT_OUTPUT` (1).
    - `mAddress`: Physical address.
    - `mCecSupported`: CEC support flag.
    - `mArcSupported`: ARC support flag.
    - `mEarcSupported`: eARC support flag.
    - `mMhlSupported`: MHL support flag.
- **Builder**: Inner class `Builder` for construction.

## Java-to-C++ Translation Guide
- **Class**: C++ class `HdmiPortInfo`.
- **Parcelable**: Implement `android::os::Parcelable`.
- **Constants**: Map `PORT_INPUT`, `PORT_OUTPUT`.

