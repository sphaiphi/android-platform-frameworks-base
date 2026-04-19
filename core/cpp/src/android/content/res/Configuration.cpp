#include <android/content/res/Configuration.h>

namespace android::content::res {

auto Configuration::set_to_defaults() -> void {
    font_scale = 1.0f;
    mcc = 0;
    mnc = 0;
    orientation = ORIENTATION_UNDEFINED;
    ui_mode = UI_MODE_TYPE_UNDEFINED | UI_MODE_NIGHT_UNDEFINED;
    screen_width_dp = 0;
    screen_height_dp = 0;
}

auto Configuration::update_from(const Configuration& delta) -> uint32_t {
    uint32_t changed = 0;
    if (delta.font_scale != font_scale && delta.font_scale != 0) {
        font_scale = delta.font_scale;
    }
    if (delta.mcc != 0 && delta.mcc != mcc) {
        mcc = delta.mcc;
        changed |= CONFIG_MCC;
    }
    if (delta.mnc != 0 && delta.mnc != mnc) {
        mnc = delta.mnc;
        changed |= CONFIG_MNC;
    }
    if (delta.orientation != ORIENTATION_UNDEFINED && delta.orientation != orientation) {
        orientation = delta.orientation;
        changed |= CONFIG_ORIENTATION;
    }
    if (delta.ui_mode != (UI_MODE_TYPE_UNDEFINED | UI_MODE_NIGHT_UNDEFINED) && delta.ui_mode != ui_mode) {
        ui_mode = delta.ui_mode;
        changed |= CONFIG_UI_MODE;
    }
    if (delta.screen_width_dp != 0 && delta.screen_width_dp != screen_width_dp) {
        screen_width_dp = delta.screen_width_dp;
        changed |= CONFIG_SCREEN_SIZE;
    }
    if (delta.screen_height_dp != 0 && delta.screen_height_dp != screen_height_dp) {
        screen_height_dp = delta.screen_height_dp;
        changed |= CONFIG_SCREEN_SIZE;
    }
    return changed;
}

auto Configuration::diff(const Configuration& delta) const -> uint32_t {
    uint32_t changed = 0;
    if (delta.mcc != 0 && delta.mcc != mcc) changed |= CONFIG_MCC;
    if (delta.mnc != 0 && delta.mnc != mnc) changed |= CONFIG_MNC;
    if (delta.orientation != ORIENTATION_UNDEFINED && delta.orientation != orientation) changed |= CONFIG_ORIENTATION;
    if (delta.ui_mode != (UI_MODE_TYPE_UNDEFINED | UI_MODE_NIGHT_UNDEFINED) && delta.ui_mode != ui_mode) changed |= CONFIG_UI_MODE;
    if (delta.screen_width_dp != 0 && delta.screen_width_dp != screen_width_dp) changed |= CONFIG_SCREEN_SIZE;
    if (delta.screen_height_dp != 0 && delta.screen_height_dp != screen_height_dp) changed |= CONFIG_SCREEN_SIZE;
    return changed;
}

auto Configuration::operator==(const Configuration& other) const -> bool {
    return font_scale == other.font_scale &&
           mcc == other.mcc &&
           mnc == other.mnc &&
           orientation == other.orientation &&
           ui_mode == other.ui_mode &&
           screen_width_dp == other.screen_width_dp &&
           screen_height_dp == other.screen_height_dp;
}

} // namespace android::content::res
