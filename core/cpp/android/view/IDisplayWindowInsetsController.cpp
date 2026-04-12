/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/java/ /home/roto/git/android-platform-frameworks-base/core/java/android/view/IDisplayWindowInsetsController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/view/IDisplayWindowInsetsController.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/view/BnDisplayWindowInsetsController.h>
#include <aidl/android/view/BpDisplayWindowInsetsController.h>

namespace aidl {
namespace android {
namespace view {
static binder_status_t _aidl_android_view_IDisplayWindowInsetsController_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnDisplayWindowInsetsController> _aidl_impl = std::static_pointer_cast<BnDisplayWindowInsetsController>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*topFocusedWindowChanged*/): {
      ::aidl::android::content::ComponentName in_component;
      int32_t in_requestedVisibleTypes;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_component);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_requestedVisibleTypes);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->topFocusedWindowChanged(in_component, in_requestedVisibleTypes);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*insetsChanged*/): {
      ::aidl::android::view::InsetsState in_insetsState;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_insetsState);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->insetsChanged(in_insetsState);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 2 /*insetsControlChanged*/): {
      ::aidl::android::view::InsetsState in_insetsState;
      std::vector<::aidl::android::view::InsetsSourceControl> in_activeControls;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_insetsState);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_activeControls);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->insetsControlChanged(in_insetsState, in_activeControls);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 3 /*showInsets*/): {
      int32_t in_types;
      bool in_fromIme;
      std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token> in_statsToken;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_types);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_fromIme);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readNullableData(_aidl_in, &in_statsToken);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->showInsets(in_types, in_fromIme, in_statsToken);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 4 /*hideInsets*/): {
      int32_t in_types;
      bool in_fromIme;
      std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token> in_statsToken;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_types);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_fromIme);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readNullableData(_aidl_in, &in_statsToken);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->hideInsets(in_types, in_fromIme, in_statsToken);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 5 /*setImeInputTargetRequestedVisibility*/): {
      bool in_visible;
      ::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token in_statsToken;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_visible);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_statsToken);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->setImeInputTargetRequestedVisibility(in_visible, in_statsToken);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_view_IDisplayWindowInsetsController_clazz = ::ndk::ICInterface::defineClass(IDisplayWindowInsetsController::descriptor, _aidl_android_view_IDisplayWindowInsetsController_onTransact, nullptr, 0);

BpDisplayWindowInsetsController::BpDisplayWindowInsetsController(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpDisplayWindowInsetsController::~BpDisplayWindowInsetsController() {}

::ndk::ScopedAStatus BpDisplayWindowInsetsController::topFocusedWindowChanged(const ::aidl::android::content::ComponentName& in_component, int32_t in_requestedVisibleTypes) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_component);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_requestedVisibleTypes);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*topFocusedWindowChanged*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayWindowInsetsController::getDefaultImpl()) {
    _aidl_status = IDisplayWindowInsetsController::getDefaultImpl()->topFocusedWindowChanged(in_component, in_requestedVisibleTypes);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpDisplayWindowInsetsController::insetsChanged(const ::aidl::android::view::InsetsState& in_insetsState) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_insetsState);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 1 /*insetsChanged*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayWindowInsetsController::getDefaultImpl()) {
    _aidl_status = IDisplayWindowInsetsController::getDefaultImpl()->insetsChanged(in_insetsState);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpDisplayWindowInsetsController::insetsControlChanged(const ::aidl::android::view::InsetsState& in_insetsState, const std::vector<::aidl::android::view::InsetsSourceControl>& in_activeControls) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_insetsState);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_activeControls);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 2 /*insetsControlChanged*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayWindowInsetsController::getDefaultImpl()) {
    _aidl_status = IDisplayWindowInsetsController::getDefaultImpl()->insetsControlChanged(in_insetsState, in_activeControls);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpDisplayWindowInsetsController::showInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_types);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_fromIme);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeNullableData(_aidl_in.get(), in_statsToken);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 3 /*showInsets*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayWindowInsetsController::getDefaultImpl()) {
    _aidl_status = IDisplayWindowInsetsController::getDefaultImpl()->showInsets(in_types, in_fromIme, in_statsToken);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpDisplayWindowInsetsController::hideInsets(int32_t in_types, bool in_fromIme, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& in_statsToken) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_types);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_fromIme);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeNullableData(_aidl_in.get(), in_statsToken);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 4 /*hideInsets*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayWindowInsetsController::getDefaultImpl()) {
    _aidl_status = IDisplayWindowInsetsController::getDefaultImpl()->hideInsets(in_types, in_fromIme, in_statsToken);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpDisplayWindowInsetsController::setImeInputTargetRequestedVisibility(bool in_visible, const ::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token& in_statsToken) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_visible);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_statsToken);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 5 /*setImeInputTargetRequestedVisibility*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IDisplayWindowInsetsController::getDefaultImpl()) {
    _aidl_status = IDisplayWindowInsetsController::getDefaultImpl()->setImeInputTargetRequestedVisibility(in_visible, in_statsToken);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnDisplayWindowInsetsController
BnDisplayWindowInsetsController::BnDisplayWindowInsetsController() {}
BnDisplayWindowInsetsController::~BnDisplayWindowInsetsController() {}
::ndk::SpAIBinder BnDisplayWindowInsetsController::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_view_IDisplayWindowInsetsController_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IDisplayWindowInsetsController
const char* IDisplayWindowInsetsController::descriptor = "android.view.IDisplayWindowInsetsController";
IDisplayWindowInsetsController::IDisplayWindowInsetsController() {}
IDisplayWindowInsetsController::~IDisplayWindowInsetsController() {}


std::shared_ptr<IDisplayWindowInsetsController> IDisplayWindowInsetsController::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_view_IDisplayWindowInsetsController_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpDisplayWindowInsetsController>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IDisplayWindowInsetsController>(interface);
  }
  return ::ndk::SharedRefBase::make<BpDisplayWindowInsetsController>(binder);
}

binder_status_t IDisplayWindowInsetsController::writeToParcel(AParcel* parcel, const std::shared_ptr<IDisplayWindowInsetsController>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IDisplayWindowInsetsController::readFromParcel(const AParcel* parcel, std::shared_ptr<IDisplayWindowInsetsController>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IDisplayWindowInsetsController::fromBinder(binder);
  return STATUS_OK;
}
bool IDisplayWindowInsetsController::setDefaultImpl(const std::shared_ptr<IDisplayWindowInsetsController>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IDisplayWindowInsetsController::default_impl);
  if (impl) {
    IDisplayWindowInsetsController::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IDisplayWindowInsetsController>& IDisplayWindowInsetsController::getDefaultImpl() {
  return IDisplayWindowInsetsController::default_impl;
}
std::shared_ptr<IDisplayWindowInsetsController> IDisplayWindowInsetsController::default_impl = nullptr;
::ndk::ScopedAStatus IDisplayWindowInsetsControllerDefault::topFocusedWindowChanged(const ::aidl::android::content::ComponentName& /*in_component*/, int32_t /*in_requestedVisibleTypes*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IDisplayWindowInsetsControllerDefault::insetsChanged(const ::aidl::android::view::InsetsState& /*in_insetsState*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IDisplayWindowInsetsControllerDefault::insetsControlChanged(const ::aidl::android::view::InsetsState& /*in_insetsState*/, const std::vector<::aidl::android::view::InsetsSourceControl>& /*in_activeControls*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IDisplayWindowInsetsControllerDefault::showInsets(int32_t /*in_types*/, bool /*in_fromIme*/, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& /*in_statsToken*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IDisplayWindowInsetsControllerDefault::hideInsets(int32_t /*in_types*/, bool /*in_fromIme*/, const std::optional<::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token>& /*in_statsToken*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IDisplayWindowInsetsControllerDefault::setImeInputTargetRequestedVisibility(bool /*in_visible*/, const ::aidl::android::view::inputmethod::ImeTracker::ImeTracker.Token& /*in_statsToken*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IDisplayWindowInsetsControllerDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IDisplayWindowInsetsControllerDefault::isRemote() {
  return false;
}
}  // namespace view
}  // namespace android
}  // namespace aidl
