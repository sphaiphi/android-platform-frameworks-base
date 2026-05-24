#include <android/util/DisplayMetrics.h>

namespace android::util {

auto DisplayMetrics::set_to_defaults() -> void {
    width_pixels = 0;
    height_pixels = 0;
    density = static_cast<float>(DENSITY_DEFAULT) / static_cast<float>(DENSITY_MEDIUM);
    density_dpi = DENSITY_DEFAULT;
    scaled_density = density;
    xdpi = static_cast<float>(DENSITY_DEFAULT);
    ydpi = static_cast<float>(DENSITY_DEFAULT);
}

} // namespace android::util
