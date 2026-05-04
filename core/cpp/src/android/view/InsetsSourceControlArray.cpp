#include <android/view/InsetsSourceControlArray.h>

namespace android::view {

InsetsSourceControlArray::InsetsSourceControlArray(
        std::vector<std::shared_ptr<InsetsSourceControl>> controls, int32_t seq)
    : controls(std::move(controls)), seq(seq) {}

} // namespace android::view
