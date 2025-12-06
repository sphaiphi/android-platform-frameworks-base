/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: /home/roto/android/build-tools/36.1.0/aidl --lang=ndk --header_out=/home/roto/git/android-platform-frameworks-base/core/cpp --out=/home/roto/git/android-platform-frameworks-base/core/cpp --include=/home/roto/git/android-platform-frameworks-base/core/cpp/ /home/roto/git/android-platform-frameworks-base/core/cpp/android/accessibilityservice/IAccessibilityInputMethodSession.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#include "aidl/android/accessibilityservice/IAccessibilityInputMethodSession.h"

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_parcel_utils.h>
#include <android/binder_status.h>
#include <aidl/android/accessibilityservice/BnAccessibilityInputMethodSession.h>
#include <aidl/android/accessibilityservice/BnRemoteAccessibilityInputConnection.h>
#include <aidl/android/accessibilityservice/BpAccessibilityInputMethodSession.h>
#include <aidl/android/accessibilityservice/BpRemoteAccessibilityInputConnection.h>
#include <aidl/android/accessibilityservice/IRemoteAccessibilityInputConnection.h>

namespace aidl {
namespace android {
namespace accessibilityservice {
static binder_status_t _aidl_android_accessibilityservice_IAccessibilityInputMethodSession_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnAccessibilityInputMethodSession> _aidl_impl = std::static_pointer_cast<BnAccessibilityInputMethodSession>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*finishInput*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->finishInput();
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*updateSelection*/): {
      int32_t in_oldSelStart;
      int32_t in_oldSelEnd;
      int32_t in_newSelStart;
      int32_t in_newSelEnd;
      int32_t in_candidatesStart;
      int32_t in_candidatesEnd;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_oldSelStart);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_oldSelEnd);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_newSelStart);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_newSelEnd);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_candidatesStart);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_candidatesEnd);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->updateSelection(in_oldSelStart, in_oldSelEnd, in_newSelStart, in_newSelEnd, in_candidatesStart, in_candidatesEnd);
      _aidl_ret_status = STATUS_OK;
      break;
    }
    case (FIRST_CALL_TRANSACTION + 2 /*invalidateInput*/): {
      ::aidl::android::view::inputmethod::EditorInfo in_editorInfo;
      std::shared_ptr<::aidl::android::accessibilityservice::IRemoteAccessibilityInputConnection> in_connection;
      int32_t in_sessionId;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_editorInfo);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_connection);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_sessionId);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->invalidateInput(in_editorInfo, in_connection, in_sessionId);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_android_accessibilityservice_IAccessibilityInputMethodSession_clazz = ::ndk::ICInterface::defineClass(IAccessibilityInputMethodSession::descriptor, _aidl_android_accessibilityservice_IAccessibilityInputMethodSession_onTransact, nullptr, 0);

BpAccessibilityInputMethodSession::BpAccessibilityInputMethodSession(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpAccessibilityInputMethodSession::~BpAccessibilityInputMethodSession() {}

::ndk::ScopedAStatus BpAccessibilityInputMethodSession::finishInput() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*finishInput*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IAccessibilityInputMethodSession::getDefaultImpl()) {
    _aidl_status = IAccessibilityInputMethodSession::getDefaultImpl()->finishInput();
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpAccessibilityInputMethodSession::updateSelection(int32_t in_oldSelStart, int32_t in_oldSelEnd, int32_t in_newSelStart, int32_t in_newSelEnd, int32_t in_candidatesStart, int32_t in_candidatesEnd) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_oldSelStart);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_oldSelEnd);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_newSelStart);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_newSelEnd);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_candidatesStart);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_candidatesEnd);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 1 /*updateSelection*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IAccessibilityInputMethodSession::getDefaultImpl()) {
    _aidl_status = IAccessibilityInputMethodSession::getDefaultImpl()->updateSelection(in_oldSelStart, in_oldSelEnd, in_newSelStart, in_newSelEnd, in_candidatesStart, in_candidatesEnd);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpAccessibilityInputMethodSession::invalidateInput(const ::aidl::android::view::inputmethod::EditorInfo& in_editorInfo, const std::shared_ptr<::aidl::android::accessibilityservice::IRemoteAccessibilityInputConnection>& in_connection, int32_t in_sessionId) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_editorInfo);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_connection);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_sessionId);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 2 /*invalidateInput*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IAccessibilityInputMethodSession::getDefaultImpl()) {
    _aidl_status = IAccessibilityInputMethodSession::getDefaultImpl()->invalidateInput(in_editorInfo, in_connection, in_sessionId);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnAccessibilityInputMethodSession
BnAccessibilityInputMethodSession::BnAccessibilityInputMethodSession() {}
BnAccessibilityInputMethodSession::~BnAccessibilityInputMethodSession() {}
::ndk::SpAIBinder BnAccessibilityInputMethodSession::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_android_accessibilityservice_IAccessibilityInputMethodSession_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IAccessibilityInputMethodSession
const char* IAccessibilityInputMethodSession::descriptor = "android.accessibilityservice.IAccessibilityInputMethodSession";
IAccessibilityInputMethodSession::IAccessibilityInputMethodSession() {}
IAccessibilityInputMethodSession::~IAccessibilityInputMethodSession() {}


std::shared_ptr<IAccessibilityInputMethodSession> IAccessibilityInputMethodSession::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_android_accessibilityservice_IAccessibilityInputMethodSession_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpAccessibilityInputMethodSession>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IAccessibilityInputMethodSession>(interface);
  }
  return ::ndk::SharedRefBase::make<BpAccessibilityInputMethodSession>(binder);
}

binder_status_t IAccessibilityInputMethodSession::writeToParcel(AParcel* parcel, const std::shared_ptr<IAccessibilityInputMethodSession>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IAccessibilityInputMethodSession::readFromParcel(const AParcel* parcel, std::shared_ptr<IAccessibilityInputMethodSession>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IAccessibilityInputMethodSession::fromBinder(binder);
  return STATUS_OK;
}
bool IAccessibilityInputMethodSession::setDefaultImpl(const std::shared_ptr<IAccessibilityInputMethodSession>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IAccessibilityInputMethodSession::default_impl);
  if (impl) {
    IAccessibilityInputMethodSession::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IAccessibilityInputMethodSession>& IAccessibilityInputMethodSession::getDefaultImpl() {
  return IAccessibilityInputMethodSession::default_impl;
}
std::shared_ptr<IAccessibilityInputMethodSession> IAccessibilityInputMethodSession::default_impl = nullptr;
::ndk::ScopedAStatus IAccessibilityInputMethodSessionDefault::finishInput() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IAccessibilityInputMethodSessionDefault::updateSelection(int32_t /*in_oldSelStart*/, int32_t /*in_oldSelEnd*/, int32_t /*in_newSelStart*/, int32_t /*in_newSelEnd*/, int32_t /*in_candidatesStart*/, int32_t /*in_candidatesEnd*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IAccessibilityInputMethodSessionDefault::invalidateInput(const ::aidl::android::view::inputmethod::EditorInfo& /*in_editorInfo*/, const std::shared_ptr<::aidl::android::accessibilityservice::IRemoteAccessibilityInputConnection>& /*in_connection*/, int32_t /*in_sessionId*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IAccessibilityInputMethodSessionDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IAccessibilityInputMethodSessionDefault::isRemote() {
  return false;
}
}  // namespace accessibilityservice
}  // namespace android
}  // namespace aidl
