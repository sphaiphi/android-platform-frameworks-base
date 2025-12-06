// accessibility_input_method_session.cppm
export module accessibilityservice:accessibility_input_method_session;

import :accessibilityservice_types;
import <cstdint>;
import <memory>;

export namespace android::accessibilityservice {

/**
 * @brief Interface for an accessibility input method session.
 *
 * This abstract class defines the contract for an accessibility service's input
 * method session. It receives notifications from the system about input state changes.
 * Implementations of this interface are NOT required to be thread-safe.
 */
class IAccessibilityInputMethodSession {
public:
    virtual ~IAccessibilityInputMethodSession() = default;

    /**
     * @brief Called when the input session is finished and should be cleaned up.
     */
    virtual void finish_input() = 0;

    /**
     * @brief Notifies of a change in text selection or cursor position.
     */
    virtual void update_selection(
        std::int32_t old_sel_start, std::int32_t old_sel_end,
        std::int32_t new_sel_start, std::int32_t new_sel_end,
        std::int32_t candidates_start, std::int32_t candidates_end) = 0;

    /**
     * @brief Notifies that the editor's state is invalid and provides a new connection.
     * @param editor_info The updated information about the text editor.
     * @param connection The new remote connection to the text editor.
     * @param session_id A unique identifier for the new session.
     */
    virtual void invalidate_input(
        const EditorInfo& editor_info,
        std::shared_ptr<IRemoteAccessibilityInputConnection> connection,
        std::int32_t session_id) = 0;
};

} // namespace android::accessibilityservice