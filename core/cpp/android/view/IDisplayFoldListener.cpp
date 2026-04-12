/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayFoldListener.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/IDisplayFoldListener.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnDisplayFoldListener.h>
#include <aidl/android/view/BpDisplayFoldListener.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_IDisplayFoldListener_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnDisplayFoldListener> _aidl_impl = std::static_pointer_cast<BnDisplayFoldListener>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*onDisplayFoldChanged*/): {
      int32_t in_displayId;
      bool in_folded;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_displayId);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_folded);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onDisplayFoldChanged(in_displayId, in_folded);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_IDisplayFoldListener_clazz = ::ndk::ICInterface::defineClass(IDisplayFoldListener::descriptor, _aidl_android_view_IDisplayFoldListener_onTransact, nullptr, 0);

BpDisplayFoldListener::BpDisplayFoldListener(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpDisplayFoldListener::~BpDisplayFoldListener() {}

::ndk::ScopedAStatus BpDisplayFoldListener::onDisplayFoldChanged(int32_t in_displayId, bool in_folded) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_displayId);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_folded);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*onDisplayFoldChanged*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayFoldListener::getDefaultImpl()) {
    _aidl_status = IDisplayFoldListener::getDefaultImpl()->onDisplayFoldChanged(in_displayId, in_folded);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnDisplayFoldListener
BnDisplayFoldListener::BnDisplayFoldListener() {}
BnDisplayFoldListener::~BnDisplayFoldListener() {}
::ndk::SpAIBinder BnDisplayFoldListener::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_IDisplayFoldListener_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IDisplayFoldListener
const char* IDisplayFoldListener::descriptor = "android.view.IDisplayFoldListener";
IDisplayFoldListener::IDisplayFoldListener() {}
IDisplayFoldListener::~IDisplayFoldListener() {}


std::shared_ptr<IDisplayFoldListener> IDisplayFoldListener::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_IDisplayFoldListener_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpDisplayFoldListener>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IDisplayFoldListener>(interface);
  }
  return ::ndk::SharedRefBase::make<BpDisplayFoldListener>(binder);
}

binder_status_t IDisplayFoldListener::writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayFoldListener>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IDisplayFoldListener::readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayFoldListener>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IDisplayFoldListener::fromBinder(binder);
  return STATUS_OK;
}
bool IDisplayFoldListener::setDefaultImpl(const std::shared_ptr<IDisplayFoldListener>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IDisplayFoldListener::default_impl);
  if (impl) {
    IDisplayFoldListener::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IDisplayFoldListener>& IDisplayFoldListener::getDefaultImpl() {
  return IDisplayFoldListener::default_impl;
}
std::shared_ptr<IDisplayFoldListener> IDisplayFoldListener::default_impl = nullptr;
::ndk::ScopedAStatus IDisplayFoldListenerDefault::onDisplayFoldChanged(int32_t /*in_displayId*/, bool /*in_folded*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IDisplayFoldListenerDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IDisplayFoldListenerDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
