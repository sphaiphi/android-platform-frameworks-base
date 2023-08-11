#ifndef AIDL_GENERATED_ANDROID_VIEW_BP_WALLPAPER_VISIBILITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BP_WALLPAPER_VISIBILITY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/view/IWallpaperVisibilityListener.h>

namespace android {

namespace view {

class BpWallpaperVisibilityListener : public ::android::BpInterface<IWallpaperVisibilityListener> {
public:
  explicit BpWallpaperVisibilityListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpWallpaperVisibilityListener() = default;
  ::android::binder::Status onWallpaperVisibilityChanged(bool visible, int32_t displayId) override;
};  // class BpWallpaperVisibilityListener

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BP_WALLPAPER_VISIBILITY_LISTENER_H_
