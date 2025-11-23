// accessibility_service.cppm
export module accessibility_service;

import <memory>;
import <string>;
import <string_view>;
import <functional>;
import <expected>;
import <cstdint>;
import <utility>;

// Forward declare NDK types to keep them out of the global module fragment.
// In a real build system, these would be included properly.
struct AIBinder;
struct AParcel;

// Use the provided NDK executor interface
export import ndk_executor;

export namespace accessibility {

//================================================================================
// Strong Types and Domain-Specific Data Structures
//================================================================================

struct SessionId {
    int32_t value;
    auto operator<=>(const SessionId&) const = default;
};

struct SelIndex {
    int32_t value;
    auto operator<=>(const SelIndex&) const = default;
};

// Represents the data passed in `invalidateInput`.
// A full implementation would mirror android.view.inputmethod.EditorInfo
struct EditorInfo {
    std::string package_name;
    // ... other fields as needed

    // Methods for Binder serialization/deserialization
    // These mirror the Parcelable interface concept. [2]
    [[nodiscard]] auto write_to_parcel(AParcel* parcel) const -> std::expected<void, int32_t>;
    [[nodiscard]] auto read_from_parcel(const AParcel* parcel) -> std::expected<void, int32_t>;
};

//================================================================================
// IAccessibilityInputMethodSession (The "Real" Session Interface)
//================================================================================

// Abstract interface for the real session object, which will be executed on a dedicated thread.
class IAccessibilityInputMethodSession {
public:
    virtual ~IAccessibilityInputMethodSession() = default;

    virtual void finish_input() = 0;
    virtual void update_selection(
        SelIndex old_sel_start, SelIndex old_sel_end,
        SelIndex new_sel_start, SelIndex new_sel_end,
        SelIndex candidates_start, SelIndex candidates_end) = 0;
    virtual void invalidate_input(EditorInfo editor_info, SessionId session_id) = 0;
};

//================================================================================
// AccessibilityInputMethodSessionWrapper (The Thread-Safe Binder Proxy)
//================================================================================

// Transaction codes matching the AIDL interface order.
enum class TransactionCode : int32_t {
    finish_input = 1,
    update_selection = 2,
    invalidate_input = 3,
    finish_session = 4,
};

// This class is the core of the solution. It receives binder calls on an arbitrary thread
// and safely dispatches them to the `NdkThreadExecutor` for processing. [3]
class AccessibilityInputMethodSessionWrapper {
public:
    // Factory function to create the wrapper and its underlying Binder object.
    [[nodiscard]] static auto create(
        std::shared_ptr<ndk::IThreadExecutor> executor,
        std::shared_ptr<IAccessibilityInputMethodSession> session)
        -> std::expected<std::shared_ptr<AccessibilityInputMethodSessionWrapper>, std::string>;

    // Non-copyable, non-movable due to managing a native binder object.
    AccessibilityInputMethodSessionWrapper(const AccessibilityInputMethodSessionWrapper&) = delete;
    AccessibilityInputMethodSessionWrapper& operator=(const AccessibilityInputMethodSessionWrapper&) = delete;
    AccessibilityInputMethodSessionWrapper(AccessibilityInputMethodSessionWrapper&&) = delete;
    AccessibilityInputMethodSessionWrapper& operator=(AccessibilityInputMethodSessionWrapper&&) = delete;
    
    ~AccessibilityInputMethodSessionWrapper();

    // Public method to retrieve the binder object for passing to other processes.
    [[nodiscard]] auto as_binder() const -> AIBinder* {
        return binder_;
    }

private:
    // Private constructor, use the `create` factory.
    explicit AccessibilityInputMethodSessionWrapper(
        std::shared_ptr<ndk::IThreadExecutor> executor,
        std::shared_ptr<IAccessibilityInputMethodSession> session);

    // This is the entry point for all incoming Binder calls from the system.
    static auto on_transact_entry(AIBinder* binder, int32_t code, const AParcel* in, AParcel* out) -> int;

    // Instance-specific handler for transactions.
    auto on_transact(TransactionCode code, const AParcel* in, AParcel* out) -> std::expected<void, int32_t>;

    // Private "doer" methods that are posted to the executor.
    // They are guaranteed to run on the correct thread.
    void do_finish_session();

    // Member variables
    std::shared_ptr<ndk::IThreadExecutor> executor_{};
    std::shared_ptr<IAccessibilityInputMethodSession> session_{};
    AIBinder* binder_{nullptr};
};

} // namespace accessibility