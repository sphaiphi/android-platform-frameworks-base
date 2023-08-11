#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_GRAPHICS_STATS_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_GRAPHICS_STATS_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IGraphicsStatsCallback.h>

namespace android {

namespace view {

class BpGraphicsStatsCallback : public ::android::BpInterface<IGraphicsStatsCallback> {
public:
  explicit BpGraphicsStatsCallback(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpGraphicsStatsCallback() = default;
  ::android::binder::Status onRotateGraphicsStatsBuffer() override;
};  // class BpGraphicsStatsCallback

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_GRAPHICS_STATS_CALLBACK_H_
