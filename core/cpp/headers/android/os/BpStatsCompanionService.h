#ifndef AIDL_GENERATED_ANDROID_OS_BP_STATS_COMPANION_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BP_STATS_COMPANION_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/os/IStatsCompanionService.h>

namespace android {

namespace os {

class BpStatsCompanionService : public ::android::BpInterface<IStatsCompanionService> {
public:
  explicit BpStatsCompanionService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpStatsCompanionService() = default;
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
};  // class BpStatsCompanionService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_STATS_COMPANION_SERVICE_H_
