#ifndef AIDL_GENERATED_ANDROID_APP_BN_PROCESS_OBSERVER_H_
#define AIDL_GENERATED_ANDROID_APP_BN_PROCESS_OBSERVER_H_

#include <binder/IInterface.h>
#include <android/app/IProcessObserver.h>

namespace android {

namespace app {

class BnProcessObserver : public ::android::BnInterface<IProcessObserver> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnProcessObserver

}  // namespace app

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_APP_BN_PROCESS_OBSERVER_H_
