#pragma once

#include <cstdint>

namespace android::content::res {

class Configuration {
public:
    static constexpr int32_t ORIENTATION_UNDEFINED = 0;
    static constexpr int32_t ORIENTATION_PORTRAIT = 1;
    static constexpr int32_t ORIENTATION_LANDSCAPE = 2;

    static constexpr int32_t UI_MODE_TYPE_MASK = 0x0f;
    static constexpr int32_t UI_MODE_TYPE_UNDEFINED = 0x00;
    static constexpr int32_t UI_MODE_TYPE_NORMAL = 0x01;
    static constexpr int32_t UI_MODE_NIGHT_MASK = 0x30;
    static constexpr int32_t UI_MODE_NIGHT_UNDEFINED = 0x00;
    static constexpr int32_t UI_MODE_NIGHT_NO = 0x10;
    static constexpr int32_t UI_MODE_NIGHT_YES = 0x20;

    static constexpr uint32_t CONFIG_MCC = 0x0001;
    static constexpr uint32_t CONFIG_MNC = 0x0002;
    static constexpr uint32_t CONFIG_ORIENTATION = 0x0080;
    static constexpr uint32_t CONFIG_UI_MODE = 0x0200;
    static constexpr uint32_t CONFIG_SCREEN_SIZE = 0x0400;

    float font_scale{1.0f};
    int32_t mcc{0};
    int32_t mnc{0};
    int32_t orientation{ORIENTATION_UNDEFINED};
    int32_t ui_mode{UI_MODE_TYPE_UNDEFINED | UI_MODE_NIGHT_UNDEFINED};
    int32_t screen_width_dp{0};
    int32_t screen_height_dp{0};

    Configuration() = default;

    auto set_to_defaults() -> void;
    auto update_from(const Configuration& delta) -> uint32_t;
    auto diff(const Configuration& delta) const -> uint32_t;
    
    auto operator==(const Configuration& other) const -> bool;
};

} // namespace android::content::res
