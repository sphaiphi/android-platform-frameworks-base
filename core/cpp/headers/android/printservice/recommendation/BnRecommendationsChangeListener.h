#ifndef AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_BN_RECOMMENDATIONS_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_BN_RECOMMENDATIONS_CHANGE_LISTENER_H_

#include <binder/IInterface.h>
#include <android/printservice/recommendation/IRecommendationsChangeListener.h>

namespace android {

namespace printservice {

namespace recommendation {

class BnRecommendationsChangeListener : public ::android::BnInterface<IRecommendationsChangeListener> {
public:
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnRecommendationsChangeListener

}  // namespace recommendation

}  // namespace printservice

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_BN_RECOMMENDATIONS_CHANGE_LISTENER_H_
