#include "glfw.h"

VALUE rb_mGLFW;
VALUE rb_eGLFWError;


// TODO: Window class, internal loop timing to reduce overhead 

void Init_glfw(void) {
    glfwSetErrorCallback(rb_glfw_error_callback);

    rb_mGLFW = rb_define_module("GLFW");
    rb_eGLFWError = rb_define_class_under(rb_mGLFW, "GLFWError", rb_eStandardError);

    Init_glfw_window(rb_mGLFW);
    Init_glfw_monitor(rb_mGLFW);
    Init_glfw_vidmode(rb_mGLFW);
    Init_glfw_image(rb_mGLFW);
    Init_glfw_cursor(rb_mGLFW);

    // GLFW Module 
    rb_define_singleton_method(rb_mGLFW, "init", rb_glfw_init, 0);
    rb_define_singleton_method(rb_mGLFW, "terminate", rb_glfw_terminate, 0);
    rb_define_singleton_method(rb_mGLFW, "poll_events", rb_glfw_poll_events, 0);
    rb_define_singleton_method(rb_mGLFW, "wait_events", rb_glfw_wait_events, 0);
    rb_define_singleton_method(rb_mGLFW, "swap_interval", rb_glfw_swap_interval, 1);
    rb_define_singleton_method(rb_mGLFW, "current_context", rb_glfw_current_context, 0);
    rb_define_singleton_method(rb_mGLFW, "supported?", rb_glfw_supported_p, 1);
    rb_define_singleton_method(rb_mGLFW, "time", rb_glfw_get_time, 0);
    rb_define_singleton_method(rb_mGLFW, "time=", rb_glfw_set_time, 1);
    rb_define_singleton_method(rb_mGLFW, "monitors", rb_glfw_monitors, 0);

    // Version Constants
    rb_define_const(rb_mGLFW, "API_VERSION", rb_sprintf("%d.%d.%d", 
         INT2NUM(GLFW_VERSION_MAJOR),  INT2NUM(GLFW_VERSION_MINOR),  INT2NUM(GLFW_VERSION_REVISION)));
    rb_define_const(rb_mGLFW, "API_VERSION_MAJOR", INT2NUM(GLFW_VERSION_MAJOR));
    rb_define_const(rb_mGLFW, "API_VERSION_MINOR", INT2NUM(GLFW_VERSION_MINOR));
    rb_define_const(rb_mGLFW, "API_VERSION_REVISION", INT2NUM(GLFW_VERSION_REVISION));
    rb_define_const(rb_mGLFW, "API_DESCRIPTION", rb_str_new_cstr(glfwGetVersionString()));

    // Callback Constants
    rb_define_const(rb_mGLFW, "CB_MOVED", INT2NUM((int) GLFW_RB_MOVED));
    rb_define_const(rb_mGLFW, "CB_RESIZED", INT2NUM((int) GLFW_RB_RESIZED));
    rb_define_const(rb_mGLFW, "CB_FRAMEBUFFER_RESIZED", INT2NUM((int) GLFW_RB_FRAMEBUFFER_RESIZED));
    rb_define_const(rb_mGLFW, "CB_CLOSING", INT2NUM((int) GLFW_RB_CLOSING));
    rb_define_const(rb_mGLFW, "CB_REFRESHED", INT2NUM((int) GLFW_RB_REFRESHED));
    rb_define_const(rb_mGLFW, "CB_FOCUS_CHANGED", INT2NUM((int) GLFW_RB_FOCUS_CHANGED));
    rb_define_const(rb_mGLFW, "CB_MINIMIZE_CHANGED", INT2NUM((int) GLFW_RB_MINIMIZE_CHANGED));
    rb_define_const(rb_mGLFW, "CB_MOUSE_MOVE", INT2NUM((int) GLFW_RB_MOUSE_MOVE));
    rb_define_const(rb_mGLFW, "CB_MOUSE_SCROLL", INT2NUM((int) GLFW_RB_MOUSE_SCROLL));
    rb_define_const(rb_mGLFW, "CB_MOUSE_BUTTON", INT2NUM((int) GLFW_RB_MOUSE_BUTTON));
    rb_define_const(rb_mGLFW, "CB_MOUSE_ENTER", INT2NUM((int) GLFW_RB_MOUSE_ENTER));
    rb_define_const(rb_mGLFW, "CB_KEY", INT2NUM((int) GLFW_RB_KEY));
    rb_define_const(rb_mGLFW, "CB_CHAR", INT2NUM((int) GLFW_RB_CHAR));
    rb_define_const(rb_mGLFW, "CB_CHAR_MODS", INT2NUM((int) GLFW_RB_CHAR_MODS));
    rb_define_const(rb_mGLFW, "CB_FILE_DROP", INT2NUM((int) GLFW_RB_FILE_DROP));
    rb_define_const(rb_mGLFW, "CB_MONITOR", INT2NUM((int) GLFW_RB_MONITOR));
    rb_define_const(rb_mGLFW, "CB_JOYSTICK", INT2NUM((int) GLFW_RB_JOYSTICK));
}

#ifndef HEADER



#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rb_glfw_error_callback(int error, const char *message) {
    rb_raise(rb_eGLFWError, message);
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Window Class (Instance Methods)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// glfwGetWindowAttrib	// TODO: Any other context hints?


// VALUE rb_glfw_window_
// VALUE rb_glfw_window_
// VALUE rb_glfw_window_
// VALUE rb_glfw_window_
// VALUE rb_glfw_window_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*	\
	
glfwSetWindowIcon	
glfwDefaultWindowHints
glfwWindowHint	
glfwCreateWindowSurface

glfwGetTimerFrequency	
glfwGetTimerValue

glfwSetJoystickCallback		
glfwSetMonitorCallback	
	
glfwCreateCursor	
glfwCreateStandardCursor		
glfwDestroyCursor	
glfwGetClipboardString		
glfwGetCursorPos	
glfwGetEGLContext	
glfwGetEGLDisplay	
glfwGetEGLSurface	
glfwGetFramebufferSize	
glfwGetInputMode	
glfwGetInstanceProcAddress	
glfwGetJoystickAxes	
glfwGetJoystickButtons	
glfwGetJoystickName	
glfwGetKey	
glfwGetKeyName	
glfwGetMouseButton	
glfwGetPhysicalDevicePresentationSupport		
glfwGetProcAddress	
glfwGetRequiredInstanceExtensions	
	
glfwGetVideoMode	
glfwGetVideoModes	

glfwGetWGLContext	
glfwGetWin32Adapter	
glfwGetWin32Monitor	
glfwGetWin32Window		
glfwJoystickPresent		
glfwPostEmptyEvent	
glfwSetClipboardString	
glfwSetCursor	
glfwSetCursorPos			
	
glfwSetInputMode			
glfwVulkanSupported	


*/
