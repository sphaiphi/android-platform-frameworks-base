#pragma once

#include <android/view/MotionEvent.h>
#include <android/view/KeyEvent.h>
#include <variant>
#include <optional>
#include <cstdint>

namespace android {
namespace view {

/**
 * Type-safe union of input event types using std::variant.
 * Zero-cost dispatch — no virtual dispatch overhead.
 */
using InputEvent = std::variant<MotionEvent, KeyEvent>;

/**
 * Wrapper holding an InputEvent variant with a sequence number.
 * Used to track individual events for finishInputEvent().
 *
 * Uses std::optional to allow default construction and
 * clear/reset semantics for the sequential event invariant.
 */
struct InputEventWrapper {
    std::optional<InputEvent> event;
    uint32_t sequence_number;

    InputEventWrapper() : event(std::nullopt), sequence_number(0) {}
    InputEventWrapper(InputEvent ev, uint32_t seq)
        : event(std::move(ev)), sequence_number(seq) {}
};

} // namespace view
} // namespace android
