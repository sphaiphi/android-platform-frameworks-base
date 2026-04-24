#include <android/content/res/Resources.h>
#include <android/content/res/AssetManager.h>
#include <android/content/res/Configuration.h>
#include <android/util/DisplayMetrics.h>
#include <android/util/TypedValue.h>
#include <iostream>
#include <memory>

int main() {
    auto assets = std::make_shared<android::content::res::AssetManager>();
    auto metrics = std::make_shared<android::util::DisplayMetrics>();
    metrics->density = 2.0f; // xhdpi
    auto config = std::make_shared<android::content::res::Configuration>();
    
    android::content::res::Resources res(assets, metrics, config);
    // Map a string resource
    android::util::TypedValue tv_str;
    tv_str.type = android::util::TypedValue::TYPE_STRING;
    tv_str.string_value = "Phase 4 Success";
    res.add_resource(0x7f010001, tv_str);
    // Map a dimension resource (12dp)
    android::util::TypedValue tv_dim;
    tv_dim.type = android::util::TypedValue::TYPE_DIMENSION;
    tv_dim.data = (12 << android::util::TypedValue::COMPLEX_MANTISSA_SHIFT) | 
                  (android::util::TypedValue::COMPLEX_UNIT_DP << android::util::TypedValue::COMPLEX_UNIT_SHIFT);
    res.add_resource(0x7f020001, tv_dim);
    // Verify resolution
    auto s = res.get_string(0x7f010001);
    std::cout << "Resources: String resolved = " << (s.has_value() ? s.value() : "ERROR") << std::endl;
    if (!s.has_value() || s.value() != "Phase 4 Success") return 1;
    auto d = res.get_dimension(0x7f020001);
    std::cout << "Resources: Dimension resolved = " << (d.has_value() ? std::to_string(d.value()) : "ERROR") << "px" << std::endl;
    if (!d.has_value() || d.value() != 24.0f) return 2;
    std::cout << "SUCCESS: Resource Resolution Engine verification complete." << std::endl;
    return 0;
}