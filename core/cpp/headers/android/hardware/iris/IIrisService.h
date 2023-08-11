#ifndef AIDL_GENERATED_ANDROID_HARDWARE_IRIS_I_IRIS_SERVICE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_IRIS_I_IRIS_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace hardware {

namespace iris {

class IIrisService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(IrisService)
};  // class IIrisService

class IIrisServiceDefault : public IIrisService {
public:
  ::android::IBinder* onAsBinder() override;
  
};

}  // namespace iris

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_IRIS_I_IRIS_SERVICE_H_
