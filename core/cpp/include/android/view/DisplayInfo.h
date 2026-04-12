#pragma once

#include <cstdint>

namespace android::view {

struct DisplayInfo {
    int32_t logicalWidth{0};
    int32_t logicalHeight{0};
    int32_t rotation{0};
};

} // namespace android::view
