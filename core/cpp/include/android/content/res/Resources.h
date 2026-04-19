#pragma once

#include <android/content/res/AssetManager.h>
#include <android/content/res/Configuration.h>
#include <android/util/DisplayMetrics.h>
#include <android/util/TypedValue.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <expected_shim.h>

namespace android::content::res {

enum class ResourceError {
    NotFound,
    TypeMismatch,
    Unknown
};

class Resources {
public:
    Resources(std::shared_ptr<AssetManager> assets,
              std::shared_ptr<android::util::DisplayMetrics> metrics,
              std::shared_ptr<Configuration> config);
    
    virtual ~Resources() = default;

    auto get_string(int32_t id) -> std::expected<std::string, ResourceError>;
    auto get_dimension(int32_t id) -> std::expected<float, ResourceError>;
    
    // For manual mapping support (mocking .arsc loading)
    auto add_resource(int32_t id, const android::util::TypedValue& value) -> void;

    auto update_configuration(const Configuration& config, const android::util::DisplayMetrics& metrics) -> void;

    [[nodiscard]] auto get_configuration() const -> std::shared_ptr<Configuration> { return config_; }
    [[nodiscard]] auto get_display_metrics() const -> std::shared_ptr<android::util::DisplayMetrics> { return metrics_; }

private:
    std::shared_ptr<AssetManager> assets_;
    std::shared_ptr<android::util::DisplayMetrics> metrics_;
    std::shared_ptr<Configuration> config_;
    
    std::unordered_map<int32_t, android::util::TypedValue> resource_map_;
};

} // namespace android::content::res
