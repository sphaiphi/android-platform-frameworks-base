#ifndef AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_I_RECOMMENDATIONS_CHANGE_LISTENER_H_
#define AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_I_RECOMMENDATIONS_CHANGE_LISTENER_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace printservice {

namespace recommendation {

class IRecommendationsChangeListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RecommendationsChangeListener)
  virtual ::android::binder::Status onRecommendationsChanged() = 0;
};  // class IRecommendationsChangeListener

class IRecommendationsChangeListenerDefault : public IRecommendationsChangeListener {
public:
  ::android::IBinder* onAsBinder() override;
  ::android::binder::Status onRecommendationsChanged() override;

};

}  // namespace recommendation

}  // namespace printservice

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_PRINTSERVICE_RECOMMENDATION_I_RECOMMENDATIONS_CHANGE_LISTENER_H_
