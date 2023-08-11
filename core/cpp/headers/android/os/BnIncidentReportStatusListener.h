#ifndef AIDL_GENERATED_ANDROID_OS_BN_INCIDENT_REPORT_STATUS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BN_INCIDENT_REPORT_STATUS_LISTENER_H_

#include <binder/IInterface.h>
#include <android/os/IIncidentReportStatusListener.h>

namespace android {

namespace os {

class BnIncidentReportStatusListener : public ::android::BnInterface<IIncidentReportStatusListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnIncidentReportStatusListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BN_INCIDENT_REPORT_STATUS_LISTENER_H_
