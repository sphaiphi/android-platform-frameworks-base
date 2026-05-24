#pragma once

#include <memory>

namespace android::app {

/**
 * Interface for managing one or more Loader instances.
 */
class LoaderManager {
public:
    virtual ~LoaderManager() = default;

    virtual void do_start() = 0;
    virtual void do_stop() = 0;
    virtual void do_destroy() = 0;
};

class LoaderManagerImpl : public LoaderManager {
public:
    void do_start() override {}
    void do_stop() override {}
    void do_destroy() override {}
};

} // namespace android::app
