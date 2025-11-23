// accessibilityservice_internal.cppm
export module accessibilityservice:internal;

import accessibilityservice:types;
import <memory>;

// Forward declarations for Binder types
namespace android {
    class IBinder;
    class IInterface;
    template<typename INTERFACE> class BnInterface;
}

export namespace accessibility::internal {

// Client-side interface for the service to call the system.
// This is what the service uses to perform global actions, get windows, etc.
class IAccessibilityServiceConnection : public android::IInterface {
public:
    // This would contain methods like `getWindows`, `performGlobalAction`, etc.
};

// Server-side interface implemented by the accessibility service.
// The system calls methods on this interface to deliver events.
class IAccessibilityServiceClient : public android::IInterface {
public:
    virtual void onAccessibilityEvent(const AccessibilityEvent& event) = 0;
    virtual void onInterrupt() = 0;
    virtual void onServiceConnected() = 0;
};

// The Binder "server" stub that receives calls from the system.
class BnAccessibilityServiceClient : public android::BnInterface<IAccessibilityServiceClient> {
public:
    // This pure virtual function handles dispatching incoming Binder transactions.
    android::status_t onTransact(uint32_t code,
                                 const android::Parcel& data,
                                 android::Parcel* reply,
                                 uint32_t flags) override;

    // Default implementations can be provided if needed.
    void onAccessibilityEvent(const AccessibilityEvent& event) override {}
    void onInterrupt() override {}
    void onServiceConnected() override {}
};

} // namespace accessibility::internal