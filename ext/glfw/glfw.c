#include "glfw.h"

VALUE mGLFW;
VALUE eGLFWError;

VALUE pointer_class;
VALUE function_class;
VALUE id_new;

#if SIZEOF_VOIDP == SIZEOF_LONG
# define PTR2NUM(x)   (LONG2NUM((long)(x)))
# define NUM2PTR(x)   ((void*)(NUM2ULONG(x)))
#else
/* # error --->> Ruby/DL2 requires sizeof(void*) == sizeof(long) to be compiled. <<--- */
# define PTR2NUM(x)   (LL2NUM((LONG_LONG)(x)))
# define NUM2PTR(x)   ((void*)(NUM2ULL(x)))
#endif

static void rb_glfw_error_cb(int code, const char *message)
{
    rb_raise(eGLFWError, "%s (error code: 0x%08x)", message, code);
}

static VALUE rb_glfw_version(VALUE glfw)
{
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    return rb_sprintf("%d.%d.%d", major, minor, revision);
}

static VALUE rb_glfw_version_str(VALUE glfw)
{
    return rb_str_new_cstr(glfwGetVersionString());
}

static VALUE rb_glfw_init(VALUE glfw)
{
    return RB_BOOL(glfwInit());
}

static VALUE rb_glfw_terminate(VALUE glfw)
{
    glfwTerminate();
    return Qnil;
}

static VALUE rb_glfw_init_hint(VALUE glfw, VALUE hint, VALUE value)
{
    glfwInitHint(NUM2INT(hint), FIXNUM_P(value) ? NUM2INT(value) : RTEST(value));
    return Qnil;
}

static VALUE rb_glfw_swap_interval(VALUE glfw, VALUE value)
{
    glfwSwapInterval(NUM2INT(value));
    return Qnil;
}

static VALUE rb_glfw_poll_events(VALUE glfw)
{
    glfwPollEvents();
    return Qnil;
}

static VALUE rb_glfw_wait_events(VALUE glfw)
{
    glfwWaitEvents();
    return Qnil;
}

static VALUE rb_glfw_get_time(VALUE glfw)
{
    return DBL2NUM(glfwGetTime());
}

static VALUE rb_glfw_set_time(VALUE glfw, VALUE value)
{
    glfwSetTime(NUM2DBL(value));
    return value;
}

static VALUE rb_glfw_timer_value(VALUE glfw)
{
    return ULL2NUM(glfwGetTimerValue());
}

static VALUE rb_glfw_timer_frequency(VALUE glfw)
{
    return ULL2NUM(glfwGetTimerFrequency());
}

static VALUE rb_glfw_post_empty_event(VALUE glfw)
{
    glfwPostEmptyEvent();
    return Qnil;
}

static VALUE rb_glfw_event_timeout(VALUE glfw, VALUE timeout)
{
    glfwWaitEventsTimeout(NUM2DBL(timeout));
    return Qnil;
}

static VALUE rb_glfw_scancode(VALUE glfw, VALUE key)
{
    return INT2NUM(glfwGetKeyScancode(NUM2INT(key)));
}

static VALUE rb_glfw_key_name(int argc, VALUE *argv, VALUE glfw)
{
    VALUE key, scancode;
    rb_scan_args(argc, argv, "11", &key, &scancode);

    int sc = RTEST(scancode) ? NUM2INT(scancode) : 0;
    return rb_str_new_cstr(glfwGetKeyName(NUM2INT(key), sc));
}

static VALUE rb_glfw_get_proc_address(VALUE glfw, VALUE name)
{
    void *proc = glfwGetProcAddress(StringValueCStr(name));
    return rb_funcall(pointer_class, id_new, 1, PTR2NUM(proc));
}

static VALUE rb_glfw_import_function(VALUE glfw, VALUE name, VALUE args, VALUE return_type)
{
    void *proc = glfwGetProcAddress(StringValueCStr(name));
    VALUE handle = rb_funcall(pointer_class, id_new, 1, PTR2NUM(proc));
    return rb_funcall(function_class, id_new, 3, handle, args, return_type);
}

static VALUE rb_glfw_is_extension_supported(VALUE glfw, VALUE name)
{
    const char *ext = StringValueCStr(name);
    return ext ? RB_BOOL(glfwExtensionSupported(ext)) : Qfalse;
}

void Init_glfw(void)
{
    mGLFW = rb_define_module("GLFW");
    eGLFWError = rb_define_class_under(mGLFW, "Error", rb_eStandardError);

    glfwSetErrorCallback(rb_glfw_error_cb);

    rb_define_module_function(mGLFW, "init", rb_glfw_init, 0);
    rb_define_module_function(mGLFW, "terminate", rb_glfw_terminate, 0);
    rb_define_module_function(mGLFW, "version", rb_glfw_version, 0);
    rb_define_module_function(mGLFW, "version_str", rb_glfw_version_str, 0);
    rb_define_module_function(mGLFW, "init_hint", rb_glfw_init_hint, 2);
    rb_define_module_function(mGLFW, "supported?", rb_glfw_is_extension_supported, 1);
    rb_define_module_function(mGLFW, "swap_interval", rb_glfw_swap_interval, 1);
    rb_define_module_function(mGLFW, "poll_events", rb_glfw_poll_events, 0);
    rb_define_module_function(mGLFW, "wait_events", rb_glfw_wait_events, 0);
    rb_define_module_function(mGLFW, "post_empty_event", rb_glfw_post_empty_event, 0);
    rb_define_module_function(mGLFW, "event_timeout", rb_glfw_event_timeout, 1);
    rb_define_module_function(mGLFW, "proc_address", rb_glfw_get_proc_address, 1);
    rb_define_module_function(mGLFW, "import", rb_glfw_import_function, 3);
    rb_define_module_function(mGLFW, "time", rb_glfw_get_time, 0);
    rb_define_module_function(mGLFW, "time=", rb_glfw_set_time, 1);
    rb_define_module_function(mGLFW, "timer_value", rb_glfw_timer_value, 0);
    rb_define_module_function(mGLFW, "timer_frequency", rb_glfw_timer_frequency, 0);
    rb_define_module_function(mGLFW, "key_name", rb_glfw_key_name, -1);
    rb_define_module_function(mGLFW, "scancode", rb_glfw_scancode, 1);

    rb_glfw_window_init();
    rb_glfw_monitor_init();
    rb_glfw_cursor_init();
    rb_glfw_image_init();
    rb_glfw_common_init();
    rb_glfw_joystick_init();;

    rb_require("fiddle");
    VALUE fiddle = rb_const_get(rb_mKernel, rb_intern("Fiddle"));
    pointer_class = rb_const_get(fiddle, rb_intern("Pointer"));
    function_class = rb_const_get(fiddle, rb_intern("Function"));
    id_new = rb_intern("new");
}

