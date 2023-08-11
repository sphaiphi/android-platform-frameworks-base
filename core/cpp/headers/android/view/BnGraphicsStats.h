#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_GRAPHICS_STATS_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_GRAPHICS_STATS_H_

#include <binder/IInterface.h>
#include <android/view/IGraphicsStats.h>

namespace android {

namespace view {

class BnGraphicsStats : public ::android::BnInterface<IGraphicsStats> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnGraphicsStats

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_GRAPHICS_STATS_H_
