# ContextHubInfo - Reverse Engineering Documentation

## Executive Summary
`ContextHubInfo` describes the properties of a Context Hub (a dedicated processing unit for sensor/context data). It contains hardware details like the vendor, toolchain, peak MIPS, power draw, and supported versions.

## Architecture Overview
- **Pattern**: Data Transfer Object (DTO) / Value Object.
- **Inheritance**: Implements `android.os.Parcelable`.
- **Sources**: Can be constructed from `android.hardware.contexthub.V1_0.ContextHub` (HIDL) or `android.hardware.contexthub.ContextHubInfo` (AIDL).

## Detailed Functionality
- **Identification**: `mId`, `mName`, `mVendor`.
- **Capabilities**: `mPeakMips`, `mMaxPacketLengthBytes`, `mSupportsReliableMessages`.
- **Power**: `mStoppedPowerDrawMw`, `mSleepPowerDrawMw`, `mPeakPowerDrawMw`.
- **Versions**: CHRE API versions, platform version, toolchain version.
- **Sub-components**: Lists supported sensors and memory regions (though arrays are initialized to empty in constructors shown).

## Data Model
| Field | Type | Description |
|---|---|---|
| `mId` | `int` | Unique Hub ID. |
| `mName` | `String` | Hub Name. |
| `mVendor` | `String` | Vendor Name. |
| `mChrePlatformId` | `long` | CHRE Platform ID. |
| `mMaxPacketLengthBytes` | `int` | Max message size. |
| ... | ... | See logic above. |

## Java-to-C++ Translation Guide
### Data Structure
```cpp
struct ContextHubInfo {
    int32_t id;
    std::string name;
    std::string vendor;
    std::string toolchain;
    int32_t platformVersion;
    int32_t toolchainVersion;
    float peakMips;
    float stoppedPowerDrawMw;
    float sleepPowerDrawMw;
    float peakPowerDrawMw;
    int32_t maxPacketLengthBytes;
    bool supportsReliableMessages;
    uint8_t chreApiMajorVersion;
    uint8_t chreApiMinorVersion;
    uint16_t chrePatchVersion;
    int64_t chrePlatformId;
    std::vector<int32_t> supportedSensors;
    std::vector<MemoryRegion> memoryRegions;
};
```
### Serialization
- Standard Parcel read/write.

## Questions for C++ Team
- `mSupportedSensors` and `mMemoryRegions` seem to be empty in the visible constructors. Are they populated elsewhere or deprecated?
