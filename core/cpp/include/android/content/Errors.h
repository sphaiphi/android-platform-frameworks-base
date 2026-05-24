#pragma once

#include <cstdint>

namespace android::content {

enum class IntentError : int32_t {
    None = 0,
    InvalidAction,
    InvalidUri,
    InvalidComponent,
    MalformedData,
    MissingExtra,
    TypeMismatch,
    ParcelingError,
};

enum class ComponentNameError : int32_t {
    None = 0,
    InvalidPackage,
    InvalidClass,
    MalformedString,
    ParcelingError,
};

} // namespace android::content

namespace android::net {

enum class UriError : int32_t {
    None = 0,
    MalformedUri,
    UnsupportedScheme,
    InvalidPath,
    ParcelingError,
};

} // namespace android::net
