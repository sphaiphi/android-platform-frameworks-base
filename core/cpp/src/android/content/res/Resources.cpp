#include <android/content/res/Resources.h>

namespace android::content::res {

Resources::Resources(std::shared_ptr<AssetManager> assets,
                   std::shared_ptr<android::util::DisplayMetrics> metrics,
                   std::shared_ptr<Configuration> config)
    : assets_(std::move(assets)),
      metrics_(std::move(metrics)),
      config_(std::move(config)) {}

auto Resources::get_string(int32_t id) -> std::expected<std::string, ResourceError> {
    auto it = resource_map_.find(id);
    if (it == resource_map_.end()) {
        return std::unexpected(ResourceError::NotFound);
    }
    
    if (it->second.type != android::util::TypedValue::TYPE_STRING) {
        return std::unexpected(ResourceError::TypeMismatch);
    }
    
    return it->second.string_value;
}

auto Resources::get_dimension(int32_t id) -> std::expected<float, ResourceError> {
    auto it = resource_map_.find(id);
    if (it == resource_map_.end()) {
        return std::unexpected(ResourceError::NotFound);
    }
    
    if (it->second.type != android::util::TypedValue::TYPE_DIMENSION) {
        return std::unexpected(ResourceError::TypeMismatch);
    }
    
    return android::util::TypedValue::complex_to_dimension(it->second.data, *metrics_);
}

auto Resources::add_resource(int32_t id, const android::util::TypedValue& value) -> void {
    resource_map_[id] = value;
}

auto Resources::update_configuration(const Configuration& config, const android::util::DisplayMetrics& metrics) -> void {
    *config_ = config;
    *metrics_ = metrics;
}

} // namespace android::content::res
