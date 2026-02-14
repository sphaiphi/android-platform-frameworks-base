#pragma once

#include <android/content/ContextWrapper.h>
#include <android/content/res/Configuration.h>
#include <android/os/Bundle.h>
#include <memory>
#include <vector>

namespace android::app {

/**
 * Base class for maintaining global application state.
 */
class Application : public android::content::ContextWrapper {
public:
    Application();
    explicit Application(std::shared_ptr<android::content::Context> base);
    virtual ~Application() = default;

    /**
     * Called when the application is starting, before any activity, service, or receiver objects (excluding content providers) have been created.
     */
    virtual void on_create();

    /**
     * This method is for use in emulated process environments.
     */
    virtual void on_terminate();

    /**
     * Called by the system when the device configuration changes while your component is running.
     */
    virtual void on_configuration_changed(const android::content::res::Configuration& new_config);

    /**
     * This is called when the overall system is running low on memory.
     */
    virtual void on_low_memory();

    /**
     * Called when the operating system has determined that it is a good time for a process to trim unneeded memory from its process.
     */
    virtual void on_trim_memory(int level);

private:
    // TBD: Callback registries
};

} // namespace android::app
