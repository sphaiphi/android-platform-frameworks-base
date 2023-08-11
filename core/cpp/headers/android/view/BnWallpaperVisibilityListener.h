#ifndef AIDL_GENERATED_ANDROID_VIEW_BN_WALLPAPER_VISIBILITY_LISTENER_H_
#define AIDL_GENERATED_ANDROID_VIEW_BN_WALLPAPER_VISIBILITY_LISTENER_H_

#include <binder/IInterface.h>
#include <android/view/IWallpaperVisibilityListener.h>

namespace android {

namespace view {

class BnWallpaperVisibilityListener : public ::android::BnInterface<IWallpaperVisibilityListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnWallpaperVisibilityListener

}  // namespace view

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_VIEW_BN_WALLPAPER_VISIBILITY_LISTENER_H_
