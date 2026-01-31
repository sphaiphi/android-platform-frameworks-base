#pragma once

#include <string>
#include <optional>
#include <expected>
#include <set>
#include <memory>
#include <android/os/Bundle.h>
#include <android/content/ComponentName.h>
#include <android/net/Uri.h>
#include <android/graphics/Rect.h>
#include <android/content/ClipData.h>
#include <android/content/Errors.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::content {

/**
 * An intent is an abstract description of an operation to be performed.
 */
class Intent {
public:
    Intent() = default;
    explicit Intent(std::string action);
    Intent(std::string action, net::Uri uri);
    ~Intent() = default;

    // Rule of zero/five
    Intent(const Intent&);
    Intent(Intent&&) noexcept;
    auto operator=(const Intent&) -> Intent&;
    auto operator=(Intent&&) noexcept -> Intent&;

    /**
     * Set the general action to be performed.
     */
    auto setAction(std::string action) -> void;

    /**
     * Return the action to be performed.
     */
    [[nodiscard]] auto getAction() const -> std::optional<std::string>;

    /**
     * Set the data this intent is operating on.
     */
    auto setData(net::Uri data) -> void;

    /**
     * Return the data this intent is operating on.
     */
    [[nodiscard]] auto getData() const -> std::optional<net::Uri>;

    /**
     * Set an explicit MIME type for the intent data.
     */
    auto setType(std::string type) -> void;

    /**
     * Retrieve any explicit MIME type included in the intent.
     */
    [[nodiscard]] auto getType() const -> std::optional<std::string>;

    /**
     * Set both data and type.
     */
    auto setDataAndType(net::Uri data, std::string type) -> void;

    /**
     * Set the identifier for this intent.
     */
    auto setIdentifier(std::string identifier) -> void;

    /**
     * Return the identifier for this intent.
     */
    [[nodiscard]] auto getIdentifier() const -> std::optional<std::string>;

    /**
     * Set an explicit application package name that limits the components this Intent will resolve to.
     */
    auto setPackage(std::string package) -> void;

    /**
     * Retrieve the application package name this Intent is limited to.
     */
    [[nodiscard]] auto getPackage() const -> std::optional<std::string>;

    /**
     * Set the concrete component name to use for the intent.
     */
    auto setComponent(ComponentName component) -> void;

    /**
     * Retrieve the concrete component associated with the intent.
     */
    [[nodiscard]] auto getComponent() const -> std::optional<ComponentName>;

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

    /**
     * Set the visual bounds of the source of this intent.
     */
    auto setSourceBounds(graphics::Rect bounds) -> void;

    /**
     * Retrieve the visual bounds of the source of this intent.
     */
    [[nodiscard]] auto getSourceBounds() const -> std::optional<graphics::Rect>;

    /**
     * Set the ClipData associated with this intent.
     */
    auto setClipData(ClipData clipData) -> void;

    /**
     * Retrieve the ClipData associated with this intent.
     */
    [[nodiscard]] auto getClipData() const -> std::optional<ClipData>;

    /**
     * Set the selector intent.
     */
    auto setSelector(std::shared_ptr<Intent> selector) -> void;

    /**
     * Retrieve the selector intent.
     */
    [[nodiscard]] auto getSelector() const -> std::shared_ptr<Intent>;

    /**
     * Determine if two intents are the same for the purposes of intent resolution (filtering).
     */
    [[nodiscard]] auto filterEquals(const Intent& other) const -> bool;

    // NDK Binder Parceling
    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;

private:
    std::optional<std::string> mAction;
    std::optional<net::Uri> mData;
    std::optional<std::string> mType;
    std::optional<std::string> mIdentifier;
    std::optional<std::string> mPackage;
    std::optional<ComponentName> mComponent;
    std::set<std::string> mCategories;
    android::os::Bundle mExtras;
    int32_t mFlags{0};
    int32_t mExtendedFlags{0};
    int32_t mContentUserHint{-2}; // UserHandle.USER_CURRENT
    std::optional<graphics::Rect> mSourceBounds;
    std::optional<ClipData> mClipData;
    std::shared_ptr<Intent> mSelector;
    std::shared_ptr<Intent> mOriginalIntent;
};

} // namespace android::content