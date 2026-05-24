/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayChangeWindowController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/IDisplayChangeWindowController.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnDisplayChangeWindowCallback.h>
#include <aidl/android/view/BnDisplayChangeWindowController.h>
#include <aidl/android/view/BpDisplayChangeWindowCallback.h>
#include <aidl/android/view/BpDisplayChangeWindowController.h>
#include <aidl/android/view/IDisplayChangeWindowCallback.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_IDisplayChangeWindowController_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnDisplayChangeWindowController> _aidl_impl = std::static_pointer_cast<BnDisplayChangeWindowController>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*onDisplayChange*/): {
      int32_t in_displayId;
      int32_t in_fromRotation;
      int32_t in_toRotation;
      ::aidl::android::window::DisplayAreaInfo in_newDisplayAreaInfo;
      std::shared_ptr<::aidl::android::view::IDisplayChangeWindowCallback> in_callback;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_displayId);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_fromRotation);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_toRotation);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_newDisplayAreaInfo);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_callback);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onDisplayChange(in_displayId, in_fromRotation, in_toRotation, in_newDisplayAreaInfo, in_callback);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_IDisplayChangeWindowController_clazz = ::ndk::ICInterface::defineClass(IDisplayChangeWindowController::descriptor, _aidl_android_view_IDisplayChangeWindowController_onTransact, nullptr, 0);

BpDisplayChangeWindowController::BpDisplayChangeWindowController(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpDisplayChangeWindowController::~BpDisplayChangeWindowController() {}

::ndk::ScopedAStatus BpDisplayChangeWindowController::onDisplayChange(int32_t in_displayId, int32_t in_fromRotation, int32_t in_toRotation, const ::aidl::android::window::DisplayAreaInfo& in_newDisplayAreaInfo, const std::shared_ptr<::aidl::android::view::IDisplayChangeWindowCallback>& in_callback) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_displayId);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_fromRotation);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_toRotation);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_newDisplayAreaInfo);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_callback);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*onDisplayChange*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayChangeWindowController::getDefaultImpl()) {
    _aidl_status = IDisplayChangeWindowController::getDefaultImpl()->onDisplayChange(in_displayId, in_fromRotation, in_toRotation, in_newDisplayAreaInfo, in_callback);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnDisplayChangeWindowController
BnDisplayChangeWindowController::BnDisplayChangeWindowController() {}
BnDisplayChangeWindowController::~BnDisplayChangeWindowController() {}
::ndk::SpAIBinder BnDisplayChangeWindowController::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_IDisplayChangeWindowController_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IDisplayChangeWindowController
const char* IDisplayChangeWindowController::descriptor = "android.view.IDisplayChangeWindowController";
IDisplayChangeWindowController::IDisplayChangeWindowController() {}
IDisplayChangeWindowController::~IDisplayChangeWindowController() {}


std::shared_ptr<IDisplayChangeWindowController> IDisplayChangeWindowController::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_IDisplayChangeWindowController_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpDisplayChangeWindowController>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IDisplayChangeWindowController>(interface);
  }
  return ::ndk::SharedRefBase::make<BpDisplayChangeWindowController>(binder);
}

binder_status_t IDisplayChangeWindowController::writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayChangeWindowController>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IDisplayChangeWindowController::readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayChangeWindowController>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IDisplayChangeWindowController::fromBinder(binder);
  return STATUS_OK;
}
bool IDisplayChangeWindowController::setDefaultImpl(const std::shared_ptr<IDisplayChangeWindowController>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IDisplayChangeWindowController::default_impl);
  if (impl) {
    IDisplayChangeWindowController::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IDisplayChangeWindowController>& IDisplayChangeWindowController::getDefaultImpl() {
  return IDisplayChangeWindowController::default_impl;
}
std::shared_ptr<IDisplayChangeWindowController> IDisplayChangeWindowController::default_impl = nullptr;
::ndk::ScopedAStatus IDisplayChangeWindowControllerDefault::onDisplayChange(int32_t /*in_displayId*/, int32_t /*in_fromRotation*/, int32_t /*in_toRotation*/, const ::aidl::android::window::DisplayAreaInfo& /*in_newDisplayAreaInfo*/, const std::shared_ptr<::aidl::android::view::IDisplayChangeWindowCallback>& /*in_callback*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IDisplayChangeWindowControllerDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IDisplayChangeWindowControllerDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
