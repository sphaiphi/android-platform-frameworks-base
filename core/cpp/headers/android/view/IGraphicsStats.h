#ifndef AIDL_GENERATED_ANDROID_VIEW_I_GRAPHICS_STATS_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_GRAPHICS_STATS_H_

#include <android/view/IGraphicsStatsCallback.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IGraphicsStats : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GraphicsStats)
  virtual ::android::binder::Status requestBufferForProcess(const ::android::String16& packageName, const ::android::sp<::android::view::IGraphicsStatsCallback>& callback, ::android::os::ParcelFileDescriptor* _aidl_return) = 0;
};  // class IGraphicsStats

class IGraphicsStatsDefault : public IGraphicsStats {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status requestBufferForProcess(const ::android::String16& packageName, const ::android::sp<::android::view::IGraphicsStatsCallback>& callback, ::android::os::ParcelFileDescriptor* _aidl_return) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_GRAPHICS_STATS_H_
