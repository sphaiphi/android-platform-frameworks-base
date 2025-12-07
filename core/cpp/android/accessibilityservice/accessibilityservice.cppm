// accessibilityservice.cppm
export module accessibilityservice;

import <memory>;
import <functional>;
import <vector>;
import <string>;
import <chrono>;
import <expected>;
import <optional>;

// Forward declarations for internal types
namespace android::os {
    class Parcel;
}

// Forward-declare dependent types that will be defined elsewhere.
// In a real scenario, these would be imported from their own modules.
export struct EditorInfo;
export class IRemoteAccessibilityInputConnection;

export import :accessibilityservice_types;
export import :accessibility_input_method_session;
export import :accessibility_input_method_session_wrapper;
export import :button_controller_interfaces;
export import ndk_executor; // Export the executor interface for users

export namespace android::accessibilityservice {

// Forward-declare the implementation detail PIMPL class
class AccessibilityServiceImpl;

// The primary abstract base class for developers to implement.
// It follows the RAII pattern and hides implementation details (PIMPL).
class AccessibilityService {
public:
    //========================================================================
    // Public API for the developer
    //========================================================================

    /**
     * @brief Returns the executor for posting tasks to the service's main thread.
     * @return A shared pointer to the thread executor.
     */
    [[nodiscard]] auto get_executor() const -> std::shared_ptr<common::IThreadExecutor>;

    /**
     * @brief Gets the current service configuration information.
     * @return A const reference to the service info.
     */
    [[nodiscard]] auto get_service_info() const -> const AccessibilityServiceInfo&;

    /**
     * @brief Dynamically updates the service's configuration.
     * @param info The new service information to apply.
     */
    void set_service_info(AccessibilityServiceInfo info);

    //========================================================================
    // Callbacks for the developer to override
    //========================================================================

    /**
     * @brief Callback for receiving accessibility events from the system.
     * @param event The event that occurred.
     */
    virtual void on_accessibility_event(const AccessibilityEvent& event) = 0;

    /**
     * @brief Callback requesting the service to interrupt feedback.
     */
    virtual void on_interrupt() = 0;

    /**
     * @brief Called when the system has successfully connected to the service.
     *        This is the ideal place to perform initial setup.
     */
    virtual void on_service_connected() {} // Optional override

    /**
     * @brief Factory callback for creating the input method session.
     * @return A unique_ptr to a developer-defined session implementation.
     */
    virtual auto on_create_input_method_session() -> std::unique_ptr<IAccessibilityInputMethodSession> {
        return nullptr; // Default implementation returns no session
    }

protected:
    // Constructor initializes the PIMPL object, starting the service logic.
    AccessibilityService();

    // The destructor handles cleanup and disconnection.
    virtual ~AccessibilityService();

    // Rule of Five: Explicitly delete copy/move to prevent slicing
    // and ensure unique ownership of the underlying service connection.
    AccessibilityService(const AccessibilityService&) = delete;
    AccessibilityService& operator=(const AccessibilityService&) = delete;
    AccessibilityService(AccessibilityService&&) = delete;
    AccessibilityService& operator=(AccessibilityService&&) = delete;

private:
    // Pointer to Implementation (PIMPL) to hide all private members
    // and implementation details from the user of the class.
    std::unique_ptr<AccessibilityServiceImpl> impl_;
};

// Strong type for display identifiers
struct DisplayId {
    int32_t value{0};
    auto operator<=>(const DisplayId&) const = default;
};

// Represents a 2D point with floating-point coordinates.
struct PointF {
    float x = 0.0f;
    float y = 0.0f;
};

// A simplified, serializable representation of a path.
// The NDK does not provide a direct android.graphics.Path equivalent.
struct Path {
    std::vector<PointF> points;
};

// Describes a single, continuous stroke in a gesture.
// It is an immutable, value-type object.
export class StrokeDescription {
public:
    // C++23: Using std::chrono for type-safe time representation.
    using milliseconds = std::chrono::milliseconds;

    [[nodiscard]] StrokeDescription(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued = false);

    // Creates a new stroke that is a continuation of this one.
    [[nodiscard]] auto continue_stroke(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued) const
        -> std::expected<StrokeDescription, std::string>;
    
    [[nodiscard]] auto get_path() const -> const Path&;
    [[nodiscard]] auto get_start_time() const -> milliseconds;
    [[nodiscard]] auto get_duration() const -> milliseconds;
    [[nodiscard]] auto will_continue() const -> bool;

private:
    friend class GestureDescription;
    friend class android::os::Parcel; // For serialization

    struct StrokeId {
        int32_t value;
    };
    
    Path path_;
    milliseconds start_time_;
    milliseconds duration_;
    bool will_be_continued_;
    StrokeId id_;
    std::optional<StrokeId> continued_stroke_id_;
    
    // Internal constructor for continuation
    StrokeDescription(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued, StrokeId continued_id);
    
    [[nodiscard]] auto get_id() const -> StrokeId;
    [[nodiscard]] auto get_continued_id() const -> std::optional<StrokeId>;
};

// Main immutable container for a complete gesture.
export class GestureDescription {
public:
    using milliseconds = std::chrono::milliseconds;

    // Public constants, mirroring the Java API.
    static constexpr int32_t MAX_STROKE_COUNT = 20;
    static constexpr milliseconds MAX_GESTURE_DURATION = std::chrono::seconds(60);

    // Error types for the builder
    enum class BuildError {
        NO_STROKES_ADDED,
        TOO_MANY_STROKES,
        DURATION_TOO_LONG
    };

    class Builder;

    // Public interface
    [[nodiscard]] auto get_stroke_count() const -> size_t;
    [[nodiscard]] auto get_stroke(size_t index) const -> const StrokeDescription&;
    [[nodiscard]] auto get_display_id() const -> DisplayId;

private:
    // Private constructor to enforce creation via Builder
    explicit GestureDescription(std::vector<StrokeDescription> strokes, DisplayId display_id);

    std::vector<StrokeDescription> strokes_;
    DisplayId display_id_;
};

// Builder for GestureDescription using fluent interface.
export class GestureDescription::Builder {
public:
    Builder() = default;

    // C++23: Deducing this for a perfect-forwarding fluent interface.
    [[nodiscard]] auto add_stroke(this auto&& self, StrokeDescription stroke) -> decltype(auto) {
        strokes_.push_back(std::move(stroke));
        return std::forward<decltype(self)>(self);
    }
    
    [[nodiscard]] auto set_display_id(this auto&& self, DisplayId id) -> decltype(auto) {
        display_id_ = id;
        return std::forward<decltype(self)>(self);
    }

    [[nodiscard]] auto build() && -> std::expected<GestureDescription, BuildError> {
        if (strokes_.empty()) {
            return std::unexpected(BuildError::NO_STROKES_ADDED);
        }
        if (strokes_.size() > MAX_STROKE_COUNT) {
            return std::unexpected(BuildError::TOO_MANY_STROKES);
        }
        
        milliseconds max_end_time{0};
        for(const auto& stroke : strokes_) {
            const auto end_time = stroke.get_start_time() + stroke.get_duration();
            if (end_time > max_end_time) {
                max_end_time = end_time;
            }
        }
        
        if (max_end_time > MAX_GESTURE_DURATION) {
            return std::unexpected(BuildError::DURATION_TOO_LONG);
        }

        return GestureDescription{std::move(strokes_), display_id_};
    }

private:
    std::vector<StrokeDescription> strokes_{};
    DisplayId display_id_{0};
};
} // namespace accessibility