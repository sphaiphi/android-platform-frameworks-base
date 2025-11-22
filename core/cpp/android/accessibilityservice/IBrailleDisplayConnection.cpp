/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=. --out=. --include=/home/roto/git/android_frameworks_base/core/java --include=/home/roto/git/android_frameworks_base/graphics/java /home/roto/git/android_frameworks_base/core/java/android/accessibilityservice/IBrailleDisplayConnection.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/accessibilityservice/IBrailleDisplayConnection.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/accessibilityservice/BnBrailleDisplayConnection.h>
#include <aidl/android/accessibilityservice/BpBrailleDisplayConnection.h>

namespace aidl {
namespace android {
namespace accessibilityservice {
static binder_status_t _aidl_android_accessibilityservice_IBrailleDisplayConnection_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnBrailleDisplayConnection> _aidl_impl = std::static_pointer_cast<BnBrailleDisplayConnection>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*disconnect*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->disconnect();
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*write*/): {
      std::vector<uint8_t> in_output;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_output);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->write(in_output);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_accessibilityservice_IBrailleDisplayConnection_clazz = ::ndk::ICInterface::defineClass(IBrailleDisplayConnection::descriptor, _aidl_android_accessibilityservice_IBrailleDisplayConnection_onTransact, nullptr, 0);

BpBrailleDisplayConnection::BpBrailleDisplayConnection(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpBrailleDisplayConnection::~BpBrailleDisplayConnection() {}

::ndk::ScopedAStatus BpBrailleDisplayConnection::disconnect() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*disconnect*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IBrailleDisplayConnection::getDefaultImpl()) {
    _aidl_status = IBrailleDisplayConnection::getDefaultImpl()->disconnect();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpBrailleDisplayConnection::write(const std::vector<uint8_t>& in_output) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_output);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 1 /*write*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IBrailleDisplayConnection::getDefaultImpl()) {
    _aidl_status = IBrailleDisplayConnection::getDefaultImpl()->write(in_output);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnBrailleDisplayConnection
BnBrailleDisplayConnection::BnBrailleDisplayConnection() {}
BnBrailleDisplayConnection::~BnBrailleDisplayConnection() {}
::ndk::SpAIBinder BnBrailleDisplayConnection::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_accessibilityservice_IBrailleDisplayConnection_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IBrailleDisplayConnection
const char* IBrailleDisplayConnection::descriptor = "android.accessibilityservice.IBrailleDisplayConnection";
IBrailleDisplayConnection::IBrailleDisplayConnection() {}
IBrailleDisplayConnection::~IBrailleDisplayConnection() {}


std::shared_ptr<IBrailleDisplayConnection> IBrailleDisplayConnection::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_accessibilityservice_IBrailleDisplayConnection_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpBrailleDisplayConnection>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IBrailleDisplayConnection>(interface);
  }
  return ::ndk::SharedRefBase::make<BpBrailleDisplayConnection>(binder);
}

binder_status_t IBrailleDisplayConnection::writeToParcel(AParcel* parcel, const std::shared_ptr<IBrailleDisplayConnection>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IBrailleDisplayConnection::readFromParcel(const AParcel* parcel, std::shared_ptr<IBrailleDisplayConnection>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IBrailleDisplayConnection::fromBinder(binder);
  return STATUS_OK;
}
bool IBrailleDisplayConnection::setDefaultImpl(const std::shared_ptr<IBrailleDisplayConnection>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IBrailleDisplayConnection::default_impl);
  if (impl) {
    IBrailleDisplayConnection::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IBrailleDisplayConnection>& IBrailleDisplayConnection::getDefaultImpl() {
  return IBrailleDisplayConnection::default_impl;
}
std::shared_ptr<IBrailleDisplayConnection> IBrailleDisplayConnection::default_impl = nullptr;
::ndk::ScopedAStatus IBrailleDisplayConnectionDefault::disconnect() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IBrailleDisplayConnectionDefault::write(const std::vector<uint8_t>& /*in_output*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IBrailleDisplayConnectionDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IBrailleDisplayConnectionDefault::isRemote() {
  return false;
}
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
