#pragma once
#include <cstdint>
#include <android/binder_status.h>

typedef struct AParcel AParcel;

#ifdef __cplusplus
extern "C" {
#endif

binder_status_t AParcel_writeString(AParcel* parcel, const char* string, int32_t length);
binder_status_t AParcel_writeInt32(AParcel* parcel, int32_t value);
binder_status_t AParcel_writeInt64(AParcel* parcel, int64_t value);
binder_status_t AParcel_writeDouble(AParcel* parcel, double value);
binder_status_t AParcel_writeFloat(AParcel* parcel, float value);
binder_status_t AParcel_writeBool(AParcel* parcel, bool value);
binder_status_t AParcel_writeStatus(AParcel* parcel, binder_status_t status);

binder_status_t AParcel_readInt32(const AParcel* parcel, int32_t* value);
binder_status_t AParcel_readInt64(const AParcel* parcel, int64_t* value);
binder_status_t AParcel_readDouble(const AParcel* parcel, double* value);
binder_status_t AParcel_readFloat(const AParcel* parcel, float* value);
binder_status_t AParcel_readBool(const AParcel* parcel, bool* value);
binder_status_t AParcel_readStatus(const AParcel* parcel, binder_status_t* status);

typedef bool (*AParcel_stringAllocator)(void* stringData, int32_t length, char** outString);
binder_status_t AParcel_readString(const AParcel* parcel, void* stringData, AParcel_stringAllocator allocator);

#ifdef __cplusplus
}
#endif
