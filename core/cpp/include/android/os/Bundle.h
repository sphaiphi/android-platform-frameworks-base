#pragma once

#include <string>
#include <map>
#include <variant>
#include <expected_shim.h>
#include <vector>
#include <memory>

namespace android::os {

enum class BundleError {
    KeyNotFound,
    TypeMismatch,
    InternalError
};

/**
 * A mapping from String keys to various Value types.
 */
class Bundle {
public:
    using Value = std::variant<
        int32_t,
        int64_t,
        double,
        bool,
        std::string,
        std::vector<std::string>,
        std::shared_ptr<Bundle>
    >;

    Bundle() = default;
    ~Bundle() = default;

    // Rule of zero
    Bundle(const Bundle&) = default;
    Bundle(Bundle&&) noexcept = default;
    auto operator=(const Bundle&) -> Bundle& = default;
    auto operator=(Bundle&&) noexcept -> Bundle& = default;

    /**
     * Inserts an int value into the mapping of this Bundle.
     */
    auto putInt(const std::string& key, int32_t value) -> void;

    /**
     * Inserts a long value into the mapping of this Bundle.
     */
    auto putLong(const std::string& key, int64_t value) -> void;

    /**
     * Inserts a double value into the mapping of this Bundle.
     */
    auto putDouble(const std::string& key, double value) -> void;

    /**
     * Inserts a boolean value into the mapping of this Bundle.
     */
    auto putBoolean(const std::string& key, bool value) -> void;

    /**
     * Inserts a string value into the mapping of this Bundle.
     */
    auto putString(const std::string& key, std::string value) -> void;

    /**
     * Inserts a string array value into the mapping of this Bundle.
     */
    auto putStringArray(const std::string& key, std::vector<std::string> value) -> void;

    /**
     * Inserts a Bundle value into the mapping of this Bundle.
     */
    auto putBundle(const std::string& key, std::shared_ptr<Bundle> value) -> void;

    /**
     * Returns the value associated with the given key, or a BundleError if
     * no mapping of the desired type exists for the given key.
     */
    [[nodiscard]] auto getInt(const std::string& key) const -> std::expected<int32_t, BundleError>;
    [[nodiscard]] auto getLong(const std::string& key) const -> std::expected<int64_t, BundleError>;
    [[nodiscard]] auto getDouble(const std::string& key) const -> std::expected<double, BundleError>;
    [[nodiscard]] auto getBoolean(const std::string& key) const -> std::expected<bool, BundleError>;
    [[nodiscard]] auto getString(const std::string& key) const -> std::expected<std::string, BundleError>;
    [[nodiscard]] auto getStringArray(const std::string& key) const -> std::expected<std::vector<std::string>, BundleError>;
    [[nodiscard]] auto getBundle(const std::string& key) const -> std::expected<std::shared_ptr<Bundle>, BundleError>;

    /**
     * Returns true if the given key is contained in the mapping of this Bundle.
     */
    [[nodiscard]] auto containsKey(const std::string& key) const -> bool;

    /**
     * Returns the number of mappings contained in this Bundle.
     */
    [[nodiscard]] auto size() const -> size_t;

    /**
     * Returns true if the mapping of this Bundle is empty.
     */
    [[nodiscard]] auto isEmpty() const -> bool;

    /**
     * Removes all elements from the mapping of this Bundle.
     */
    auto clear() -> void;

    /**
     * Removes any entry with the given key from the mapping of this Bundle.
     */
    auto remove(const std::string& key) -> void;

private:
    template<typename T>
    [[nodiscard]] auto get(const std::string& key) const -> std::expected<T, BundleError>;

    std::map<std::string, Value> mData;
};

} // namespace android::os