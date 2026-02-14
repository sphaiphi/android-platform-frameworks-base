#pragma once

#include <string>
#include <cstdint>

namespace android::app {

/**
 * Represents an App Operation note event that occurred asynchronously.
 */
class AsyncNotedAppOp {
public:
    AsyncNotedAppOp(int32_t opCode, int32_t notingUid, const std::string& attributionTag, const std::string& message, int64_t time)
        : op_code_(opCode), noting_uid_(notingUid), attribution_tag_(attributionTag), message_(message), time_(time) {}

    [[nodiscard]] auto get_op_code() const noexcept -> int32_t { return op_code_; }
    [[nodiscard]] auto get_noting_uid() const noexcept -> int32_t { return noting_uid_; }
    [[nodiscard]] auto get_attribution_tag() const -> const std::string& { return attribution_tag_; }
    [[nodiscard]] auto get_message() const -> const std::string& { return message_; }
    [[nodiscard]] auto get_time() const noexcept -> int64_t { return time_; }

private:
    int32_t op_code_;
    int32_t noting_uid_;
    std::string attribution_tag_;
    std::string message_;
    int64_t time_;
};

} // namespace android::app
