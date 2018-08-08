#include "glfw.h"

VALUE rb_mGLFW;
VALUE rb_eGLFWError;


// TODO: Window class, internal loop timing to reduce overhead 

void Init_glfw(void) {

    rb_mGLFW = rb_define_module("GLFW");
    rb_eGLFWError = rb_define_class_under(rb_mGLFW, "GLFWError", rb_eStandardError);

    Init_glfw_window(rb_mGLFW);
    Init_glfw_monitor(rb_mGLFW);
    Init_glfw_vidmode(rb_mGLFW);
    Init_glfw_image(rb_mGLFW);
    Init_glfw_cursor(rb_mGLFW);

    // GLFW Module Functions
    rb_define_singleton_method(rb_mGLFW, "init", rb_glfw_init, 0);
    rb_define_singleton_method(rb_mGLFW, "terminate", rb_glfw_terminate, 0);
    rb_define_singleton_method(rb_mGLFW, "poll_events", rb_glfw_poll_events, 0);
    rb_define_singleton_method(rb_mGLFW, "wait_events", rb_glfw_wait_events, 0);
    rb_define_singleton_method(rb_mGLFW, "post_empty_event", rb_glfw_post_empty, 0);
    rb_define_singleton_method(rb_mGLFW, "swap_interval", rb_glfw_swap_interval, 1);
    rb_define_singleton_method(rb_mGLFW, "current_context", rb_glfw_current_context, 0);
    rb_define_singleton_method(rb_mGLFW, "supported?", rb_glfw_supported_p, 1);
    rb_define_singleton_method(rb_mGLFW, "time", rb_glfw_get_time, 0);
    rb_define_singleton_method(rb_mGLFW, "time=", rb_glfw_set_time, 1);
    rb_define_singleton_method(rb_mGLFW, "monitors", rb_glfw_monitors, 0);
    rb_define_singleton_method(rb_mGLFW, "load_default_hints", rb_glfw_load_default_hints, 0);
    rb_define_singleton_method(rb_mGLFW, "hint", rb_glfw_window_hint, 2);
    rb_define_singleton_method(rb_mGLFW, "key_name", rb_glfw_key_name, 2);
    rb_define_singleton_method(rb_mGLFW, "vulkan_support?", rb_glfw_vulkan_p, 0);
    rb_define_singleton_method(rb_mGLFW, "timer_frequency", rb_glfw_timer_frequency, 0);
    rb_define_singleton_method(rb_mGLFW, "timer_value", rb_glfw_timer_value, 0);
    rb_define_singleton_method(rb_mGLFW, "monitor_changed", rb_glfw_monitor_changed, 2);

    // Set Callbacks
    glfwSetErrorCallback(rb_glfw_error_callback);
    glfwSetMonitorCallback(rb_glfw_monitor_callback);

    // API Version 
    rb_define_const(rb_mGLFW, "API_VERSION", rb_sprintf("%d.%d.%d", 
         INT2NUM(GLFW_VERSION_MAJOR),  INT2NUM(GLFW_VERSION_MINOR),  INT2NUM(GLFW_VERSION_REVISION)));
    rb_define_const(rb_mGLFW, "API_VERSION_MAJOR", INT2NUM(GLFW_VERSION_MAJOR));
    rb_define_const(rb_mGLFW, "API_VERSION_MINOR", INT2NUM(GLFW_VERSION_MINOR));
    rb_define_const(rb_mGLFW, "API_VERSION_REVISION", INT2NUM(GLFW_VERSION_REVISION));
    rb_define_const(rb_mGLFW, "API_DESCRIPTION", rb_str_new_cstr(glfwGetVersionString()));
    // Callback Types
    rb_define_const(rb_mGLFW, "CB_MOVED", INT2NUM(GLFW_RB_MOVED));
    rb_define_const(rb_mGLFW, "CB_RESIZED", INT2NUM(GLFW_RB_RESIZED));
    rb_define_const(rb_mGLFW, "CB_FRAMEBUFFER_RESIZED", INT2NUM(GLFW_RB_FRAMEBUFFER_RESIZED));
    rb_define_const(rb_mGLFW, "CB_CLOSING", INT2NUM(GLFW_RB_CLOSING));
    rb_define_const(rb_mGLFW, "CB_REFRESHED", INT2NUM(GLFW_RB_REFRESHED));
    rb_define_const(rb_mGLFW, "CB_FOCUS_CHANGED", INT2NUM(GLFW_RB_FOCUS_CHANGED));
    rb_define_const(rb_mGLFW, "CB_MINIMIZE_CHANGED", INT2NUM(GLFW_RB_MINIMIZE_CHANGED));
    rb_define_const(rb_mGLFW, "CB_MOUSE_MOVE", INT2NUM(GLFW_RB_MOUSE_MOVE));
    rb_define_const(rb_mGLFW, "CB_MOUSE_SCROLL", INT2NUM(GLFW_RB_MOUSE_SCROLL));
    rb_define_const(rb_mGLFW, "CB_MOUSE_BUTTON", INT2NUM(GLFW_RB_MOUSE_BUTTON));
    rb_define_const(rb_mGLFW, "CB_MOUSE_ENTER", INT2NUM(GLFW_RB_MOUSE_ENTER));
    rb_define_const(rb_mGLFW, "CB_KEY", INT2NUM(GLFW_RB_KEY));
    rb_define_const(rb_mGLFW, "CB_CHAR", INT2NUM(GLFW_RB_CHAR));
    rb_define_const(rb_mGLFW, "CB_CHAR_MODS", INT2NUM(GLFW_RB_CHAR_MODS));
    rb_define_const(rb_mGLFW, "CB_FILE_DROP", INT2NUM(GLFW_RB_FILE_DROP));
    rb_define_const(rb_mGLFW, "CB_MONITOR", INT2NUM(GLFW_RB_MONITOR));
    rb_define_const(rb_mGLFW, "CB_JOYSTICK", INT2NUM(GLFW_RB_JOYSTICK));
    // Input Modes
    rb_define_const(rb_mGLFW, "INPUT_PRESS", INT2NUM(GLFW_PRESS));
    rb_define_const(rb_mGLFW, "INPUT_RELEASE", INT2NUM(GLFW_RELEASE));
    rb_define_const(rb_mGLFW, "INPUT_REPEAT", INT2NUM(GLFW_REPEAT));
    // Hints
    rb_define_const(rb_mGLFW, "HINT_RESIZABLE", INT2NUM(GLFW_RESIZABLE));
    rb_define_const(rb_mGLFW, "HINT_VISIBLE", INT2NUM(GLFW_VISIBLE));
    rb_define_const(rb_mGLFW, "HINT_DECORATED", INT2NUM(GLFW_DECORATED));
    rb_define_const(rb_mGLFW, "HINT_FOCUSED", INT2NUM(GLFW_FOCUSED));
    rb_define_const(rb_mGLFW, "HINT_AUTO_ICONIFY", INT2NUM(GLFW_AUTO_ICONIFY));
    rb_define_const(rb_mGLFW, "HINT_FLOATING", INT2NUM(GLFW_FLOATING));
    rb_define_const(rb_mGLFW, "HINT_MAXIMIZED", INT2NUM(GLFW_MAXIMIZED));
    rb_define_const(rb_mGLFW, "HINT_RED_BITS", INT2NUM(GLFW_RED_BITS));
    rb_define_const(rb_mGLFW, "HINT_GREEN_BITS", INT2NUM(GLFW_GREEN_BITS));
    rb_define_const(rb_mGLFW, "HINT_BLUE_BITS", INT2NUM(GLFW_BLUE_BITS));
    rb_define_const(rb_mGLFW, "HINT_ALPHA_BITS", INT2NUM(GLFW_ALPHA_BITS));
    rb_define_const(rb_mGLFW, "HINT_DEPTH_BITS", INT2NUM(GLFW_DEPTH_BITS));
    rb_define_const(rb_mGLFW, "HINT_STENCIL_BITS", INT2NUM(GLFW_STENCIL_BITS));
    rb_define_const(rb_mGLFW, "HINT_ACCUM_RED_BITS", INT2NUM(GLFW_ACCUM_RED_BITS));
    rb_define_const(rb_mGLFW, "HINT_ACCUM_GREEN_BITS", INT2NUM(GLFW_ACCUM_GREEN_BITS));
    rb_define_const(rb_mGLFW, "HINT_ACCUM_BLUE_BITS", INT2NUM(GLFW_ACCUM_BLUE_BITS));
    rb_define_const(rb_mGLFW, "HINT_ACCUM_ALPHA_BITS", INT2NUM(GLFW_ACCUM_ALPHA_BITS));
    rb_define_const(rb_mGLFW, "HINT_AUX_BUFFERS", INT2NUM(GLFW_AUX_BUFFERS));
    rb_define_const(rb_mGLFW, "HINT_SAMPLES", INT2NUM(GLFW_SAMPLES));
    rb_define_const(rb_mGLFW, "HINT_REFRESH_RATE", INT2NUM(GLFW_REFRESH_RATE));
    rb_define_const(rb_mGLFW, "HINT_STEREO", INT2NUM(GLFW_STEREO));
    rb_define_const(rb_mGLFW, "HINT_SRGB_CAPABLE", INT2NUM(GLFW_SRGB_CAPABLE));
    rb_define_const(rb_mGLFW, "HINT_DOUBLEBUFFER", INT2NUM(GLFW_DOUBLEBUFFER));
    rb_define_const(rb_mGLFW, "HINT_CLIENT_API", INT2NUM(GLFW_CLIENT_API));
    rb_define_const(rb_mGLFW, "HINT_CONTEXT_CREATION_API", INT2NUM(GLFW_CONTEXT_CREATION_API));
    rb_define_const(rb_mGLFW, "HINT_CONTEXT_VERSION_MAJOR", INT2NUM(GLFW_CONTEXT_VERSION_MAJOR));
    rb_define_const(rb_mGLFW, "HINT_CONTEXT_VERSION_MINOR", INT2NUM(GLFW_CONTEXT_VERSION_MINOR));
    rb_define_const(rb_mGLFW, "HINT_CONTEXT_ROBUSTNESS", INT2NUM(GLFW_CONTEXT_ROBUSTNESS));
    rb_define_const(rb_mGLFW, "HINT_CONTEXT_RELEASE_BEHAVIOR", INT2NUM(GLFW_CONTEXT_RELEASE_BEHAVIOR));
    rb_define_const(rb_mGLFW, "HINT_OPENGL_FORWARD_COMPAT", INT2NUM(GLFW_OPENGL_FORWARD_COMPAT));
    rb_define_const(rb_mGLFW, "HINT_OPENGL_DEBUG_CONTEXT", INT2NUM(GLFW_OPENGL_DEBUG_CONTEXT));
    rb_define_const(rb_mGLFW, "HINT_OPENGL_PROFILE", INT2NUM(GLFW_OPENGL_PROFILE));
    // API
    rb_define_const(rb_mGLFW, "API_OPENGL", INT2NUM(GLFW_OPENGL_API));
    rb_define_const(rb_mGLFW, "API_OPENGL_ES", INT2NUM(GLFW_OPENGL_ES_API));
    rb_define_const(rb_mGLFW, "API_NONE", INT2NUM(GLFW_NO_API));
    // Context
    rb_define_const(rb_mGLFW, "CONTEXT_NATIVE", INT2NUM(GLFW_NATIVE_CONTEXT_API));
    rb_define_const(rb_mGLFW, "CONTEXT_EGL", INT2NUM(GLFW_EGL_CONTEXT_API));
    // Robustness
    rb_define_const(rb_mGLFW, "ROBUSTNESS_NONE", INT2NUM(GLFW_NO_ROBUSTNESS));
    rb_define_const(rb_mGLFW, "ROBUSTNESS_NO_NOTIFICATION", INT2NUM(GLFW_NO_RESET_NOTIFICATION));
    rb_define_const(rb_mGLFW, "ROBUSTNESS_LOSE_CONTEXT", INT2NUM(GLFW_LOSE_CONTEXT_ON_RESET));
    // Release Behavior
    rb_define_const(rb_mGLFW, "RELEASE_BEHAVIOR_ANY", INT2NUM(GLFW_ANY_RELEASE_BEHAVIOR));
    rb_define_const(rb_mGLFW, "RELEASE_BEHAVIOR_FLUSH", INT2NUM(GLFW_RELEASE_BEHAVIOR_FLUSH));
    rb_define_const(rb_mGLFW, "RELEASE_BEHAVIOR_NONE", INT2NUM(GLFW_RELEASE_BEHAVIOR_NONE));
    // OpenGL Profile
    rb_define_const(rb_mGLFW, "PROFILE_ANY", INT2NUM(GLFW_OPENGL_ANY_PROFILE));
    rb_define_const(rb_mGLFW, "PROFILE_COMPAT", INT2NUM(GLFW_OPENGL_COMPAT_PROFILE));
    rb_define_const(rb_mGLFW, "PROFILE_CORE", INT2NUM(GLFW_OPENGL_CORE_PROFILE));

    // Keys
    rb_define_const(rb_mGLFW, "KEY_UNKNOWN", INT2NUM(GLFW_KEY_UNKNOWN));
    rb_define_const(rb_mGLFW, "KEY_SPACE", INT2NUM(GLFW_KEY_SPACE));
    rb_define_const(rb_mGLFW, "KEY_APOSTROPHE", INT2NUM(GLFW_KEY_APOSTROPHE));
    rb_define_const(rb_mGLFW, "KEY_COMMA", INT2NUM(GLFW_KEY_COMMA));
    rb_define_const(rb_mGLFW, "KEY_MINUS", INT2NUM(GLFW_KEY_MINUS));
    rb_define_const(rb_mGLFW, "KEY_PERIOD", INT2NUM(GLFW_KEY_PERIOD));
    rb_define_const(rb_mGLFW, "KEY_SLASH", INT2NUM(GLFW_KEY_SLASH));
    rb_define_const(rb_mGLFW, "KEY_0", INT2NUM(GLFW_KEY_0));
    rb_define_const(rb_mGLFW, "KEY_1", INT2NUM(GLFW_KEY_1));
    rb_define_const(rb_mGLFW, "KEY_2", INT2NUM(GLFW_KEY_2));
    rb_define_const(rb_mGLFW, "KEY_3", INT2NUM(GLFW_KEY_3));
    rb_define_const(rb_mGLFW, "KEY_4", INT2NUM(GLFW_KEY_4));
    rb_define_const(rb_mGLFW, "KEY_5", INT2NUM(GLFW_KEY_5));
    rb_define_const(rb_mGLFW, "KEY_6", INT2NUM(GLFW_KEY_6));
    rb_define_const(rb_mGLFW, "KEY_7", INT2NUM(GLFW_KEY_7));
    rb_define_const(rb_mGLFW, "KEY_8", INT2NUM(GLFW_KEY_8));
    rb_define_const(rb_mGLFW, "KEY_9", INT2NUM(GLFW_KEY_9));
    rb_define_const(rb_mGLFW, "KEY_SEMICOLON", INT2NUM(GLFW_KEY_SEMICOLON));
    rb_define_const(rb_mGLFW, "KEY_EQUAL", INT2NUM(GLFW_KEY_EQUAL));
    rb_define_const(rb_mGLFW, "KEY_A", INT2NUM(GLFW_KEY_A));
    rb_define_const(rb_mGLFW, "KEY_B", INT2NUM(GLFW_KEY_B));
    rb_define_const(rb_mGLFW, "KEY_C", INT2NUM(GLFW_KEY_C));
    rb_define_const(rb_mGLFW, "KEY_D", INT2NUM(GLFW_KEY_D));
    rb_define_const(rb_mGLFW, "KEY_E", INT2NUM(GLFW_KEY_E));
    rb_define_const(rb_mGLFW, "KEY_F", INT2NUM(GLFW_KEY_F));
    rb_define_const(rb_mGLFW, "KEY_G", INT2NUM(GLFW_KEY_G));
    rb_define_const(rb_mGLFW, "KEY_H", INT2NUM(GLFW_KEY_H));
    rb_define_const(rb_mGLFW, "KEY_I", INT2NUM(GLFW_KEY_I));
    rb_define_const(rb_mGLFW, "KEY_J", INT2NUM(GLFW_KEY_J));
    rb_define_const(rb_mGLFW, "KEY_K", INT2NUM(GLFW_KEY_K));
    rb_define_const(rb_mGLFW, "KEY_L", INT2NUM(GLFW_KEY_L));
    rb_define_const(rb_mGLFW, "KEY_M", INT2NUM(GLFW_KEY_M));
    rb_define_const(rb_mGLFW, "KEY_N", INT2NUM(GLFW_KEY_N));
    rb_define_const(rb_mGLFW, "KEY_O", INT2NUM(GLFW_KEY_O));
    rb_define_const(rb_mGLFW, "KEY_P", INT2NUM(GLFW_KEY_P));
    rb_define_const(rb_mGLFW, "KEY_Q", INT2NUM(GLFW_KEY_Q));
    rb_define_const(rb_mGLFW, "KEY_R", INT2NUM(GLFW_KEY_R));
    rb_define_const(rb_mGLFW, "KEY_S", INT2NUM(GLFW_KEY_S));
    rb_define_const(rb_mGLFW, "KEY_T", INT2NUM(GLFW_KEY_T));
    rb_define_const(rb_mGLFW, "KEY_U", INT2NUM(GLFW_KEY_U));
    rb_define_const(rb_mGLFW, "KEY_V", INT2NUM(GLFW_KEY_V));
    rb_define_const(rb_mGLFW, "KEY_W", INT2NUM(GLFW_KEY_W));
    rb_define_const(rb_mGLFW, "KEY_X", INT2NUM(GLFW_KEY_X));
    rb_define_const(rb_mGLFW, "KEY_Y", INT2NUM(GLFW_KEY_Y));
    rb_define_const(rb_mGLFW, "KEY_Z", INT2NUM(GLFW_KEY_Z));
    rb_define_const(rb_mGLFW, "KEY_LEFT_BRACKET", INT2NUM(GLFW_KEY_LEFT_BRACKET));
    rb_define_const(rb_mGLFW, "KEY_BACKSLASH", INT2NUM(GLFW_KEY_BACKSLASH));
    rb_define_const(rb_mGLFW, "KEY_RIGHT_BRACKET", INT2NUM(GLFW_KEY_RIGHT_BRACKET));
    rb_define_const(rb_mGLFW, "KEY_GRAVE_ACCENT", INT2NUM(GLFW_KEY_GRAVE_ACCENT));
    rb_define_const(rb_mGLFW, "KEY_WORLD_1", INT2NUM(GLFW_KEY_WORLD_1));
    rb_define_const(rb_mGLFW, "KEY_WORLD_2", INT2NUM(GLFW_KEY_WORLD_2));
    rb_define_const(rb_mGLFW, "KEY_ESCAPE", INT2NUM(GLFW_KEY_ESCAPE));
    rb_define_const(rb_mGLFW, "KEY_ENTER", INT2NUM(GLFW_KEY_ENTER));
    rb_define_const(rb_mGLFW, "KEY_TAB", INT2NUM(GLFW_KEY_TAB));
    rb_define_const(rb_mGLFW, "KEY_BACKSPACE", INT2NUM(GLFW_KEY_BACKSPACE));
    rb_define_const(rb_mGLFW, "KEY_INSERT", INT2NUM(GLFW_KEY_INSERT));
    rb_define_const(rb_mGLFW, "KEY_DELETE", INT2NUM(GLFW_KEY_DELETE));
    rb_define_const(rb_mGLFW, "KEY_RIGHT", INT2NUM(GLFW_KEY_RIGHT));
    rb_define_const(rb_mGLFW, "KEY_LEFT", INT2NUM(GLFW_KEY_LEFT));
    rb_define_const(rb_mGLFW, "KEY_DOWN", INT2NUM(GLFW_KEY_DOWN));
    rb_define_const(rb_mGLFW, "KEY_UP", INT2NUM(GLFW_KEY_UP));
    rb_define_const(rb_mGLFW, "KEY_PAGE_UP", INT2NUM(GLFW_KEY_PAGE_UP));
    rb_define_const(rb_mGLFW, "KEY_PAGE_DOWN", INT2NUM(GLFW_KEY_PAGE_DOWN));
    rb_define_const(rb_mGLFW, "KEY_HOME", INT2NUM(GLFW_KEY_HOME));
    rb_define_const(rb_mGLFW, "KEY_END", INT2NUM(GLFW_KEY_END));
    rb_define_const(rb_mGLFW, "KEY_CAPS_LOCK", INT2NUM(GLFW_KEY_CAPS_LOCK));
    rb_define_const(rb_mGLFW, "KEY_SCROLL_LOCK", INT2NUM(GLFW_KEY_SCROLL_LOCK));
    rb_define_const(rb_mGLFW, "KEY_NUM_LOCK", INT2NUM(GLFW_KEY_NUM_LOCK));
    rb_define_const(rb_mGLFW, "KEY_PRINT_SCREEN", INT2NUM(GLFW_KEY_PRINT_SCREEN));
    rb_define_const(rb_mGLFW, "KEY_PAUSE", INT2NUM(GLFW_KEY_PAUSE));
    rb_define_const(rb_mGLFW, "KEY_F1", INT2NUM(GLFW_KEY_F1));
    rb_define_const(rb_mGLFW, "KEY_F2", INT2NUM(GLFW_KEY_F2));
    rb_define_const(rb_mGLFW, "KEY_F3", INT2NUM(GLFW_KEY_F3));
    rb_define_const(rb_mGLFW, "KEY_F4", INT2NUM(GLFW_KEY_F4));
    rb_define_const(rb_mGLFW, "KEY_F5", INT2NUM(GLFW_KEY_F5));
    rb_define_const(rb_mGLFW, "KEY_F6", INT2NUM(GLFW_KEY_F6));
    rb_define_const(rb_mGLFW, "KEY_F7", INT2NUM(GLFW_KEY_F7));
    rb_define_const(rb_mGLFW, "KEY_F8", INT2NUM(GLFW_KEY_F8));
    rb_define_const(rb_mGLFW, "KEY_F9", INT2NUM(GLFW_KEY_F9));
    rb_define_const(rb_mGLFW, "KEY_F10", INT2NUM(GLFW_KEY_F10));
    rb_define_const(rb_mGLFW, "KEY_F11", INT2NUM(GLFW_KEY_F11));
    rb_define_const(rb_mGLFW, "KEY_F12", INT2NUM(GLFW_KEY_F12));
    rb_define_const(rb_mGLFW, "KEY_F13", INT2NUM(GLFW_KEY_F13));
    rb_define_const(rb_mGLFW, "KEY_F14", INT2NUM(GLFW_KEY_F14));
    rb_define_const(rb_mGLFW, "KEY_F15", INT2NUM(GLFW_KEY_F15));
    rb_define_const(rb_mGLFW, "KEY_F16", INT2NUM(GLFW_KEY_F16));
    rb_define_const(rb_mGLFW, "KEY_F17", INT2NUM(GLFW_KEY_F17));
    rb_define_const(rb_mGLFW, "KEY_F18", INT2NUM(GLFW_KEY_F18));
    rb_define_const(rb_mGLFW, "KEY_F19", INT2NUM(GLFW_KEY_F19));
    rb_define_const(rb_mGLFW, "KEY_F20", INT2NUM(GLFW_KEY_F20));
    rb_define_const(rb_mGLFW, "KEY_F21", INT2NUM(GLFW_KEY_F21));
    rb_define_const(rb_mGLFW, "KEY_F22", INT2NUM(GLFW_KEY_F22));
    rb_define_const(rb_mGLFW, "KEY_F23", INT2NUM(GLFW_KEY_F23));
    rb_define_const(rb_mGLFW, "KEY_F24", INT2NUM(GLFW_KEY_F24));
    rb_define_const(rb_mGLFW, "KEY_F25", INT2NUM(GLFW_KEY_F25));
    rb_define_const(rb_mGLFW, "KEY_KP_0", INT2NUM(GLFW_KEY_KP_0));
    rb_define_const(rb_mGLFW, "KEY_KP_1", INT2NUM(GLFW_KEY_KP_1));
    rb_define_const(rb_mGLFW, "KEY_KP_2", INT2NUM(GLFW_KEY_KP_2));
    rb_define_const(rb_mGLFW, "KEY_KP_3", INT2NUM(GLFW_KEY_KP_3));
    rb_define_const(rb_mGLFW, "KEY_KP_4", INT2NUM(GLFW_KEY_KP_4));
    rb_define_const(rb_mGLFW, "KEY_KP_5", INT2NUM(GLFW_KEY_KP_5));
    rb_define_const(rb_mGLFW, "KEY_KP_6", INT2NUM(GLFW_KEY_KP_6));
    rb_define_const(rb_mGLFW, "KEY_KP_7", INT2NUM(GLFW_KEY_KP_7));
    rb_define_const(rb_mGLFW, "KEY_KP_8", INT2NUM(GLFW_KEY_KP_8));
    rb_define_const(rb_mGLFW, "KEY_KP_9", INT2NUM(GLFW_KEY_KP_9));
    rb_define_const(rb_mGLFW, "KEY_KP_DECIMAL", INT2NUM(GLFW_KEY_KP_DECIMAL));
    rb_define_const(rb_mGLFW, "KEY_KP_DIVIDE", INT2NUM(GLFW_KEY_KP_DIVIDE));
    rb_define_const(rb_mGLFW, "KEY_KP_MULTIPLY", INT2NUM(GLFW_KEY_KP_MULTIPLY));
    rb_define_const(rb_mGLFW, "KEY_KP_SUBTRACT", INT2NUM(GLFW_KEY_KP_SUBTRACT));
    rb_define_const(rb_mGLFW, "KEY_KP_ADD", INT2NUM(GLFW_KEY_KP_ADD));
    rb_define_const(rb_mGLFW, "KEY_KP_ENTER", INT2NUM(GLFW_KEY_KP_ENTER));
    rb_define_const(rb_mGLFW, "KEY_KP_EQUAL", INT2NUM(GLFW_KEY_KP_EQUAL));
    rb_define_const(rb_mGLFW, "KEY_LEFT_SHIFT", INT2NUM(GLFW_KEY_LEFT_SHIFT));
    rb_define_const(rb_mGLFW, "KEY_LEFT_CONTROL", INT2NUM(GLFW_KEY_LEFT_CONTROL));
    rb_define_const(rb_mGLFW, "KEY_LEFT_ALT", INT2NUM(GLFW_KEY_LEFT_ALT));
    rb_define_const(rb_mGLFW, "KEY_LEFT_SUPER", INT2NUM(GLFW_KEY_LEFT_SUPER));
    rb_define_const(rb_mGLFW, "KEY_RIGHT_SHIFT", INT2NUM(GLFW_KEY_RIGHT_SHIFT));
    rb_define_const(rb_mGLFW, "KEY_RIGHT_CONTROL", INT2NUM(GLFW_KEY_RIGHT_CONTROL));
    rb_define_const(rb_mGLFW, "KEY_RIGHT_ALT", INT2NUM(GLFW_KEY_RIGHT_ALT));
    rb_define_const(rb_mGLFW, "KEY_RIGHT_SUPER", INT2NUM(GLFW_KEY_RIGHT_SUPER));
    rb_define_const(rb_mGLFW, "KEY_MENU", INT2NUM(GLFW_KEY_MENU));
    // Modifier Keys
    rb_define_const(rb_mGLFW, "MOD_CONTROL", INT2NUM(GLFW_MOD_CONTROL));
    rb_define_const(rb_mGLFW, "MOD_SHIFT", INT2NUM(GLFW_MOD_SHIFT));
    rb_define_const(rb_mGLFW, "MOD_ALT", INT2NUM(GLFW_MOD_ALT));
    rb_define_const(rb_mGLFW, "MOD_SUPER", INT2NUM(GLFW_MOD_SUPER));
    // Mouse Buttons
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_1", INT2NUM(GLFW_MOUSE_BUTTON_1));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_2", INT2NUM(GLFW_MOUSE_BUTTON_2));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_3", INT2NUM(GLFW_MOUSE_BUTTON_3));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_4", INT2NUM(GLFW_MOUSE_BUTTON_4));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_5", INT2NUM(GLFW_MOUSE_BUTTON_5));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_6", INT2NUM(GLFW_MOUSE_BUTTON_6));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_7", INT2NUM(GLFW_MOUSE_BUTTON_7));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_8", INT2NUM(GLFW_MOUSE_BUTTON_8));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_LAST", INT2NUM(GLFW_MOUSE_BUTTON_LAST));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_LEFT", INT2NUM(GLFW_MOUSE_BUTTON_LEFT));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_RIGHT", INT2NUM(GLFW_MOUSE_BUTTON_RIGHT));
    rb_define_const(rb_mGLFW, "MOUSE_BUTTON_MIDDLE", INT2NUM(GLFW_MOUSE_BUTTON_MIDDLE));
    // Cursor Shapes
    rb_define_const(rb_mGLFW, "CURSOR_ARROW", INT2NUM(GLFW_ARROW_CURSOR));
    rb_define_const(rb_mGLFW, "CURSOR_IBEAM", INT2NUM(GLFW_IBEAM_CURSOR));
    rb_define_const(rb_mGLFW, "CURSOR_CROSSHAIR", INT2NUM(GLFW_CROSSHAIR_CURSOR));
    rb_define_const(rb_mGLFW, "CURSOR_HAND", INT2NUM(GLFW_HAND_CURSOR));
    rb_define_const(rb_mGLFW, "CURSOR_HRESIZE", INT2NUM(GLFW_HRESIZE_CURSOR));
    rb_define_const(rb_mGLFW, "CURSOR_VRESIZE", INT2NUM(GLFW_VRESIZE_CURSOR));


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rb_glfw_error_callback(int error, const char *message) {
    rb_raise(rb_eGLFWError, message);
} 

void rb_glfw_monitor_callback(GLFWmonitor *monitor, int connected) {
    VALUE m = Data_Wrap_Struct(rb_cGLFWmonitor, NULL, RUBY_DEFAULT_FREE, monitor);
    rb_funcall(rb_mGLFW, rb_intern("monitor_changed"), 2, m, INT2BOOL(connected));
}

VALUE rb_glfw_init(VALUE klass) {
    return glfwInit() ? Qtrue : Qfalse;
}

VALUE rb_glfw_terminate(VALUE klass) {
    glfwTerminate();
    return Qnil;
}

VALUE rb_glfw_poll_events(VALUE klass) {
    glfwPollEvents();
    return Qnil;
}

VALUE rb_glfw_wait_events(VALUE klass) {
    glfwWaitEvents();
    return Qnil;
}

VALUE rb_glfe_event_timeout(VALUE klass, VALUE timeout) {
    glfwWaitEventsTimeout(NUM2DBL(timeout));
    return Qnil;
}

VALUE rb_glfw_get_time(VALUE klass) {
    return DBL2NUM(glfwGetTime());
}

VALUE rb_glfw_set_time(VALUE klass, VALUE t) {
    glfwSetTime(NUM2DBL(t));
    return t;
}

VALUE rb_glfw_swap_interval(VALUE klass, VALUE interval) {
    glfwSwapInterval(NUM2INT(interval));
    return interval;
}

VALUE rb_glfw_current_context(VALUE klass) {
    GLFWwindow *w = glfwGetCurrentContext();
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, w);
}

VALUE rb_glfw_supported_p(VALUE klass, volatile VALUE extension) {
    const char* ext = rb_string_value_cstr(&extension);
    return glfwExtensionSupported(ext) ? Qtrue : Qfalse;
}

VALUE rb_glfw_monitors(VALUE klass) {
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    VALUE ary = rb_ary_new_capa(count);
    for (int i = 0; i < count; i++)
        rb_ary_store(ary, i, Data_Wrap_Struct(rb_cGLFWmonitor, NULL, RUBY_DEFAULT_FREE, monitors[i]));
    return ary;
}

VALUE rb_glfw_load_default_hints(VALUE klass) {
    glfwDefaultWindowHints();
    return Qnil;
}

VALUE rb_glfw_window_hint(VALUE klass, VALUE hint, VALUE value) {
    int hintvalue;
    if (NIL_P(value))
        hintvalue = GLFW_DONT_CARE;
    else if (FIXNUM_P(value))
        hintvalue = NUM2INT(value);
    else
        hintvalue = RTEST(value);
    glfwWindowHint(NUM2INT(hint), hintvalue);

    return Qnil;
}

VALUE rb_glfw_key_name(VALUE klass, VALUE key, VALUE scancode) {
    const char *name = glfwGetKeyName(NUM2INT(key), NUM2INT(scancode));
    return rb_utf8_str_new_cstr(name);
}

VALUE rb_glfw_vulkan_p(VALUE klass) {
    return glfwVulkanSupported() ? Qtrue : Qfalse;
}

VALUE rb_glfw_post_empty(VALUE klass) {
    glfwPostEmptyEvent();
    return Qnil;
}

VALUE rb_glfw_timer_frequency(VALUE klass) {
    return ULL2NUM(glfwGetTimerFrequency());
}

VALUE rb_glfw_timer_value(VALUE klass) {
    return ULL2NUM(glfwGetTimerValue());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Window Class (Instance Methods)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// glfwGetWindowAttrib	// TODO: Any other context hints?


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*	\

glfwSetJoystickCallback	*/

VALUE rb_glfw_joystick_buttons(VALUE klass, VALUE joystick) {
    int count;
    const unsigned char *buttons = glfwGetJoystickButtons(NUM2INT(joystick), &count);
    VALUE ary = rb_ary_new_capa(count);
    for (int i = 0; i < count; i++)
        rb_ary_store(ary, i, INT2NUM(buttons[i]));
    return ary;
}

VALUE rb_glfw_joystick_axes(VALUE klass, VALUE joystick) {
    int count;
    const float *axes = glfwGetJoystickAxes(NUM2INT(joystick), &count);
    VALUE ary = rb_ary_new_capa(count);
    for (int i = 0; i < count; i++)
        rb_ary_store(ary, i, DBL2NUM(axes[i]));
    return ary;
}

VALUE rb_glfw_joystick_name(VALUE klass, VALUE joystick) {
    const char *name = glfwGetJoystickName(NUM2INT(joystick));
    return rb_utf8_str_new_cstr(name);
}

VALUE rb_glfw_joystick_p(VALUE klass, VALUE joystick) {
    return INT2BOOL(glfwJoystickPresent(NUM2INT(joystick)));
}

VALUE rb_glfw_monitor_changed(VALUE klass, VALUE monitor, VALUE connected) {
    return Qnil;
}

/*


glfwGetPhysicalDevicePresentationSupport		
glfwGetProcAddress	
glfwGetRequiredInstanceExtensions			

	
			
glfwGetInstanceProcAddress
glfwGetWGLContext
glfwCreateWindowSurface
glfwGetWin32Adapter	
glfwGetWin32Monitor	
glfwGetWin32Window
glfwGetEGLContext	
glfwGetEGLDisplay	
glfwGetEGLSurface	

*/


