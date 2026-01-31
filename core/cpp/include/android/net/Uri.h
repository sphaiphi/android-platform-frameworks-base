#pragma once

#include <string>
#include <vector>
#include <optional>
#include <expected>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::net {

/**
 * Immutable URI reference.
 */
class Uri {
public:
    class Builder {
    public:
        auto scheme(std::string scheme) -> Builder&;
        auto opaquePart(std::string opaquePart) -> Builder&;
        auto authority(std::string authority) -> Builder&;
        auto path(std::string path) -> Builder&;
        auto appendPath(const std::string& newSegment) -> Builder&;
        auto query(std::string query) -> Builder&;
        auto appendQueryParameter(const std::string& key, const std::string& value) -> Builder&;
        auto fragment(std::string fragment) -> Builder&;
        auto build() -> Uri;

    private:
        friend class Uri;
        std::optional<std::string> mScheme;
        std::optional<std::string> mOpaquePart;
        std::optional<std::string> mAuthority;
        std::optional<std::string> mPath;
        std::optional<std::string> mQuery;
        std::optional<std::string> mFragment;
    };

    Uri() = default;
    ~Uri() = default;
    Uri(const Uri&) = default;
    Uri(Uri&&) noexcept = default;
    auto operator=(const Uri&) -> Uri& = default;
    auto operator=(Uri&&) noexcept -> Uri& = default;

    static auto parse(const std::string& uriString) -> Uri;

    [[nodiscard]] auto getScheme() const -> std::optional<std::string>;
    [[nodiscard]] auto getSchemeSpecificPart() const -> std::string;
    [[nodiscard]] auto getEncodedSchemeSpecificPart() const -> std::string;
    [[nodiscard]] auto getAuthority() const -> std::optional<std::string>;
    [[nodiscard]] auto getEncodedAuthority() const -> std::optional<std::string>;
    [[nodiscard]] auto getPath() const -> std::optional<std::string>;
    [[nodiscard]] auto getEncodedPath() const -> std::optional<std::string>;
    [[nodiscard]] auto getQuery() const -> std::optional<std::string>;
    [[nodiscard]] auto getEncodedQuery() const -> std::optional<std::string>;
    [[nodiscard]] auto getFragment() const -> std::optional<std::string>;
    [[nodiscard]] auto getEncodedFragment() const -> std::optional<std::string>;

    [[nodiscard]] auto isHierarchical() const -> bool;
    [[nodiscard]] auto isOpaque() const -> bool;
    [[nodiscard]] auto isRelative() const -> bool;
    [[nodiscard]] auto isAbsolute() const -> bool;

    [[nodiscard]] auto toString() const -> std::string;
    [[nodiscard]] auto buildUpon() const -> Builder;

    auto operator==(const Uri& other) const -> bool;
    auto operator<(const Uri& other) const -> bool;

    // NDK Binder Parceling
    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;

private:
    Uri(Builder builder);

    std::optional<std::string> mScheme;
    std::optional<std::string> mOpaquePart;
    std::optional<std::string> mAuthority;
    std::optional<std::string> mPath;
    std::optional<std::string> mQuery;
    std::optional<std::string> mFragment;

    mutable std::optional<std::string> mCachedString;

    static constexpr int NULL_TYPE_ID = 0;
    static constexpr int STRING_TYPE_ID = 1;
};

} // namespace android::net
