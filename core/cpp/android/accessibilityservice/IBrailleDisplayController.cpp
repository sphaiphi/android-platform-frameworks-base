/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IBrailleDisplayController.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/accessibilityservice/IBrailleDisplayController.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/accessibilityservice/BnBrailleDisplayConnection.h>
#include <aidl/android/accessibilityservice/BnBrailleDisplayController.h>
#include <aidl/android/accessibilityservice/BpBrailleDisplayConnection.h>
#include <aidl/android/accessibilityservice/BpBrailleDisplayController.h>
#include <aidl/android/accessibilityservice/IBrailleDisplayConnection.h>

namespace aidl {
namespace android {
namespace accessibilityservice {
static binder_status_t _aidl_android_accessibilityservice_IBrailleDisplayController_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnBrailleDisplayController> _aidl_impl = std::static_pointer_cast<BnBrailleDisplayController>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*onConnected*/): {
      std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayConnection> in_connection;
      std::vector<uint8_t> in_hidDescriptor;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_connection);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_hidDescriptor);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onConnected(in_connection, in_hidDescriptor);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*onConnectionFailed*/): {
      int32_t in_error;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_error);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onConnectionFailed(in_error);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 2 /*onInput*/): {
      std::vector<uint8_t> in_input;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_input);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onInput(in_input);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 3 /*onDisconnected*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onDisconnected();
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_accessibilityservice_IBrailleDisplayController_clazz = ::ndk::ICInterface::defineClass(IBrailleDisplayController::descriptor, _aidl_android_accessibilityservice_IBrailleDisplayController_onTransact, nullptr, 0);

BpBrailleDisplayController::BpBrailleDisplayController(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpBrailleDisplayController::~BpBrailleDisplayController() {}

::ndk::ScopedAStatus BpBrailleDisplayController::onConnected(const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayConnection>& in_connection, const std::vector<uint8_t>& in_hidDescriptor) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_connection);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_hidDescriptor);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*onConnected*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IBrailleDisplayController::getDefaultImpl()) {
    _aidl_status = IBrailleDisplayController::getDefaultImpl()->onConnected(in_connection, in_hidDescriptor);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpBrailleDisplayController::onConnectionFailed(int32_t in_error) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_error);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 1 /*onConnectionFailed*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IBrailleDisplayController::getDefaultImpl()) {
    _aidl_status = IBrailleDisplayController::getDefaultImpl()->onConnectionFailed(in_error);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpBrailleDisplayController::onInput(const std::vector<uint8_t>& in_input) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_input);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 2 /*onInput*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IBrailleDisplayController::getDefaultImpl()) {
    _aidl_status = IBrailleDisplayController::getDefaultImpl()->onInput(in_input);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpBrailleDisplayController::onDisconnected() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 3 /*onDisconnected*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IBrailleDisplayController::getDefaultImpl()) {
    _aidl_status = IBrailleDisplayController::getDefaultImpl()->onDisconnected();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnBrailleDisplayController
BnBrailleDisplayController::BnBrailleDisplayController() {}
BnBrailleDisplayController::~BnBrailleDisplayController() {}
::ndk::SpAIBinder BnBrailleDisplayController::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_accessibilityservice_IBrailleDisplayController_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IBrailleDisplayController
const char* IBrailleDisplayController::descriptor = "android.accessibilityservice.IBrailleDisplayController";
IBrailleDisplayController::IBrailleDisplayController() {}
IBrailleDisplayController::~IBrailleDisplayController() {}


std::shared_ptr<IBrailleDisplayController> IBrailleDisplayController::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_accessibilityservice_IBrailleDisplayController_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpBrailleDisplayController>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IBrailleDisplayController>(interface);
  }
  return ::ndk::SharedRefBase::make<BpBrailleDisplayController>(binder);
}

binder_status_t IBrailleDisplayController::writeToParcel(AParcel* parcel, const std::shared_ptr<IBrailleDisplayController>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IBrailleDisplayController::readFromParcel(const AParcel* parcel, std::shared_ptr<IBrailleDisplayController>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IBrailleDisplayController::fromBinder(binder);
  return STATUS_OK;
}
bool IBrailleDisplayController::setDefaultImpl(const std::shared_ptr<IBrailleDisplayController>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IBrailleDisplayController::default_impl);
  if (impl) {
    IBrailleDisplayController::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IBrailleDisplayController>& IBrailleDisplayController::getDefaultImpl() {
  return IBrailleDisplayController::default_impl;
}
std::shared_ptr<IBrailleDisplayController> IBrailleDisplayController::default_impl = nullptr;
::ndk::ScopedAStatus IBrailleDisplayControllerDefault::onConnected(const std::shared_ptr<::aidl::android::accessibilityservice::IBrailleDisplayConnection>& /*in_connection*/, const std::vector<uint8_t>& /*in_hidDescriptor*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IBrailleDisplayControllerDefault::onConnectionFailed(int32_t /*in_error*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IBrailleDisplayControllerDefault::onInput(const std::vector<uint8_t>& /*in_input*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IBrailleDisplayControllerDefault::onDisconnected() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IBrailleDisplayControllerDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IBrailleDisplayControllerDefault::isRemote() {
  return false;
}
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
