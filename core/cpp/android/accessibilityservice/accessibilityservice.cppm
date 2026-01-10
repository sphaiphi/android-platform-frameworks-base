// accessibilityservice.cppm
export module accessibilityservice;

import <memory>;
import <functional>;
import <vector>;
import <string>;
import <chrono>;
import <expected>;
import <optional>;

export import :types;
export import :input_method_session;
export import :input_method_session_wrapper;
export import :button_controller;
export import :fingerprint_gesture_controller;
export import :touch_interaction_controller;
export import :magnification_controller;
export import ndk_executor;

export namespace android::accessibilityservice {

class AccessibilityServiceImpl;

class AccessibilityService {
public:
    [[nodiscard]] auto get_executor() const -> std::shared_ptr<common::IThreadExecutor>;

    [[nodiscard]] auto get_service_info() const -> const AccessibilityServiceInfo&;

    void set_service_info(AccessibilityServiceInfo info);
    
    [[nodiscard]] auto get_fingerprint_gesture_controller() const -> std::shared_ptr<IFingerprintGestureController>;

    [[nodiscard]] auto get_touch_interaction_controller(int display_id) const -> std::shared_ptr<ITouchInteractionController>;

    [[nodiscard]] auto get_magnification_controller() const -> std::shared_ptr<IMagnificationController>;

    virtual void on_accessibility_event(const AccessibilityEvent& event) = 0;

    virtual void on_interrupt() = 0;

    virtual void on_service_connected() {} 

    virtual auto on_create_input_method_session() -> std::unique_ptr<IAccessibilityInputMethodSession> {
        return nullptr;
    }

protected:
    AccessibilityService();
    virtual ~AccessibilityService();

    AccessibilityService(const AccessibilityService&) = delete;
    AccessibilityService& operator=(const AccessibilityService&) = delete;
    AccessibilityService(AccessibilityService&&) = delete;
    AccessibilityService& operator=(AccessibilityService&&) = delete;

private:
    std::unique_ptr<AccessibilityServiceImpl> impl_;
};

// GestureDescription and StrokeDescription exports
struct PointF {
    float x = 0.0f;
    float y = 0.0f;
};

struct Path {
    std::vector<PointF> points;
};

export class StrokeDescription {
public:
    using milliseconds = std::chrono::milliseconds;

    [[nodiscard]] StrokeDescription(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued = false);

    [[nodiscard]] auto continue_stroke(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued) const
        -> std::expected<StrokeDescription, std::string>;
    
    [[nodiscard]] auto get_path() const -> const Path&;
    [[nodiscard]] auto get_start_time() const -> milliseconds;
    [[nodiscard]] auto get_duration() const -> milliseconds;
    [[nodiscard]] auto will_continue() const -> bool;

private:
    friend class GestureDescription;
    // friend class android::os::Parcel;

    struct StrokeId {
        int32_t value;
    };
    
    Path path_;
    milliseconds start_time_;
    milliseconds duration_;
    bool will_be_continued_;
    StrokeId id_;
    std::optional<StrokeId> continued_stroke_id_;
    
    StrokeDescription(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued, StrokeId continued_id);
    
    [[nodiscard]] auto get_id() const -> StrokeId;
    [[nodiscard]] auto get_continued_id() const -> std::optional<StrokeId>;
};

export class GestureDescription {
public:
    using milliseconds = std::chrono::milliseconds;

    static constexpr int32_t MAX_STROKE_COUNT = 20;
    static constexpr milliseconds MAX_GESTURE_DURATION = std::chrono::seconds(60);

    enum class BuildError {
        NO_STROKES_ADDED,
        TOO_MANY_STROKES,
        DURATION_TOO_LONG
    };

    class Builder;

    [[nodiscard]] auto get_stroke_count() const -> size_t;
    [[nodiscard]] auto get_stroke(size_t index) const -> const StrokeDescription&;
    [[nodiscard]] auto get_display_id() const -> DisplayId;

private:
    explicit GestureDescription(std::vector<StrokeDescription> strokes, DisplayId display_id);

    std::vector<StrokeDescription> strokes_;
    DisplayId display_id_;
};

export class GestureDescription::Builder {
public:
    Builder() = default;

    [[nodiscard]] auto add_stroke(this auto&& self, StrokeDescription stroke) -> decltype(auto) {
        strokes_.push_back(std::move(stroke));
        return std::forward<decltype(self)>(self);
    }
    
    [[nodiscard]] auto set_display_id(this auto&& self, DisplayId id) -> decltype(auto) {
        display_id_ = id;
        return std::forward<decltype(self)>(self);
    }

    [[nodiscard]] auto build() && -> std::expected<GestureDescription, BuildError> {
        if (strokes_.empty()) return std::unexpected(BuildError::NO_STROKES_ADDED);
        if (strokes_.size() > MAX_STROKE_COUNT) return std::unexpected(BuildError::TOO_MANY_STROKES);
        
        milliseconds max_end_time{0};
        for(const auto& stroke : strokes_) {
            const auto end_time = stroke.get_start_time() + stroke.get_duration();
            if (end_time > max_end_time) max_end_time = end_time;
        }
        
        if (max_end_time > MAX_GESTURE_DURATION) return std::unexpected(BuildError::DURATION_TOO_LONG);

        return GestureDescription{std::move(strokes_), display_id_};
    }

private:
    std::vector<StrokeDescription> strokes_{};
    DisplayId display_id_{0};
};

} // namespace android::accessibilityservice