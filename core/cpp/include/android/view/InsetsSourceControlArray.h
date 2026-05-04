#pragma once

#include <android/view/InsetsSourceControl.h>
#include <vector>
#include <memory>

namespace android::view {

/**
 * Array of InsetsSourceControl objects with a sequence number.
 * Returned by IWindowSession.addToDisplay to inform the client about
 * active insets controls.
 */
struct InsetsSourceControlArray {
    std::vector<std::shared_ptr<InsetsSourceControl>> controls;
    int32_t seq{0};

    InsetsSourceControlArray() = default;
    InsetsSourceControlArray(std::vector<std::shared_ptr<InsetsSourceControl>> controls, int32_t seq);
};

} // namespace android::view
