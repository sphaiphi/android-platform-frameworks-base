/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IAppTransitionAnimationSpecsFuture.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/IAppTransitionAnimationSpecsFuture.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnAppTransitionAnimationSpecsFuture.h>
#include <aidl/android/view/BpAppTransitionAnimationSpecsFuture.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_IAppTransitionAnimationSpecsFuture_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnAppTransitionAnimationSpecsFuture> _aidl_impl = std::static_pointer_cast<BnAppTransitionAnimationSpecsFuture>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*get*/): {
      std::vector<::aidl::android::view::AppTransitionAnimationSpec> _aidl_return;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->get(&_aidl_return);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_out, _aidl_return);
      if (_aidl_ret_status != STATUS_OK) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_IAppTransitionAnimationSpecsFuture_clazz = ::ndk::ICInterface::defineClass(IAppTransitionAnimationSpecsFuture::descriptor, _aidl_android_view_IAppTransitionAnimationSpecsFuture_onTransact, nullptr, 0);

BpAppTransitionAnimationSpecsFuture::BpAppTransitionAnimationSpecsFuture(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpAppTransitionAnimationSpecsFuture::~BpAppTransitionAnimationSpecsFuture() {}

::ndk::ScopedAStatus BpAppTransitionAnimationSpecsFuture::get(std::vector<::aidl::android::view::AppTransitionAnimationSpec>* _aidl_return) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*get*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IAppTransitionAnimationSpecsFuture::getDefaultImpl()) {
    _aidl_status = IAppTransitionAnimationSpecsFuture::getDefaultImpl()->get(_aidl_return);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) goto _aidl_status_return;
  _aidl_ret_status = ::ndk::AParcel_readData(_aidl_out.get(), _aidl_return);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnAppTransitionAnimationSpecsFuture
BnAppTransitionAnimationSpecsFuture::BnAppTransitionAnimationSpecsFuture() {}
BnAppTransitionAnimationSpecsFuture::~BnAppTransitionAnimationSpecsFuture() {}
::ndk::SpAIBinder BnAppTransitionAnimationSpecsFuture::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_IAppTransitionAnimationSpecsFuture_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IAppTransitionAnimationSpecsFuture
const char* IAppTransitionAnimationSpecsFuture::descriptor = "android.view.IAppTransitionAnimationSpecsFuture";
IAppTransitionAnimationSpecsFuture::IAppTransitionAnimationSpecsFuture() {}
IAppTransitionAnimationSpecsFuture::~IAppTransitionAnimationSpecsFuture() {}


std::shared_ptr<IAppTransitionAnimationSpecsFuture> IAppTransitionAnimationSpecsFuture::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_IAppTransitionAnimationSpecsFuture_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpAppTransitionAnimationSpecsFuture>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IAppTransitionAnimationSpecsFuture>(interface);
  }
  return ::ndk::SharedRefBase::make<BpAppTransitionAnimationSpecsFuture>(binder);
}

binder_status_t IAppTransitionAnimationSpecsFuture::writeToParcel(AParcel* parcel, const std::shared_ptr<IAppTransitionAnimationSpecsFuture>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IAppTransitionAnimationSpecsFuture::readFromParcel(const AParcel* parcel, std::shared_ptr<IAppTransitionAnimationSpecsFuture>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IAppTransitionAnimationSpecsFuture::fromBinder(binder);
  return STATUS_OK;
}
bool IAppTransitionAnimationSpecsFuture::setDefaultImpl(const std::shared_ptr<IAppTransitionAnimationSpecsFuture>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IAppTransitionAnimationSpecsFuture::default_impl);
  if (impl) {
    IAppTransitionAnimationSpecsFuture::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IAppTransitionAnimationSpecsFuture>& IAppTransitionAnimationSpecsFuture::getDefaultImpl() {
  return IAppTransitionAnimationSpecsFuture::default_impl;
}
std::shared_ptr<IAppTransitionAnimationSpecsFuture> IAppTransitionAnimationSpecsFuture::default_impl = nullptr;
::ndk::ScopedAStatus IAppTransitionAnimationSpecsFutureDefault::get(std::vector<::aidl::android::view::AppTransitionAnimationSpec>* /*_aidl_return*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IAppTransitionAnimationSpecsFutureDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IAppTransitionAnimationSpecsFutureDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
