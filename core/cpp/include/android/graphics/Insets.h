#pragma once

#include <cstdint>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::graphics {

class Insets {
public:
    int32_t left{0};
    int32_t top{0};
    int32_t right{0};
    int32_t bottom{0};

    Insets() = default;
    Insets(int32_t left, int32_t top, int32_t right, int32_t bottom);

    static Insets of(int32_t left, int32_t top, int32_t right, int32_t bottom);
    static Insets ofZero();

    [[nodiscard]] bool is_empty() const;

    auto operator==(const Insets& other) const -> bool;
    auto operator!=(const Insets& other) const -> bool;

    auto operator+(const Insets& other) const -> Insets;
    auto operator-(const Insets& other) const -> Insets;

    static Insets intersect(const Insets& a, const Insets& b);

    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;
};

} // namespace android::graphics
