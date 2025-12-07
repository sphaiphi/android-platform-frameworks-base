// file: gesturedescription_internal.cppm
export module android.accessibilityservice:internal;

import <vector>;
import <chrono>;
import <optional>;

// Because Parcel is a C-style API, we import it this way.
// In a real Android build, this would be via system headers.
struct AParcel;

export namespace android::os {
    // A C++ wrapper around the NDK's AParcel for RAII and type safety.
    class Parcel {
    public:
        explicit Parcel(AParcel* parcel) : parcel_(parcel) {}

        // Methods for writing data (simplified)
        void writeInt32(int32_t val);
        void writeInt64(int64_t val);
        void writeFloat(float val);
        void writeBool(bool val);
        template<typename T> void writeParcelable(const T& parcelable);
        template<typename T> void writeVector(const std::vector<T>& vec);
        
        // Methods for reading data (simplified)
        auto readInt32() -> int32_t;
        auto readInt64() -> int64_t;
        auto readFloat() -> float;
        auto readBool() -> bool;
        template<typename T> auto readParcelable() -> T;
        template<typename T> auto readVector() -> std::vector<T>;

    private:
        AParcel* parcel_;
    };
}


export namespace android::accessibilityservice::internal {
    
using namespace std::chrono_literals;

// A single touch point on the screen. Equivalent to Java's internal TouchPoint.
// This is a Parcelable type.
struct TouchPoint {
    int32_t stroke_id;
    int32_t continued_stroke_id;
    bool is_start_of_path;
    bool is_end_of_path;
    float x;
    float y;

    void writeToParcel(android::os::Parcel& parcel) const;
    static auto readFromParcel(android::os::Parcel& parcel) -> TouchPoint;
};

// Represents a snapshot of all touch points at a specific moment in time.
// Equivalent to Java's internal GestureStep. This is a Parcelable type.
struct GestureStep {
    std::chrono::milliseconds time_since_gesture_start;
    std::vector<TouchPoint> points;

    void writeToParcel(android::os::Parcel& parcel) const;
    static auto readFromParcel(android::os::Parcel& parcel) -> GestureStep;
};

} // namespace android::accessibilityservice::internal