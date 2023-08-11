#ifndef AIDL_GENERATED_ANDROID_VIEW_I_GRAPHICS_STATS_CALLBACK_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_GRAPHICS_STATS_CALLBACK_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IGraphicsStatsCallback : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GraphicsStatsCallback)
  virtual ::android::binder::Status onRotateGraphicsStatsBuffer() = 0;
};  // class IGraphicsStatsCallback

class IGraphicsStatsCallbackDefault : public IGraphicsStatsCallback {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onRotateGraphicsStatsBuffer() override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_GRAPHICS_STATS_CALLBACK_H_
