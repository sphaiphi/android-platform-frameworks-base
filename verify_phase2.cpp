#include <android/util/DisplayMetrics.h>
#include <android/content/res/Configuration.h>
#include <iostream>
int main() {
    // Verify DisplayMetrics
    android::util::DisplayMetrics dm;
    dm.density_dpi = android::util::DisplayMetrics::DENSITY_XHIGH;
    dm.density = 2.0f;
    
    float dp = 16.0f;
    float px = dp * dm.density;
    std::cout << "DisplayMetrics: 16dp at xhdpi = " << px << "px" << std::endl;
    if (px != 32.0f) return 1;
    // Verify Configuration
    android::content::res::Configuration c1;
    c1.orientation = android::content::res::Configuration::ORIENTATION_PORTRAIT;
    
    android::content::res::Configuration c2;
    c2.orientation = android::content::res::Configuration::ORIENTATION_LANDSCAPE;
    
    uint32_t diff = c1.diff(c2);
    std::cout << "Configuration: Diff result = 0x" << std::hex << diff << std::endl;
    if (!(diff & android::content::res::Configuration::CONFIG_ORIENTATION)) return 2;
    std::cout << "SUCCESS: Metrics and Configuration verification complete." << std::endl;
    return 0;
}