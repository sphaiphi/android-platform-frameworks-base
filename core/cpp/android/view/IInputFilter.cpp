/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ --include=/home/roto/git/android-platform-frameworks-base/graphics/java /home/roto/git/android-platform-frameworks-base/core/java/android/view/IInputFilter.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/IInputFilter.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnInputFilter.h>
#include <aidl/android/view/BnInputFilterHost.h>
#include <aidl/android/view/BpInputFilter.h>
#include <aidl/android/view/BpInputFilterHost.h>
#include <aidl/android/view/IInputFilterHost.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_IInputFilter_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnInputFilter> _aidl_impl = std::static_pointer_cast<BnInputFilter>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*install*/): {
      std::shared_ptr<::aidl::android::view::IInputFilterHost> in_host;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_host);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->install(in_host);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*uninstall*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->uninstall();
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 2 /*filterInputEvent*/): {
      ::aidl::android::view::InputEvent in_event;
      int32_t in_policyFlags;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_event);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_policyFlags);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->filterInputEvent(in_event, in_policyFlags);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_IInputFilter_clazz = ::ndk::ICInterface::defineClass(IInputFilter::descriptor, _aidl_android_view_IInputFilter_onTransact, nullptr, 0);

BpInputFilter::BpInputFilter(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpInputFilter::~BpInputFilter() {}

::ndk::ScopedAStatus BpInputFilter::install(const std::shared_ptr<::aidl::android::view::IInputFilterHost>& in_host) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_host);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*install*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IInputFilter::getDefaultImpl()) {
    _aidl_status = IInputFilter::getDefaultImpl()->install(in_host);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpInputFilter::uninstall() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 1 /*uninstall*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IInputFilter::getDefaultImpl()) {
    _aidl_status = IInputFilter::getDefaultImpl()->uninstall();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpInputFilter::filterInputEvent(const ::aidl::android::view::InputEvent& in_event, int32_t in_policyFlags) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_event);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_policyFlags);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 2 /*filterInputEvent*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IInputFilter::getDefaultImpl()) {
    _aidl_status = IInputFilter::getDefaultImpl()->filterInputEvent(in_event, in_policyFlags);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnInputFilter
BnInputFilter::BnInputFilter() {}
BnInputFilter::~BnInputFilter() {}
::ndk::SpAIBinder BnInputFilter::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_IInputFilter_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IInputFilter
const char* IInputFilter::descriptor = "android.view.IInputFilter";
IInputFilter::IInputFilter() {}
IInputFilter::~IInputFilter() {}


std::shared_ptr<IInputFilter> IInputFilter::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_IInputFilter_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpInputFilter>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IInputFilter>(interface);
  }
  return ::ndk::SharedRefBase::make<BpInputFilter>(binder);
}

binder_status_t IInputFilter::writeToParcel(AParcel* parcel, const std::shared_ptr<IInputFilter>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IInputFilter::readFromParcel(const AParcel* parcel, std::shared_ptr<IInputFilter>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IInputFilter::fromBinder(binder);
  return STATUS_OK;
}
bool IInputFilter::setDefaultImpl(const std::shared_ptr<IInputFilter>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IInputFilter::default_impl);
  if (impl) {
    IInputFilter::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IInputFilter>& IInputFilter::getDefaultImpl() {
  return IInputFilter::default_impl;
}
std::shared_ptr<IInputFilter> IInputFilter::default_impl = nullptr;
::ndk::ScopedAStatus IInputFilterDefault::install(const std::shared_ptr<::aidl::android::view::IInputFilterHost>& /*in_host*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IInputFilterDefault::uninstall() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IInputFilterDefault::filterInputEvent(const ::aidl::android::view::InputEvent& /*in_event*/, int32_t /*in_policyFlags*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IInputFilterDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IInputFilterDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
