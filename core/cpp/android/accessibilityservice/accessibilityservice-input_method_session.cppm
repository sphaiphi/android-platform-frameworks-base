// accessibilityservice-input_method_session.cppm
export module accessibilityservice:input_method_session;

import :types;
import <cstdint>;
import <memory>;

export namespace android::accessibilityservice {

// Forward declaration if not imported
class IRemoteAccessibilityInputConnection;

class IAccessibilityInputMethodSession {
public:
    virtual ~IAccessibilityInputMethodSession() = default;

    virtual void finish_input() = 0;

    virtual void update_selection(
        std::int32_t old_sel_start, std::int32_t old_sel_end,
        std::int32_t new_sel_start, std::int32_t new_sel_end,
        std::int32_t candidates_start, std::int32_t candidates_end) = 0;

    virtual void invalidate_input(
        const EditorInfo& editor_info,
        std::shared_ptr<IRemoteAccessibilityInputConnection> connection,
        std::int32_t session_id) = 0;
};

} // namespace android::accessibilityservice