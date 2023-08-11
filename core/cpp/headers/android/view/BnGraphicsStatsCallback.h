#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_GRAPHICS_STATS_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_GRAPHICS_STATS_CALLBACK_H_

#include <binder/IInterface.h>
#include <android/view/IGraphicsStatsCallback.h>

namespace android {

namespace view {

class BnGraphicsStatsCallback : public ::android::BnInterface<IGraphicsStatsCallback> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnGraphicsStatsCallback

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_GRAPHICS_STATS_CALLBACK_H_
