#include <android/graphics/Insets.h>
#include <algorithm>

namespace android::graphics {

Insets::Insets(int32_t left, int32_t top, int32_t right, int32_t bottom)
    : left(left), top(top), right(right), bottom(bottom) {}

Insets Insets::of(int32_t left, int32_t top, int32_t right, int32_t bottom) {
    return Insets{left, top, right, bottom};
}

Insets Insets::ofZero() {
    return Insets{0, 0, 0, 0};
}

bool Insets::is_empty() const {
    return left == 0 && top == 0 && right == 0 && bottom == 0;
}

auto Insets::operator==(const Insets& other) const -> bool {
    return left == other.left && top == other.top &&
           right == other.right && bottom == other.bottom;
}

auto Insets::operator!=(const Insets& other) const -> bool {
    return !(*this == other);
}

auto Insets::operator+(const Insets& other) const -> Insets {
    return Insets{left + other.left, top + other.top,
                  right + other.right, bottom + other.bottom};
}

auto Insets::operator-(const Insets& other) const -> Insets {
    return Insets{left - other.left, top - other.top,
                  right - other.right, bottom - other.bottom};
}

Insets Insets::intersect(const Insets& a, const Insets& b) {
    return Insets{
        std::max(a.left, b.left),
        std::max(a.top, b.top),
        std::max(a.right, b.right),
        std::max(a.bottom, b.bottom)
    };
}

auto Insets::writeToParcel(AParcel* parcel) const -> binder_status_t {
    binder_status_t status;
    status = AParcel_writeInt32(parcel, left);
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, top);
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, right);
    if (status != STATUS_OK) return status;
    return AParcel_writeInt32(parcel, bottom);
}

auto Insets::readFromParcel(const AParcel* parcel) -> binder_status_t {
    binder_status_t status;
    status = AParcel_readInt32(parcel, &left);
    if (status != STATUS_OK) return status;
    status = AParcel_readInt32(parcel, &top);
    if (status != STATUS_OK) return status;
    status = AParcel_readInt32(parcel, &right);
    if (status != STATUS_OK) return status;
    return AParcel_readInt32(parcel, &bottom);
}

} // namespace android::graphics
