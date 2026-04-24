#include <android/content/res/AssetManager.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

int main() {    
    std::cout << "Diagnostic: sizeof(std::expected<std::vector<uint8_t>, android::content::res::AssetError>) = "
               << sizeof(std::expected<std::vector<uint8_t>, android::content::res::AssetError>) << std::endl;
               
    android::content::res::AssetManager am;
    auto result = am.open("verify_asset.txt");
    if (result.has_value()) {
        std::string content(result.value().begin(), result.value().end());
        std::cout << "SUCCESS: " << content << std::endl;
        return 0;
    } else {
        std::cerr << "FAILURE: Could not read asset. Error code: " << (int)result.error() << std::endl;
        return 1;
    }
}
