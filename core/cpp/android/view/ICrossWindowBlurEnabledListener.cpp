/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/ICrossWindowBlurEnabledListener.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/ICrossWindowBlurEnabledListener.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnCrossWindowBlurEnabledListener.h>
#include <aidl/android/view/BpCrossWindowBlurEnabledListener.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_ICrossWindowBlurEnabledListener_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnCrossWindowBlurEnabledListener> _aidl_impl = std::static_pointer_cast<BnCrossWindowBlurEnabledListener>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*onCrossWindowBlurEnabledChanged*/): {
      bool in_enabled;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_enabled);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onCrossWindowBlurEnabledChanged(in_enabled);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_ICrossWindowBlurEnabledListener_clazz = ::ndk::ICInterface::defineClass(ICrossWindowBlurEnabledListener::descriptor, _aidl_android_view_ICrossWindowBlurEnabledListener_onTransact, nullptr, 0);

BpCrossWindowBlurEnabledListener::BpCrossWindowBlurEnabledListener(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpCrossWindowBlurEnabledListener::~BpCrossWindowBlurEnabledListener() {}

::ndk::ScopedAStatus BpCrossWindowBlurEnabledListener::onCrossWindowBlurEnabledChanged(bool in_enabled) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_enabled);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*onCrossWindowBlurEnabledChanged*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && ICrossWindowBlurEnabledListener::getDefaultImpl()) {
    _aidl_status = ICrossWindowBlurEnabledListener::getDefaultImpl()->onCrossWindowBlurEnabledChanged(in_enabled);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnCrossWindowBlurEnabledListener
BnCrossWindowBlurEnabledListener::BnCrossWindowBlurEnabledListener() {}
BnCrossWindowBlurEnabledListener::~BnCrossWindowBlurEnabledListener() {}
::ndk::SpAIBinder BnCrossWindowBlurEnabledListener::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_ICrossWindowBlurEnabledListener_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for ICrossWindowBlurEnabledListener
const char* ICrossWindowBlurEnabledListener::descriptor = "android.view.ICrossWindowBlurEnabledListener";
ICrossWindowBlurEnabledListener::ICrossWindowBlurEnabledListener() {}
ICrossWindowBlurEnabledListener::~ICrossWindowBlurEnabledListener() {}


std::shared_ptr<ICrossWindowBlurEnabledListener> ICrossWindowBlurEnabledListener::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_ICrossWindowBlurEnabledListener_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpCrossWindowBlurEnabledListener>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<ICrossWindowBlurEnabledListener>(interface);
  }
  return ::ndk::SharedRefBase::make<BpCrossWindowBlurEnabledListener>(binder);
}

binder_status_t ICrossWindowBlurEnabledListener::writeToParcel(AParcel* parcel, const std::shared_ptr<ICrossWindowBlurEnabledListener>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t ICrossWindowBlurEnabledListener::readFromParcel(const AParcel* parcel, std::shared_ptr<ICrossWindowBlurEnabledListener>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = ICrossWindowBlurEnabledListener::fromBinder(binder);
  return STATUS_OK;
}
bool ICrossWindowBlurEnabledListener::setDefaultImpl(const std::shared_ptr<ICrossWindowBlurEnabledListener>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!ICrossWindowBlurEnabledListener::default_impl);
  if (impl) {
    ICrossWindowBlurEnabledListener::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<ICrossWindowBlurEnabledListener>& ICrossWindowBlurEnabledListener::getDefaultImpl() {
  return ICrossWindowBlurEnabledListener::default_impl;
}
std::shared_ptr<ICrossWindowBlurEnabledListener> ICrossWindowBlurEnabledListener::default_impl = nullptr;
::ndk::ScopedAStatus ICrossWindowBlurEnabledListenerDefault::onCrossWindowBlurEnabledChanged(bool /*in_enabled*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder ICrossWindowBlurEnabledListenerDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool ICrossWindowBlurEnabledListenerDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
