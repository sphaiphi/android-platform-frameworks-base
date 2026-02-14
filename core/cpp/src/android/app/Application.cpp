#include <android/app/Application.h>

namespace android::app {

Application::Application() : android::content::ContextWrapper(nullptr) {}

Application::Application(std::shared_ptr<android::content::Context> base) : android::content::ContextWrapper(std::move(base)) {}

void Application::on_create() {
    // Default implementation does nothing
}

void Application::on_terminate() {
    // Default implementation does nothing
}

void Application::on_configuration_changed(const android::content::res::Configuration& /*new_config*/) {
    // Default implementation does nothing
}

void Application::on_low_memory() {
    // Default implementation does nothing
}

void Application::on_trim_memory(int /*level*/) {
    // Default implementation does nothing
}

} // namespace android::app
