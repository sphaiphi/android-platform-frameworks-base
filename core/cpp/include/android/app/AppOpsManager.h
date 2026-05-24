#pragma once

#include <string>
#include <memory>
#include <cstdint>

namespace android::app {

class IAppOpsService {
public:
    virtual ~IAppOpsService() = default;
};

/**
 * API for tracking and controlling application operations.
 */
class AppOpsManager {
public:
    static constexpr int32_t MODE_ALLOWED = 0;
    static constexpr int32_t MODE_IGNORED = 1;
    static constexpr int32_t MODE_ERRORED = 2;
    static constexpr int32_t MODE_DEFAULT = 3;

    static constexpr int32_t OP_NONE = -1;
    static constexpr int32_t OP_COARSE_LOCATION = 0;
    static constexpr int32_t OP_FINE_LOCATION = 1;
    // ... add more as needed

    AppOpsManager();
    virtual ~AppOpsManager() = default;

    /**
     * Do a quick check for whether an application might be able to perform an operation.
     */
    virtual auto check_op(int32_t op, int32_t uid, const std::string& package_name) -> int32_t;

    /**
     * Make a note of an application performing an operation.
     */
    virtual auto note_op(int32_t op, int32_t uid, const std::string& package_name, const std::string& attribution_tag, const std::string& message) -> int32_t;

    /**
     * Report that an application has started executing a long-running operation.
     */
    virtual auto start_op(int32_t op, int32_t uid, const std::string& package_name, bool attribution_chain_id, const std::string& attribution_tag, const std::string& message, int32_t attribution_flags, int32_t attribution_chain_id_int) -> int32_t;

    /**
     * Report that an application is no longer performing an operation that had previously been started with start_op.
     */
    virtual void finish_op(int32_t op, int32_t uid, const std::string& package_name, const std::string& attribution_tag);

private:
    std::shared_ptr<IAppOpsService> service_;
};

} // namespace android::app
