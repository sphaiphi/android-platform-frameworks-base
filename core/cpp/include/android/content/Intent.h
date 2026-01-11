#pragma once

#include <string>
#include <optional>
#include <expected>
#include <set>
#include <memory>
#include <android/os/Bundle.h>

namespace android::content {

enum class IntentError {
    ActionNotSet,
    DataNotSet,
    TypeNotSet
};

/**
 * An intent is an abstract description of an operation to be performed.
 */
class Intent {
public:
    Intent() = default;
    explicit Intent(std::string action);
    ~Intent() = default;

    // Rule of zero/five
    Intent(const Intent&) = default;
    Intent(Intent&&) noexcept = default;
    auto operator=(const Intent&) -> Intent& = default;
    auto operator=(Intent&&) noexcept -> Intent& = default;

    /**
     * Set the general action to be performed.
     */
    auto setAction(std::string action) -> void;

    /**
     * Return the action to be performed.
     */
    [[nodiscard]] auto getAction() const -> std::expected<std::string, IntentError>;

    /**
     * Set the data this intent is operating on.
     */
    auto setData(std::string data) -> void;

    /**
     * Return the data this intent is operating on.
     */
    [[nodiscard]] auto getData() const -> std::expected<std::string, IntentError>;

    /**
     * Set an explicit MIME type for the intent data.
     */
    auto setType(std::string type) -> void;

    /**
     * Retrieve any explicit MIME type included in the intent.
     */
    [[nodiscard]] auto getType() const -> std::expected<std::string, IntentError>;

    /**
     * Add a new category to the intent.
     */
    auto addCategory(const std::string& category) -> void;

    /**
     * Remove a category from an intent.
     */
    auto removeCategory(const std::string& category) -> void;

    /**
     * Check if a category exists in the intent.
     */
    [[nodiscard]] auto hasCategory(const std::string& category) const -> bool;

    /**
     * Return the set of all categories in the intent.
     */
    [[nodiscard]] auto getCategories() const -> const std::set<std::string>&;

    /**
     * Add extended data to the intent.
     */
    auto putExtra(const std::string& key, int32_t value) -> void;

    /**
     * Add extended data to the intent.
     */
    auto putExtra(const std::string& key, std::string value) -> void;

    /**
     * Copy all extras from the given Bundle into this Intent.
     */
    auto putExtras(const android::os::Bundle& extras) -> void;
    
    /**
     * Returns true if the Intent's extras contain the given key.
     */
    [[nodiscard]] auto hasExtra(const std::string& key) const -> bool;

    /**
     * Retrieve extended data from the intent.
     */
    [[nodiscard]] auto getExtras() -> android::os::Bundle&;

    /**
     * Retrieve extended data from the intent.
     */
    [[nodiscard]] auto getExtras() const -> const android::os::Bundle&;

    /**
     * Set special flags controlling how this intent is handled.
     */
    auto setFlags(int32_t flags) -> void;

    /**
     * Add additional flags to the intent.
     */
    auto addFlags(int32_t flags) -> void;

    /**
     * Retrieve any special flags associated with this intent.
     */
    [[nodiscard]] auto getFlags() const -> int32_t;

private:
    std::optional<std::string> mAction;
    std::optional<std::string> mData;
    std::optional<std::string> mType;
    std::set<std::string> mCategories;
    android::os::Bundle mExtras;
    int32_t mFlags{0};
};

} // namespace android::content
