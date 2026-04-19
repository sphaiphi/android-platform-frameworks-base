#include <gtest/gtest.h>
#include <android/content/res/AssetManager.h>
#include <filesystem>
#include <fstream>

using namespace android::content::res;
namespace fs = std::filesystem;

class AssetManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_assets_dir = fs::temp_directory_path() / "test_assets";
        fs::create_directories(test_assets_dir);
        
        // Create a dummy asset file
        test_file_path = test_assets_dir / "hello.txt";
        std::ofstream ofs(test_file_path);
        ofs << "Hello, Assets!";
        ofs.close();
    }

    void TearDown() override {
        fs::remove_all(test_assets_dir);
    }

    fs::path test_assets_dir;
    fs::path test_file_path;
    AssetManager asset_manager;
};

TEST_F(AssetManagerTest, OpenNonExistentFile) {
    auto result = asset_manager.open("non_existent.txt");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), AssetError::FileNotFound);
}

TEST_F(AssetManagerTest, OpenExistentFile) {
    // Note: AssetManager might need a "root" or similar to know where assets are.
    // For now, let's assume it can take absolute paths or we'll need to set a base.
    auto result = asset_manager.open(test_file_path.string());
    ASSERT_TRUE(result.has_value());
    
    std::string content(result.value().begin(), result.value().end());
    EXPECT_EQ(content, "Hello, Assets!");
}
