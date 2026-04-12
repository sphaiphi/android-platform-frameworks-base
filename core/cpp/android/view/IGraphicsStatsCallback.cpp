/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IGraphicsStatsCallback.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/IGraphicsStatsCallback.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnGraphicsStatsCallback.h>
#include <aidl/android/view/BpGraphicsStatsCallback.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_IGraphicsStatsCallback_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnGraphicsStatsCallback> _aidl_impl = std::static_pointer_cast<BnGraphicsStatsCallback>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*onRotateGraphicsStatsBuffer*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onRotateGraphicsStatsBuffer();
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_IGraphicsStatsCallback_clazz = ::ndk::ICInterface::defineClass(IGraphicsStatsCallback::descriptor, _aidl_android_view_IGraphicsStatsCallback_onTransact, nullptr, 0);

BpGraphicsStatsCallback::BpGraphicsStatsCallback(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpGraphicsStatsCallback::~BpGraphicsStatsCallback() {}

::ndk::ScopedAStatus BpGraphicsStatsCallback::onRotateGraphicsStatsBuffer() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*onRotateGraphicsStatsBuffer*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IGraphicsStatsCallback::getDefaultImpl()) {
    _aidl_status = IGraphicsStatsCallback::getDefaultImpl()->onRotateGraphicsStatsBuffer();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnGraphicsStatsCallback
BnGraphicsStatsCallback::BnGraphicsStatsCallback() {}
BnGraphicsStatsCallback::~BnGraphicsStatsCallback() {}
::ndk::SpAIBinder BnGraphicsStatsCallback::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_IGraphicsStatsCallback_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IGraphicsStatsCallback
const char* IGraphicsStatsCallback::descriptor = "android.view.IGraphicsStatsCallback";
IGraphicsStatsCallback::IGraphicsStatsCallback() {}
IGraphicsStatsCallback::~IGraphicsStatsCallback() {}


std::shared_ptr<IGraphicsStatsCallback> IGraphicsStatsCallback::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_IGraphicsStatsCallback_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpGraphicsStatsCallback>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IGraphicsStatsCallback>(interface);
  }
  return ::ndk::SharedRefBase::make<BpGraphicsStatsCallback>(binder);
}

binder_status_t IGraphicsStatsCallback::writeToParcel(AParcel* parcel, const std::shared_ptr<IGraphicsStatsCallback>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IGraphicsStatsCallback::readFromParcel(const AParcel* parcel, std::shared_ptr<IGraphicsStatsCallback>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IGraphicsStatsCallback::fromBinder(binder);
  return STATUS_OK;
}
bool IGraphicsStatsCallback::setDefaultImpl(const std::shared_ptr<IGraphicsStatsCallback>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IGraphicsStatsCallback::default_impl);
  if (impl) {
    IGraphicsStatsCallback::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IGraphicsStatsCallback>& IGraphicsStatsCallback::getDefaultImpl() {
  return IGraphicsStatsCallback::default_impl;
}
std::shared_ptr<IGraphicsStatsCallback> IGraphicsStatsCallback::default_impl = nullptr;
::ndk::ScopedAStatus IGraphicsStatsCallbackDefault::onRotateGraphicsStatsBuffer() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IGraphicsStatsCallbackDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IGraphicsStatsCallbackDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
