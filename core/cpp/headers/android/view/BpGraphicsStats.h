#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_GRAPHICS_STATS_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_GRAPHICS_STATS_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IGraphicsStats.h>

namespace android {

namespace view {

class BpGraphicsStats : public ::android::BpInterface<IGraphicsStats> {
public:
  explicit BpGraphicsStats(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpGraphicsStats() = default;
  ::android::binder::Status requestBufferForProcess(const ::android::String16& packageName, const ::android::sp<::android::view::IGraphicsStatsCallback>& callback, ::android::os::ParcelFileDescriptor* _aidl_return) override;
};  // class BpGraphicsStats

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_GRAPHICS_STATS_H_
