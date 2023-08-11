#ifndef AIDL_GENERATED_ANDROID_OS_BP_INCIDENT_REPORT_STATUS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_BP_INCIDENT_REPORT_STATUS_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IIncidentReportStatusListener.h>

namespace android {

namespace os {

class BpIncidentReportStatusListener : public ::android::BpInterface<IIncidentReportStatusListener> {
public:
  explicit BpIncidentReportStatusListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpIncidentReportStatusListener() = default;
  ::android::binder::Status onReportStarted() override;
  ::android::binder::Status onReportSectionStatus(int32_t section, int32_t status) override;
  ::android::binder::Status onReportFinished() override;
  ::android::binder::Status onReportFailed() override;
};  // class BpIncidentReportStatusListener

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_INCIDENT_REPORT_STATUS_LISTENER_H_
