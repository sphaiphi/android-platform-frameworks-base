#pragma once

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::graphics {

class Point {
public:
    int32_t x{0};
    int32_t y{0};

    Point() = default;
    Point(int32_t x, int32_t y);

    auto set(int32_t x, int32_t y) -> void;

    auto operator==(const Point& other) const -> bool;
    auto operator!=(const Point& other) const -> bool;

    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;
};

} // namespace android::graphics
