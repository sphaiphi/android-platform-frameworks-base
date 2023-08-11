#ifndef AIDL_GENERATED_ANDROID_HARDWARE_IRIS_BP_IRIS_SERVICE_H_
#define AIDL_GENERATED_ANDROID_HARDWARE_IRIS_BP_IRIS_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/hardware/iris/IIrisService.h>

namespace android {

namespace hardware {

namespace iris {

class BpIrisService : public ::android::BpInterface<IIrisService> {
public:
  explicit BpIrisService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpIrisService() = default;
};  // class BpIrisService

}  // namespace iris

}  // namespace hardware

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_HARDWARE_IRIS_BP_IRIS_SERVICE_H_
