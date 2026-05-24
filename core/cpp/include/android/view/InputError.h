#pragma once

namespace android {
namespace view {

/**
 * Error codes for InputEventReceiver operations.
 */
enum class InputError {
    NO_EVENT_IN_PROGRESS,     ///< finishInputEvent called without a current event
    DISPOSED,                 ///< Operation attempted on a disposed receiver
    TYPE_MISMATCH,            ///< Event type mismatch in finishInputEvent
    SOCKET_READ_ERROR,        ///< Error reading from input channel socket
    SOCKET_WRITE_ERROR,       ///< Error writing to input channel socket
    INVALID_CHANNEL,          ///< InputChannel is not valid
    WIRE_FORMAT_ERROR,        ///< Malformed wire protocol data
};

} // namespace view
} // namespace android
