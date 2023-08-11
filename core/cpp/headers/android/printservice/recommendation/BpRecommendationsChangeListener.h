#ifndef AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_BP_RECOMMENDATIONS_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_BP_RECOMMENDATIONS_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <android/printservice/recommendation/IRecommendationsChangeListener.h>

namespace android {

namespace printservice {

namespace recommendation {

class BpRecommendationsChangeListener : public ::android::BpInterface<IRecommendationsChangeListener> {
public:
  explicit BpRecommendationsChangeListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRecommendationsChangeListener() = default;
  ::android::binder::Status onRecommendationsChanged() override;
};  // class BpRecommendationsChangeListener

}  // namespace recommendation

}  // namespace printservice

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_BP_RECOMMENDATIONS_CHANGE_LISTENER_H_
