#pragma once

#include <memory>
#include <vector>

namespace android::content {
class Context;
}

namespace android::app {

class Application;

class ActivityThreadInternal {
public:
    virtual ~ActivityThreadInternal() = default;
    
    virtual auto get_system_context() -> std::shared_ptr<android::content::Context> = 0;
    virtual auto get_application() -> std::shared_ptr<Application> = 0;
    virtual auto is_in_density_compat_mode() -> bool = 0;
};

} // namespace android::app
