#include <android/app/ActivityThread.h>
#include <android/app/ContextImpl.h>
#include <iostream>

namespace android::app {

void ActivityThread::H::handle_message(const android::os::Message& msg) {
    auto thread = ActivityThread::current_activity_thread();
    if (!thread) return;

    switch (msg.what) {
        case BIND_APPLICATION:
            thread->bind_application(*static_cast<std::string*>(msg.obj));
            break;
        case LAUNCH_ACTIVITY: {
            auto r = *static_cast<std::shared_ptr<ActivityClientRecord>*>(msg.obj);
            thread->handle_launch_activity(r);
            break;
        }
        default:
            break;
    }
}

std::shared_ptr<ActivityThread> ActivityThread::s_current_activity_thread = nullptr;

ActivityThread::ActivityThread() {
    android::os::Looper::prepare_main_looper();
    h_ = std::make_shared<H>(android::os::Looper::my_looper());
    m_instrumentation = std::make_shared<Instrumentation>();
}

auto ActivityThread::system_main() -> std::shared_ptr<ActivityThread> {
    auto thread = std::make_shared<ActivityThread>();
    thread->attach(true);
    s_current_activity_thread = thread;
    return thread;
}

auto ActivityThread::current_activity_thread() -> std::shared_ptr<ActivityThread> {
    return s_current_activity_thread;
}

void ActivityThread::attach(bool system) {
    if (!system) {
        // Normal application attach
    } else {
        // System process attach
    }
}

void ActivityThread::detach() {
    s_current_activity_thread = nullptr;
}

void ActivityThread::bind_application(const std::string& package_name) {
    bound_package_name_ = package_name;
    // In a real implementation, this would load the APK, create the Context, etc.
}

void ActivityThread::handle_launch_activity(std::shared_ptr<ActivityClientRecord> r) {
    if (!r->activity) {
        r->activity = m_instrumentation->new_activity("Activity");
    }

    auto context = std::make_shared<ContextImpl>();
    context->set_package_name(bound_package_name_);
    
    r->activity->attach_base_context(context);
    r->activity->set_intent(r->intent);

    m_instrumentation->call_activity_on_create(r->activity, android::os::Bundle());
    
    m_activities[r.get()] = r;
}

void ActivityThread::handle_resume_activity(void* token, bool final_state_request, bool is_forward) {
    auto it = m_activities.find(token);
    if (it == m_activities.end()) return;

    auto r = it->second;
    if (r->activity->get_state() == ActivityState::created || r->activity->get_state() == ActivityState::stopped) {
        m_instrumentation->call_activity_on_start(r->activity);
    }
    m_instrumentation->call_activity_on_resume(r->activity);
    r->paused = false;
    r->stopped = false;
}

void ActivityThread::handle_pause_activity(void* token, bool finished, bool user_leaving, int config_changes) {
    auto it = m_activities.find(token);
    if (it == m_activities.end()) return;

    auto r = it->second;
    m_instrumentation->call_activity_on_pause(r->activity);
    r->paused = true;
}

void ActivityThread::handle_stop_activity(void* token, bool show, int config_changes) {
    auto it = m_activities.find(token);
    if (it == m_activities.end()) return;

    auto r = it->second;
    m_instrumentation->call_activity_on_stop(r->activity);
    r->stopped = true;
}

void ActivityThread::handle_destroy_activity(void* token, bool finishing, int config_changes, bool get_non_config_instance) {
    auto it = m_activities.find(token);
    if (it == m_activities.end()) return;

    auto r = it->second;
    m_instrumentation->call_activity_on_destroy(r->activity);
    m_activities.erase(it);
}

} // namespace android::app
