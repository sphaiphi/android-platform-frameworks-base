// accessibilityservice-types.cppm
export module accessibilityservice:types;

import <string>;
import <vector>;
import <cstdint>;
import <optional>;
import <limits>;
import <chrono>;

import <binder/Parcelable.h>;
import <binder/Parcel.h>;
import <utils/Errors.h>;

export namespace android::accessibilityservice {

// All data structures must implement the Parcelable interface for IPC.
struct Parcelable {
    virtual ~Parcelable() = default;
    virtual android::status_t writeToParcel(android::Parcel* parcel) const = 0;
    virtual android::status_t readFromParcel(const android::Parcel* parcel) = 0;
};

// Placeholder for EditorInfo.
export struct EditorInfo final : public Parcelable {
    std::optional<std::string> initial_text;
    int32_t input_type{};
    
    status_t writeToParcel(android::Parcel* parcel) const override { return android::OK; }
    status_t readFromParcel(const android::Parcel* parcel) override { return android::OK; }
};

// Simplified MotionEvent for gesture support.
export struct MotionEvent final : public Parcelable {
    int32_t action{0};
    int64_t event_time_nanos{0};
    float x{0.0f};
    float y{0.0f};
    int32_t pointer_count{1};

    status_t writeToParcel(android::Parcel* parcel) const override { return android::OK; }
    status_t readFromParcel(const android::Parcel* parcel) override { return android::OK; }
};

// Strong type for event types for type safety
export enum class EventType : int32_t {
    view_clicked = 1,
    // ... (abbreviated for brevity in refactor, assume full list)
};

// Represents a UI event.
export struct AccessibilityEvent final : public Parcelable {
    EventType event_type{EventType::view_clicked};
    std::u16string package_name{};
    int64_t event_time_nanos{0};

    status_t writeToParcel(android::Parcel* parcel) const override { return android::OK; }
    status_t readFromParcel(const android::Parcel* parcel) override { return android::OK; }
};

// Describes the capabilities of the accessibility service.
export struct AccessibilityServiceInfo final : public Parcelable {
    static constexpr int32_t FEEDBACK_GENERIC = 16;
    
    std::vector<EventType> event_types{};
    std::vector<std::string> package_names{};
    int32_t feedback_type{FEEDBACK_GENERIC};
    int64_t notification_timeout_ms{0};
    int32_t flags{0};

    status_t writeToParcel(android::Parcel* parcel) const override { return android::OK; }
    status_t readFromParcel(const android::Parcel* parcel) override { return android::OK; }
};

// Describes a gesture event (e.g. touch gesture).
export struct AccessibilityGestureEvent final : public Parcelable {
    int32_t gesture_id{0};
    int32_t display_id{0};
    std::vector<MotionEvent> motion_events{};

    status_t writeToParcel(android::Parcel* parcel) const override { return android::OK; }
    status_t readFromParcel(const android::Parcel* parcel) override { return android::OK; }
};

// Configuration for screen magnification.
export struct MagnificationConfig final : public Parcelable {
    static constexpr int32_t MAGNIFICATION_MODE_FULLSCREEN = 1;
    
    int32_t mode{0};
    bool activated{false};
    float scale{std::numeric_limits<float>::quiet_NaN()};
    float center_x{std::numeric_limits<float>::quiet_NaN()};
    float center_y{std::numeric_limits<float>::quiet_NaN()};

    status_t writeToParcel(android::Parcel* parcel) const override { return android::OK; }
    status_t readFromParcel(const android::Parcel* parcel) override { return android::OK; }
};

// Internal gesture types exposed for IPC
export struct TouchPoint {
    int32_t stroke_id;
    int32_t continued_stroke_id;
    bool is_start_of_path;
    bool is_end_of_path;
    float x;
    float y;

    // Serialization methods...
};

export struct GestureStep {
    std::chrono::milliseconds time_since_gesture_start;
    std::vector<TouchPoint> points;

    // Serialization methods...
};

} // namespace android::accessibilityservice