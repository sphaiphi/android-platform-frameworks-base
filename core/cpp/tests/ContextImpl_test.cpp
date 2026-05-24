#include <gtest/gtest.h>
#include <android/app/ContextImpl.h>
#include <android/app/SystemServiceRegistry.h>
#include <android/content/Context.h>

using namespace android::app;
using namespace android::content;

class MockServiceFetcher : public ServiceFetcher {
public:
    auto get_service(ContextImpl* /*ctx*/) -> std::expected<void*, ContextError> override {
        return reinterpret_cast<void*>(0xDEADBEEF);
    }
};

TEST(ContextImplTest, GetPackageName) {
    auto context = std::make_shared<ContextImpl>();
    context->set_package_name("com.example.app");
    EXPECT_EQ(context->get_package_name(), "com.example.app");
}

TEST(ContextImplTest, GetSystemServices) {
    auto context = std::make_shared<ContextImpl>();
    
    // Testing non-existent service
    auto result = context->get_system_service("non_existent_service");
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), ContextError::service_not_found);

    // Testing a service that SHOULD exist (e.g., "activity")
    SystemServiceRegistry::register_service("activity", std::make_unique<MockServiceFetcher>());
    
    auto activity_service = context->get_system_service("activity");
    ASSERT_TRUE(activity_service.has_value()) << "Activity service should be found";
    EXPECT_EQ(activity_service.value(), reinterpret_cast<void*>(0xDEADBEEF));
}

TEST(ContextImplTest, GetFilesDir) {
    auto context = std::make_shared<ContextImpl>();
    context->set_files_dir("/data/user/0/com.example.app/files");
    EXPECT_EQ(context->get_files_dir(), "/data/user/0/com.example.app/files");
}

TEST(ContextImplTest, GetCacheDir) {
    auto context = std::make_shared<ContextImpl>();
    context->set_cache_dir("/data/user/0/com.example.app/cache");
    EXPECT_EQ(context->get_cache_dir(), "/data/user/0/com.example.app/cache");
}
