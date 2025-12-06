// accessibilityservice_types.cppm
export module accessibilityservice:accessibilityservice_types;

import <string>;
import <vector>;
import <cstdint>;

import <binder/Parcelable.h>;
import <binder/Parcel.h>;
import <utils/Errors.h>;

// Placeholder for EditorInfo. A real implementation would have all fields
// from the Java counterpart and implement Parcelable correctly.
export struct EditorInfo final : public android::Parcelable {
    status_t writeToParcel(android::Parcel* parcel) const override {
        // In a real implementation, all members would be written to the parcel.
        return android::OK;
    }

    status_t readFromParcel(const android::Parcel* parcel) override {
        // In a real implementation, all members would be read from the parcel.
        return android::OK;
    }
};

export namespace android::accessibilityservice {

// Strong type for event types for type safety
enum class EventType : int32_t {
    view_clicked = 1,
    view_focused = 8,
    view_text_changed = 16,
    window_state_changed = 32,
    notification_state_changed = 64,
    // ... other event types
};

// All data structures must implement the Parcelable interface for IPC.
struct Parcelable {
    virtual ~Parcelable() = default;
    virtual android::status_t writeToParcel(android::Parcel* parcel) const = 0;
    virtual android::status_t readFromParcel(const android::Parcel* parcel) = 0;
};

// Represents a UI event.
// All members are initialized to safe defaults.
export struct AccessibilityEvent : public Parcelable {
    EventType event_type{EventType::view_clicked};
    std::u16string package_name{};
    int64_t event_time_nanos{0};

    // Rule of Zero: Compiler-generated special members are sufficient.

    android::status_t writeToParcel(android::Parcel* parcel) const override;
    android::status_t readFromParcel(const android::Parcel* parcel) override;
};

// Describes the capabilities of the accessibility service.
export struct AccessibilityServiceInfo : public Parcelable {
    std::vector<EventType> event_types{};
    std::vector<std::u16string> package_names{};
    int32_t feedback_type{0}; // Use a strong enum in a real implementation
    int32_t flags{0};

    // Rule of Zero is sufficient here as well.

    android::status_t writeToParcel(android::Parcel* parcel) const override;
    android::status_t readFromParcel(const android::Parcel* parcel) override;
};

} // namespace accessibility

