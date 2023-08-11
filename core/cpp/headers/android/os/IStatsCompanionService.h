#ifndef AIDL_GENERATED_ANDROID_OS_I_STATS_COMPANION_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_I_STATS_COMPANION_SERVICE_H_

#include <android/os/StatsDimensionsValue.h>
#include <android/os/StatsLogEventWrapper.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace os {

class IStatsCompanionService : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(StatsCompanionService)
  virtual ::android::binder::Status statsdReady() = 0;
  virtual ::android::binder::Status setAnomalyAlarm(int64_t timestampMs) = 0;
  virtual ::android::binder::Status cancelAnomalyAlarm() = 0;
  virtual ::android::binder::Status setPullingAlarm(int64_t nextPullTimeMs) = 0;
  virtual ::android::binder::Status cancelPullingAlarm() = 0;
  virtual ::android::binder::Status setAlarmForSubscriberTriggering(int64_t timestampMs) = 0;
  virtual ::android::binder::Status cancelAlarmForSubscriberTriggering() = 0;
  virtual ::android::binder::Status pullData(int32_t pullCode, ::std::vector<::android::os::StatsLogEventWrapper>* _aidl_return) = 0;
  virtual ::android::binder::Status sendDataBroadcast(const ::android::sp<::android::IBinder>& intentSender, int64_t lastReportTimeNs) = 0;
  virtual ::android::binder::Status sendActiveConfigsChangedBroadcast(const ::android::sp<::android::IBinder>& intentSender, const ::std::vector<int64_t>& configIds) = 0;
  virtual ::android::binder::Status sendSubscriberBroadcast(const ::android::sp<::android::IBinder>& intentSender, int64_t configUid, int64_t configId, int64_t subscriptionId, int64_t subscriptionRuleId, const ::std::vector<::android::String16>& cookies, const ::android::os::StatsDimensionsValue& dimensionsValue) = 0;
  virtual ::android::binder::Status triggerUidSnapshot() = 0;
};  // class IStatsCompanionService

class IStatsCompanionServiceDefault : public IStatsCompanionService {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status statsdReady() override;
  ::android::binder::Status setAnomalyAlarm(int64_t timestampMs) override;
  ::android::binder::Status cancelAnomalyAlarm() override;
  ::android::binder::Status setPullingAlarm(int64_t nextPullTimeMs) override;
  ::android::binder::Status cancelPullingAlarm() override;
  ::android::binder::Status setAlarmForSubscriberTriggering(int64_t timestampMs) override;
  ::android::binder::Status cancelAlarmForSubscriberTriggering() override;
  ::android::binder::Status pullData(int32_t pullCode, ::std::vector<::android::os::StatsLogEventWrapper>* _aidl_return) override;
  ::android::binder::Status sendDataBroadcast(const ::android::sp<::android::IBinder>& intentSender, int64_t lastReportTimeNs) override;
  ::android::binder::Status sendActiveConfigsChangedBroadcast(const ::android::sp<::android::IBinder>& intentSender, const ::std::vector<int64_t>& configIds) override;
  ::android::binder::Status sendSubscriberBroadcast(const ::android::sp<::android::IBinder>& intentSender, int64_t configUid, int64_t configId, int64_t subscriptionId, int64_t subscriptionRuleId, const ::std::vector<::android::String16>& cookies, const ::android::os::StatsDimensionsValue& dimensionsValue) override;
  ::android::binder::Status triggerUidSnapshot() override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_STATS_COMPANION_SERVICE_H_
