/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IInputMonitorHost.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/IInputMonitorHost.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnInputMonitorHost.h>
#include <aidl/android/view/BpInputMonitorHost.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_IInputMonitorHost_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnInputMonitorHost> _aidl_impl = std::static_pointer_cast<BnInputMonitorHost>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*pilferPointers*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->pilferPointers();
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*dispose*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->dispose();
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_IInputMonitorHost_clazz = ::ndk::ICInterface::defineClass(IInputMonitorHost::descriptor, _aidl_android_view_IInputMonitorHost_onTransact, nullptr, 0);

BpInputMonitorHost::BpInputMonitorHost(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpInputMonitorHost::~BpInputMonitorHost() {}

::ndk::ScopedAStatus BpInputMonitorHost::pilferPointers() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*pilferPointers*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IInputMonitorHost::getDefaultImpl()) {
    _aidl_status = IInputMonitorHost::getDefaultImpl()->pilferPointers();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpInputMonitorHost::dispose() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 1 /*dispose*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IInputMonitorHost::getDefaultImpl()) {
    _aidl_status = IInputMonitorHost::getDefaultImpl()->dispose();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnInputMonitorHost
BnInputMonitorHost::BnInputMonitorHost() {}
BnInputMonitorHost::~BnInputMonitorHost() {}
::ndk::SpAIBinder BnInputMonitorHost::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_IInputMonitorHost_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IInputMonitorHost
const char* IInputMonitorHost::descriptor = "android.view.IInputMonitorHost";
IInputMonitorHost::IInputMonitorHost() {}
IInputMonitorHost::~IInputMonitorHost() {}


std::shared_ptr<IInputMonitorHost> IInputMonitorHost::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_IInputMonitorHost_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpInputMonitorHost>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IInputMonitorHost>(interface);
  }
  return ::ndk::SharedRefBase::make<BpInputMonitorHost>(binder);
}

binder_status_t IInputMonitorHost::writeToParcel(AParcel* parcel, const std::shared_ptr<IInputMonitorHost>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IInputMonitorHost::readFromParcel(const AParcel* parcel, std::shared_ptr<IInputMonitorHost>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IInputMonitorHost::fromBinder(binder);
  return STATUS_OK;
}
bool IInputMonitorHost::setDefaultImpl(const std::shared_ptr<IInputMonitorHost>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IInputMonitorHost::default_impl);
  if (impl) {
    IInputMonitorHost::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IInputMonitorHost>& IInputMonitorHost::getDefaultImpl() {
  return IInputMonitorHost::default_impl;
}
std::shared_ptr<IInputMonitorHost> IInputMonitorHost::default_impl = nullptr;
::ndk::ScopedAStatus IInputMonitorHostDefault::pilferPointers() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IInputMonitorHostDefault::dispose() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IInputMonitorHostDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IInputMonitorHostDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
