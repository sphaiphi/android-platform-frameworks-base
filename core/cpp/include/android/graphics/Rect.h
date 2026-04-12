#pragma once

#include <cstdint>
#include <string>
#include <expected_shim.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::graphics {

/**
 * Rect holds four integer coordinates for a rectangle.
 */
class Rect {
public:
    int32_t left{0};
    int32_t top{0};
    int32_t right{0};
    int32_t bottom{0};

    Rect() = default;
    Rect(int32_t left, int32_t top, int32_t right, int32_t bottom);
    Rect(const Rect& other) = default;

    auto set(int32_t left, int32_t top, int32_t right, int32_t bottom) -> void;
    auto set(const Rect& src) -> void;
    auto setEmpty() -> void;

    [[nodiscard]] auto width() const -> int32_t;
    [[nodiscard]] auto height() const -> int32_t;
    [[nodiscard]] auto centerX() const -> int32_t;
    [[nodiscard]] auto centerY() const -> int32_t;
    [[nodiscard]] auto exactCenterX() const -> float;
    [[nodiscard]] auto exactCenterY() const -> float;

    [[nodiscard]] auto isEmpty() const -> bool;
    [[nodiscard]] auto contains(int32_t x, int32_t y) const -> bool;
    [[nodiscard]] auto contains(int32_t left, int32_t top, int32_t right, int32_t bottom) const -> bool;
    [[nodiscard]] auto contains(const Rect& r) const -> bool;

    auto offset(int32_t dx, int32_t dy) -> void;
    auto offsetTo(int32_t newLeft, int32_t newTop) -> void;
    auto inset(int32_t dx, int32_t dy) -> void;
    auto inset(int32_t left, int32_t top, int32_t right, int32_t bottom) -> void;

    auto intersect(int32_t left, int32_t top, int32_t right, int32_t bottom) -> bool;
    auto intersect(const Rect& r) -> bool;
    auto setIntersect(const Rect& a, const Rect& b) -> bool;
    auto intersects(int32_t left, int32_t top, int32_t right, int32_t bottom) const -> bool;
    static auto intersects(const Rect& a, const Rect& b) -> bool;

    auto union_with(int32_t left, int32_t top, int32_t right, int32_t bottom) -> void;
    auto union_with(const Rect& r) -> void;
    auto union_with(int32_t x, int32_t y) -> void;

    auto sort() -> void;

    [[nodiscard]] auto flattenToString() const -> std::string;
    static auto unflattenFromString(const std::string& str) -> std::expected<Rect, std::string>;

    auto operator==(const Rect& other) const -> bool;
    auto operator!=(const Rect& other) const -> bool;

    // NDK Binder Parceling
    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;
};

} // namespace android::graphics
