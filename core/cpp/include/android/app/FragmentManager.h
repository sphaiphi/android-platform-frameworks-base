#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>

namespace android::app {

class Fragment;

/**
 * Interface for interacting with Fragment objects inside an Activity.
 */
class FragmentManager {
public:
    virtual ~FragmentManager() = default;

    virtual auto find_fragment_by_tag(const std::string& tag) -> std::shared_ptr<Fragment> = 0;
    // virtual auto begin_transaction() -> std::shared_ptr<FragmentTransaction> = 0;
};

class FragmentManagerImpl : public FragmentManager {
public:
    auto find_fragment_by_tag(const std::string& tag) -> std::shared_ptr<Fragment> override {
        for (const auto& fragment : fragments_) {
            if (fragment->get_tag() == tag) {
                return fragment;
            }
        }
        return nullptr;
    }

    auto add_fragment(std::shared_ptr<Fragment> fragment) -> void {
        fragments_.push_back(std::move(fragment));
    }

private:
    std::vector<std::shared_ptr<Fragment>> fragments_;
};

} // namespace android::app
