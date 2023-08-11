#ifndef AIDL_GENERATED_ANDROID_OS_I_INCIDENT_REPORT_STATUS_LISTENER_H_
#define AIDL_GENERATED_ANDROID_OS_I_INCIDENT_REPORT_STATUS_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IIncidentReportStatusListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(IncidentReportStatusListener)
  enum  : int32_t {
    STATUS_STARTING = 1,
    STATUS_FINISHED = 2,
  };
  virtual ::android::binder::Status onReportStarted() = 0;
  virtual ::android::binder::Status onReportSectionStatus(int32_t section, int32_t status) = 0;
  virtual ::android::binder::Status onReportFinished() = 0;
  virtual ::android::binder::Status onReportFailed() = 0;
};  // class IIncidentReportStatusListener

class IIncidentReportStatusListenerDefault : public IIncidentReportStatusListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onReportStarted() override;
  ::android::binder::Status onReportSectionStatus(int32_t section, int32_t status) override;
  ::android::binder::Status onReportFinished() override;
  ::android::binder::Status onReportFailed() override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_INCIDENT_REPORT_STATUS_LISTENER_H_
