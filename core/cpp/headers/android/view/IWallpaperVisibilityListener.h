#ifndef AIDL_GENERATED_ANDROID_VIEW_I_WALLPAPER_VISIBILITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_I_WALLPAPER_VISIBILITY_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace view {

class IWallpaperVisibilityListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(WallpaperVisibilityListener)
  virtual ::android::binder::Status onWallpaperVisibilityChanged(bool visible, int32_t displayId) = 0;
};  // class IWallpaperVisibilityListener

class IWallpaperVisibilityListenerDefault : public IWallpaperVisibilityListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onWallpaperVisibilityChanged(bool visible, int32_t displayId) override;

};

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_I_WALLPAPER_VISIBILITY_LISTENER_H_
