// file: gesturedescription_internal.cpp
module android.accessibilityservice:internal;

// This is where the Parcel methods would be defined.
// Since we don't have the real NDK AParcel here, this is a mock implementation.
// In a real build, this would link against libbinder_ndk.so
namespace android::os {
    void Parcel::writeInt32(int32_t val) { /* AParcel_writeInt32(parcel_, val); */ }
    void Parcel::writeInt64(int64_t val) { /* AParcel_writeInt64(parcel_, val); */ }
    // ... other mock implementations ...
}


namespace android::accessibilityservice::internal {

//--- TouchPoint Parcelable Implementation ---//
void TouchPoint::writeToParcel(android::os::Parcel& parcel) const {
    parcel.writeInt32(stroke_id);
    parcel.writeInt32(continued_stroke_id);
    parcel.writeBool(is_start_of_path);
    parcel.writeBool(is_end_of_path);
    parcel.writeFloat(x);
    parcel.writeFloat(y);
}

auto TouchPoint::readFromParcel(android::os::Parcel& parcel) -> TouchPoint {
    return TouchPoint {
        .stroke_id = parcel.readInt32(),
        .continued_stroke_id = parcel.readInt32(),
        .is_start_of_path = parcel.readBool(),
        .is_end_of_path = parcel.readBool(),
        .x = parcel.readFloat(),
        .y = parcel.readFloat(),
    };
}

//--- GestureStep Parcelable Implementation ---//
void GestureStep::writeToParcel(android::os::Parcel& parcel) const {
    parcel.writeInt64(time_since_gesture_start.count());
    // In a real implementation, you would write the size and then each element.
    // parcel.writeVector(points); 
}

auto GestureStep::readFromParcel(android::os::Parcel& parcel) -> GestureStep {
    GestureStep step;
    step.time_since_gesture_start = std::chrono::milliseconds(parcel.readInt64());
    // step.points = parcel.readVector<TouchPoint>();
    return step;
}

} // namespace android::accessibilityservice::internal