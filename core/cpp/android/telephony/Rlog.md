# Rlog - Reverse Engineering Documentation

## Executive Summary
`Rlog` is a specialized logging utility for the Android Radio/Telephony stack. It directs logs to the `LOG_ID_RADIO` buffer (viewable via `logcat -b radio`) and provides utilities for PII (Personally Identifiable Information) redaction.

## Detailed Functionality

### 1. Radio Logging
*   Wraps `android.util.Log.println_native` passing `Log.LOG_ID_RADIO`.
*   Provides standard levels: `v`, `d`, `i`, `w`, `e`.

### 2. PII Redaction (`pii`)
*   **Purpose**: Prevents sensitive user data (phone numbers, IMSI, etc.) from leaking into logs on production builds.
*   **Logic**:
    *   If Build is **User** (`Build.IS_USER`): Returns a secure hash of the input string.
    *   If input is null/empty or `Log.VERBOSE` is enabled for the tag: Returns the original string.
*   **Hashing**: Uses SHA-1 encoded in Base64 (URL safe, no padding).
    *   User builds return `"****"` effectively unless explicit PII logging is enabled in logic (though the code primarily checks `USER_BUILD`). Wait, the code says: `if (USER_BUILD) return "****";` inside `secureHash`. This means on User builds, it *always* returns stars, not the hash. The hash is calculated only if NOT user build (e.g., userdebug/eng) but PII logging is requested?
    *   *Correction based on code review*: `pii()` calls `secureHash()`. `secureHash()` returns `"****"` immediately if `USER_BUILD` is true. Otherwise (userdebug/eng), it returns the SHA-1 hash.

## Java-to-C++ Translation Guide
*   **Logging**: Use `__android_log_buf_write` with `LOG_ID_RADIO`.
*   **PII**: Implement the logic:
    *   Check build type (ro.build.type).
    *   If user build, return redacted string.
    *   If debug build, compute SHA-1 + Base64. OpenSSL or BoringSSL is usually available in Android native.

## Implementation Risks
*   **Performance**: SHA-1 calculation on every log line can be expensive. Ensure `pii` is only called when necessary.
*   **Security**: Ensure the hashing algorithm matches exactly if log correlation between Java and C++ components is required.
