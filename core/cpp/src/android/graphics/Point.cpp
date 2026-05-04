#include <android/graphics/Point.h>

namespace android::graphics {

Point::Point(int32_t x, int32_t y) : x(x), y(y) {}

auto Point::set(int32_t x, int32_t y) -> void {
    this->x = x;
    this->y = y;
}

auto Point::operator==(const Point& other) const -> bool {
    return x == other.x && y == other.y;
}

auto Point::operator!=(const Point& other) const -> bool {
    return !(*this == other);
}

auto Point::writeToParcel(AParcel* parcel) const -> binder_status_t {
    binder_status_t status;
    status = AParcel_writeInt32(parcel, x);
    if (status != STATUS_OK) return status;
    return AParcel_writeInt32(parcel, y);
}

auto Point::readFromParcel(const AParcel* parcel) -> binder_status_t {
    binder_status_t status;
    status = AParcel_readInt32(parcel, &x);
    if (status != STATUS_OK) return status;
    return AParcel_readInt32(parcel, &y);
}

} // namespace android::graphics
