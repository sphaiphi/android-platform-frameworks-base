#include <android/view/InputEvent.h>

namespace android {
namespace view {

// InputEventWrapper construction is handled inline in the header.
// This file exists for future extensibility (e.g., sequence number allocation).
static uint32_t g_next_sequence = 1;

auto allocate_sequence_number() -> uint32_t {
    return g_next_sequence++;
}

} // namespace view
} // namespace android
