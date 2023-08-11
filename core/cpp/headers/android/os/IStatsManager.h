#ifndef AIDL_GENERATED_ANDROID_OS_I_STATS_MANAGER_H_
#define AIDL_GENERATED_ANDROID_OS_I_STATS_MANAGER_H_

#include <android/os/IStatsPullerCallback.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace android {

namespace os {

class IStatsManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(StatsManager)
  enum  : int32_t {
    FLAG_REQUIRE_STAGING = 1,
    FLAG_ROLLBACK_ENABLED = 2,
    FLAG_REQUIRE_LOW_LATENCY_MONITOR = 4,
  };
  virtual ::android::binder::Status systemRunning() = 0;
  virtual ::android::binder::Status statsCompanionReady() = 0;
  virtual ::android::binder::Status informAnomalyAlarmFired() = 0;
  virtual ::android::binder::Status informPollAlarmFired() = 0;
  virtual ::android::binder::Status informAlarmForSubscriberTriggeringFired() = 0;
  virtual ::android::binder::Status informDeviceShutdown() = 0;
  virtual ::android::binder::Status informAllUidData(const ::android::os::ParcelFileDescriptor& fd) = 0;
  virtual ::android::binder::Status informOnePackage(const ::android::String16& app, int32_t uid, int64_t version, const ::android::String16& version_string, const ::android::String16& installer) = 0;
  virtual ::android::binder::Status informOnePackageRemoved(const ::android::String16& app, int32_t uid) = 0;
  virtual ::android::binder::Status getData(int64_t key, const ::android::String16& packageName, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status getMetadata(const ::android::String16& packageName, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status addConfiguration(int64_t configKey, const ::std::vector<uint8_t>& config, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status setDataFetchOperation(int64_t configKey, const ::android::sp<::android::IBinder>& intentSender, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status removeDataFetchOperation(int64_t configKey, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status setActiveConfigsChangedOperation(const ::android::sp<::android::IBinder>& intentSender, const ::android::String16& packageName, ::std::vector<int64_t>* _aidl_return) = 0;
  virtual ::android::binder::Status removeActiveConfigsChangedOperation(const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status removeConfiguration(int64_t configKey, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status setBroadcastSubscriber(int64_t configKey, int64_t subscriberId, const ::android::sp<::android::IBinder>& intentSender, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status unsetBroadcastSubscriber(int64_t configKey, int64_t subscriberId, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status sendAppBreadcrumbAtom(int32_t label, int32_t state) = 0;
  virtual ::android::binder::Status registerPullerCallback(int32_t atomTag, const ::android::sp<::android::os::IStatsPullerCallback>& pullerCallback, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status unregisterPullerCallback(int32_t atomTag, const ::android::String16& packageName) = 0;
  virtual ::android::binder::Status sendBinaryPushStateChangedAtom(const ::android::String16& trainName, int64_t trainVersionCode, int32_t options, int32_t state, const ::std::vector<int64_t>& experimentId) = 0;
  virtual ::android::binder::Status sendWatchdogRollbackOccurredAtom(int32_t rollbackType, const ::android::String16& packageName, int64_t packageVersionCode, int32_t rollbackReason, const ::android::String16& failingPackageName) = 0;
  virtual ::android::binder::Status getRegisteredExperimentIds(::std::vector<int64_t>* _aidl_return) = 0;
};  // class IStatsManager

class IStatsManagerDefault : public IStatsManager {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status systemRunning() override;
  ::android::binder::Status statsCompanionReady() override;
  ::android::binder::Status informAnomalyAlarmFired() override;
  ::android::binder::Status informPollAlarmFired() override;
  ::android::binder::Status informAlarmForSubscriberTriggeringFired() override;
  ::android::binder::Status informDeviceShutdown() override;
  ::android::binder::Status informAllUidData(const ::android::os::ParcelFileDescriptor& fd) override;
  ::android::binder::Status informOnePackage(const ::android::String16& app, int32_t uid, int64_t version, const ::android::String16& version_string, const ::android::String16& installer) override;
  ::android::binder::Status informOnePackageRemoved(const ::android::String16& app, int32_t uid) override;
  ::android::binder::Status getData(int64_t key, const ::android::String16& packageName, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status getMetadata(const ::android::String16& packageName, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status addConfiguration(int64_t configKey, const ::std::vector<uint8_t>& config, const ::android::String16& packageName) override;
  ::android::binder::Status setDataFetchOperation(int64_t configKey, const ::android::sp<::android::IBinder>& intentSender, const ::android::String16& packageName) override;
  ::android::binder::Status removeDataFetchOperation(int64_t configKey, const ::android::String16& packageName) override;
  ::android::binder::Status setActiveConfigsChangedOperation(const ::android::sp<::android::IBinder>& intentSender, const ::android::String16& packageName, ::std::vector<int64_t>* _aidl_return) override;
  ::android::binder::Status removeActiveConfigsChangedOperation(const ::android::String16& packageName) override;
  ::android::binder::Status removeConfiguration(int64_t configKey, const ::android::String16& packageName) override;
  ::android::binder::Status setBroadcastSubscriber(int64_t configKey, int64_t subscriberId, const ::android::sp<::android::IBinder>& intentSender, const ::android::String16& packageName) override;
  ::android::binder::Status unsetBroadcastSubscriber(int64_t configKey, int64_t subscriberId, const ::android::String16& packageName) override;
  ::android::binder::Status sendAppBreadcrumbAtom(int32_t label, int32_t state) override;
  ::android::binder::Status registerPullerCallback(int32_t atomTag, const ::android::sp<::android::os::IStatsPullerCallback>& pullerCallback, const ::android::String16& packageName) override;
  ::android::binder::Status unregisterPullerCallback(int32_t atomTag, const ::android::String16& packageName) override;
  ::android::binder::Status sendBinaryPushStateChangedAtom(const ::android::String16& trainName, int64_t trainVersionCode, int32_t options, int32_t state, const ::std::vector<int64_t>& experimentId) override;
  ::android::binder::Status sendWatchdogRollbackOccurredAtom(int32_t rollbackType, const ::android::String16& packageName, int64_t packageVersionCode, int32_t rollbackReason, const ::android::String16& failingPackageName) override;
  ::android::binder::Status getRegisteredExperimentIds(::std::vector<int64_t>* _aidl_return) override;

};

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_STATS_MANAGER_H_
