#include <android/view/Surface.h>

namespace android::view {

Surface::Surface(void* native_handle) : native_handle_(native_handle) {}

bool Surface::is_valid() const {
    return native_handle_ != nullptr;
}

} // namespace android::view
