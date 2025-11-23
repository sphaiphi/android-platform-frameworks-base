// accessibility_service_impl.cpp
// In a real build system, this file would not need to re-import the module.
// This is a workaround for single-file compilation examples.
#include <iostream>
#include <print>

import <binder/AIBinder.h>;
import <binder/AParcel.h>;
import <android/looper.h>;
import accessibility_service;
import ndk_executor; // Make sure this is available

namespace accessibility {

//================================================================================
// EditorInfo Implementation
//================================================================================

[[nodiscard]] auto EditorInfo::write_to_parcel(AParcel* parcel) const -> std::expected<void, int32_t> {
    // NDK AParcel string writing returns a media_status_t (which is an int32_t)
    if (auto status = AParcel_writeString(parcel, package_name.c_str()); status != 0) {
        return std::unexpected(status);
    }
    // ... write other fields ...
    return {};
}

[[nodiscard]] auto EditorInfo::read_from_parcel(const AParcel* parcel) -> std::expected<void, int32_t> {
    char* str = nullptr;
    if (auto status = AParcel_readString(parcel, &str); status != 0) {
        return std::unexpected(status);
    }
    package_name = str; // copy the string
    // AParcel_readString allocates memory that the caller must free.
    // In a real library, you would use a custom deleter with unique_ptr.
    // For this example, we manually manage it.
    AIBinder_release(reinterpret_cast<AIBinder*>(str)); // This is the documented way to free the string memory

    // ... read other fields ...
    return {};
}


//================================================================================
// AccessibilityInputMethodSessionWrapper Implementation
//================================================================================

// Static `onTransact` entry point required by the NDK Binder C API.
// It retrieves the `this` pointer and calls the member function.
auto AccessibilityInputMethodSessionWrapper::on_transact_entry(
    AIBinder* binder, int32_t code, const AParcel* in, AParcel* out) -> int {
    
    // Retrieve the wrapper instance from the binder object.
    auto* wrapper = static_cast<AccessibilityInputMethodSessionWrapper*>(AIBinder_getUserData(binder));
    if (!wrapper) {
        std::println(stderr, "AccessibilityWrapper: Binder has no associated wrapper object.");
        return -1; // General error
    }

    auto transaction_code = static_cast<TransactionCode>(code);
    auto result = wrapper->on_transact(transaction_code, in, out);
    if (!result) {
        std::println(stderr, "AccessibilityWrapper: Transaction failed with code {}", result.error());
        return result.error();
    }
    return 0; // Success
}

// Factory function
[[nodiscard]] auto AccessibilityInputMethodSessionWrapper::create(
    std::shared_ptr<ndk::IThreadExecutor> executor,
    std::shared_ptr<IAccessibilityInputMethodSession> session)
    -> std::expected<std::shared_ptr<AccessibilityInputMethodSessionWrapper>, std::string> {

    if (!executor || !session) {
        return std::unexpected("Executor and session must not be null.");
    }
    
    // Use `new` because make_shared cannot access the private constructor.
    // The custom deleter will ensure `delete` is called.
    auto wrapper = std::shared_ptr<AccessibilityInputMethodSessionWrapper>(
        new AccessibilityInputMethodSessionWrapper(std::move(executor), std::move(session))
    );

    // Create the AIBinder_Class, a "vtable" for our binder object.
    // This only needs to be done once per process.
    static AIBinder_Class* binder_class = []{
        auto* cls = AIBinder_Class_new(
            "accessibility::AccessibilityInputMethodSessionWrapper",
            nullptr, // no constructor
            nullptr, // no destructor
            on_transact_entry);
        return cls;
    }();

    // Create a binder instance and associate our wrapper with it.
    wrapper->binder_ = AIBinder_new(binder_class, wrapper.get());
    if (!wrapper->binder_) {
        return std::unexpected("Failed to create AIBinder instance.");
    }
    
    AIBinder_incStrong(wrapper->binder_); // The wrapper now holds one strong count.
    
    return wrapper;
}


AccessibilityInputMethodSessionWrapper::AccessibilityInputMethodSessionWrapper(
    std::shared_ptr<ndk::IThreadExecutor> executor,
    std::shared_ptr<IAccessibilityInputMethodSession> session)
    : executor_{std::move(executor)}, session_{std::move(session)} {}

AccessibilityInputMethodSessionWrapper::~AccessibilityInputMethodSessionWrapper() {
    if (binder_) {
        // The binder might outlive the wrapper if other processes hold a reference.
        // We null out our user data to prevent use-after-free in on_transact.
        AIBinder_setUserData(binder_, nullptr); 
        AIBinder_decStrong(binder_);
    }
    std::println("AccessibilityInputMethodSessionWrapper destroyed.");
}


// Instance-specific transaction handler.
auto AccessibilityInputMethodSessionWrapper::on_transact(
    TransactionCode code, const AParcel* in, AParcel* /*out*/) -> std::expected<void, int32_t> {

    // Check if the session is still alive. If not, do nothing.
    // This is a thread-safe check on the shared_ptr.
    if (!std::atomic_load(&session_)) {
        return {}; // Session is finished, ignore the call.
    }

    switch (code) {
        case TransactionCode::finish_input: {
            // Capture nothing, as there are no arguments.
            executor_->post([session = session_] {
                session->finish_input();
            });
            break;
        }

        case TransactionCode::update_selection: {
            // Read all arguments from the parcel.
            SelIndex old_ss, old_se, new_ss, new_se, cand_s, cand_e;
            AParcel_readInt32(in, &old_ss.value);
            AParcel_readInt32(in, &old_se.value);
            AParcel_readInt32(in, &new_ss.value);
            AParcel_readInt32(in, &new_se.value);
            AParcel_readInt32(in, &cand_s.value);
            AParcel_readInt32(in, &cand_e.value);

            // Post the task, capturing all arguments BY VALUE.
            executor_->post([session = session_, old_ss, old_se, new_ss, new_se, cand_s, cand_e] {
                session->update_selection(old_ss, old_se, new_ss, new_se, cand_s, cand_e);
            });
            break;
        }
        
        case TransactionCode::invalidate_input: {
            EditorInfo info;
            if (auto res = info.read_from_parcel(in); !res) return std::unexpected(res.error());

            SessionId id;
            AParcel_readInt32(in, &id.value);
            
            executor_->post([session = session_, info = std::move(info), id] () mutable {
                session->invalidate_input(std::move(info), id);
            });
            break;
        }

        case TransactionCode::finish_session: {
            // This is a special case. We want to release the session object.
            // Post the task to the executor to ensure thread-safe release.
            executor_->post([this] {
                do_finish_session();
            });
            break;
        }

        default:
            // Unrecognized transaction code.
            return std::unexpected(-1); // Or a more specific error code
    }

    return {};
}

void AccessibilityInputMethodSessionWrapper::do_finish_session() {
    // This runs on the executor's thread.
    // Atomically reset the shared_ptr, releasing our reference to the session.
    // If this is the last reference, the session object is destroyed on this thread.
    std::atomic_store(&session_, {});
    std::println("Session finished and released on executor thread.");
}

}
