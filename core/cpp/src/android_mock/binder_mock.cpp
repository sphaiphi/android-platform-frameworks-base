#include <android/binder_parcel.h>
#include <android/binder_status.h>
#include <string>
#include <vector>

extern "C" {

binder_status_t AParcel_writeString(AParcel* /*parcel*/, const char* /*string*/, int32_t /*length*/) {
    return STATUS_OK;
}

binder_status_t AParcel_writeInt32(AParcel* /*parcel*/, int32_t /*value*/) {
    return STATUS_OK;
}

binder_status_t AParcel_writeInt64(AParcel* /*parcel*/, int64_t /*value*/) {
    return STATUS_OK;
}

binder_status_t AParcel_writeDouble(AParcel* /*parcel*/, double /*value*/) {
    return STATUS_OK;
}

binder_status_t AParcel_writeFloat(AParcel* /*parcel*/, float /*value*/) {
    return STATUS_OK;
}

binder_status_t AParcel_writeBool(AParcel* /*parcel*/, bool /*value*/) {
    return STATUS_OK;
}

binder_status_t AParcel_writeStatus(AParcel* /*parcel*/, binder_status_t /*status*/) {
    return STATUS_OK;
}

binder_status_t AParcel_readInt32(const AParcel* /*parcel*/, int32_t* value) {
    if (value) *value = 0;
    return STATUS_OK;
}

binder_status_t AParcel_readInt64(const AParcel* /*parcel*/, int64_t* value) {
    if (value) *value = 0;
    return STATUS_OK;
}

binder_status_t AParcel_readDouble(const AParcel* /*parcel*/, double* value) {
    if (value) *value = 0.0;
    return STATUS_OK;
}

binder_status_t AParcel_readFloat(const AParcel* /*parcel*/, float* value) {
    if (value) *value = 0.0f;
    return STATUS_OK;
}

binder_status_t AParcel_readBool(const AParcel* /*parcel*/, bool* value) {
    if (value) *value = false;
    return STATUS_OK;
}

binder_status_t AParcel_readStatus(const AParcel* /*parcel*/, binder_status_t* status) {
    if (status) *status = STATUS_OK;
    return STATUS_OK;
}

binder_status_t AParcel_readString(const AParcel* /*parcel*/, void* stringData, AParcel_stringAllocator allocator) {
    char* buffer = nullptr;
    if (allocator(stringData, 0, &buffer)) {
        return STATUS_OK;
    }
    return STATUS_BAD_VALUE;
}

}
