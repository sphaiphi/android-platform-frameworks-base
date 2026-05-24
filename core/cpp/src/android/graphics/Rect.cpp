#include <android/graphics/Rect.h>
#include <algorithm>
#include <sstream>

namespace android::graphics {

Rect::Rect(int32_t left, int32_t top, int32_t right, int32_t bottom)
    : left(left), top(top), right(right), bottom(bottom) {}

auto Rect::set(int32_t left, int32_t top, int32_t right, int32_t bottom) -> void {
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}

auto Rect::set(const Rect& src) -> void {
    this->left = src.left;
    this->top = src.top;
    this->right = src.right;
    this->bottom = src.bottom;
}

auto Rect::setEmpty() -> void {
    left = top = right = bottom = 0;
}

auto Rect::width() const -> int32_t {
    return right - left;
}

auto Rect::height() const -> int32_t {
    return bottom - top;
}

auto Rect::centerX() const -> int32_t {
    return (left + right) >> 1;
}

auto Rect::centerY() const -> int32_t {
    return (top + bottom) >> 1;
}

auto Rect::exactCenterX() const -> float {
    return (left + right) * 0.5f;
}

auto Rect::exactCenterY() const -> float {
    return (top + bottom) * 0.5f;
}

auto Rect::isEmpty() const -> bool {
    return left >= right || top >= bottom;
}

auto Rect::contains(int32_t x, int32_t y) const -> bool {
    return left < right && top < bottom  // check for empty first
           && x >= left && x < right && y >= top && y < bottom;
}

auto Rect::contains(int32_t left, int32_t top, int32_t right, int32_t bottom) const -> bool {
    // check for empty first
    return this->left < this->right && this->top < this->bottom
           // now check for containment
           && this->left <= left && this->top <= top
           && this->right >= right && this->bottom >= bottom;
}

auto Rect::contains(const Rect& r) const -> bool {
    // check for empty first
    return this->left < this->right && this->top < this->bottom
           // now check for containment
           && left <= r.left && top <= r.top
           && right >= r.right && bottom >= r.bottom;
}

auto Rect::offset(int32_t dx, int32_t dy) -> void {
    left += dx;
    top += dy;
    right += dx;
    bottom += dy;
}

auto Rect::offsetTo(int32_t newLeft, int32_t newTop) -> void {
    right += newLeft - left;
    bottom += newTop - top;
    left = newLeft;
    top = newTop;
}

auto Rect::inset(int32_t dx, int32_t dy) -> void {
    left += dx;
    top += dy;
    right -= dx;
    bottom -= dy;
}

auto Rect::inset(int32_t left, int32_t top, int32_t right, int32_t bottom) -> void {
    this->left += left;
    this->top += top;
    this->right -= right;
    this->bottom -= bottom;
}

auto Rect::intersect(int32_t left, int32_t top, int32_t right, int32_t bottom) -> bool {
    if (this->left < right && left < this->right && this->top < bottom && top < this->bottom) {
        if (this->left < left) this->left = left;
        if (this->top < top) this->top = top;
        if (this->right > right) this->right = right;
        if (this->bottom > bottom) this->bottom = bottom;
        return true;
    }
    return false;
}

auto Rect::intersect(const Rect& r) -> bool {
    return intersect(r.left, r.top, r.right, r.bottom);
}

auto Rect::setIntersect(const Rect& a, const Rect& b) -> bool {
    if (a.left < b.right && b.left < a.right && a.top < b.bottom && b.top < a.bottom) {
        left = std::max(a.left, b.left);
        top = std::max(a.top, b.top);
        right = std::min(a.right, b.right);
        bottom = std::min(a.bottom, b.bottom);
        return true;
    }
    return false;
}

auto Rect::intersects(int32_t left, int32_t top, int32_t right, int32_t bottom) const -> bool {
    return this->left < right && left < this->right && this->top < bottom && top < this->bottom;
}

auto Rect::intersects(const Rect& a, const Rect& b) -> bool {
    return a.left < b.right && b.left < a.right && a.top < b.bottom && b.top < a.bottom;
}

auto Rect::union_with(int32_t left, int32_t top, int32_t right, int32_t bottom) -> void {
    if ((left < right) && (top < bottom)) {
        if ((this->left < this->right) && (this->top < this->bottom)) {
            if (this->left > left) this->left = left;
            if (this->top > top) this->top = top;
            if (this->right < right) this->right = right;
            if (this->bottom < bottom) this->bottom = bottom;
        } else {
            this->left = left;
            this->top = top;
            this->right = right;
            this->bottom = bottom;
        }
    }
}

auto Rect::union_with(const Rect& r) -> void {
    union_with(r.left, r.top, r.right, r.bottom);
}

auto Rect::union_with(int32_t x, int32_t y) -> void {
    union_with(x, y, x + 1, y + 1);
}

auto Rect::sort() -> void {
    if (left > right) {
        std::swap(left, right);
    }
    if (top > bottom) {
        std::swap(top, bottom);
    }
}

auto Rect::flattenToString() const -> std::string {
    std::stringstream ss;
    ss << left << " " << top << " " << right << " " << bottom;
    return ss.str();
}

auto Rect::unflattenFromString(const std::string& str) -> std::expected<Rect, std::string> {
    std::stringstream ss(str);
    int32_t l, t, r, b;
    if (ss >> l >> t >> r >> b) {
        return Rect(l, t, r, b);
    }
    return std::unexpected("Malformed Rect string");
}

auto Rect::operator==(const Rect& other) const -> bool {
    return left == other.left && top == other.top && right == other.right && bottom == other.bottom;
}

auto Rect::operator!=(const Rect& other) const -> bool {
    return !(*this == other);
}

auto Rect::writeToParcel(AParcel* parcel) const -> binder_status_t {
    binder_status_t status = AParcel_writeInt32(parcel, left);
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, top);
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, right);
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, bottom);
    return status;
}

auto Rect::readFromParcel(const AParcel* parcel) -> binder_status_t {
    binder_status_t status = AParcel_readInt32(parcel, &left);
    if (status != STATUS_OK) return status;
    status = AParcel_readInt32(parcel, &top);
    if (status != STATUS_OK) return status;
    status = AParcel_readInt32(parcel, &right);
    if (status != STATUS_OK) return status;
    status = AParcel_readInt32(parcel, &bottom);
    return status;
}

} // namespace android::graphics
