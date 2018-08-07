
#include "window.h"

VALUE rb_cGLFWwindow;

void Init_glfw_window(VALUE mmodule) {
    rb_cGLFWwindow = rb_define_class_under(rb_mGLFW, "Window", rb_cObject);

    rb_define_alloc_func(rb_cGLFWwindow, rb_glfw_window_alloc);
    rb_define_method(rb_cGLFWwindow, "initialize", rb_glfw_window_initialize, -1);
    rb_define_method(rb_cGLFWwindow, "destroy", rb_glfw_window_destroy, 0);
    rb_define_method(rb_cGLFWwindow, "show", rb_glfw_window_show, 0);
    rb_define_method(rb_cGLFWwindow, "hide", rb_glfw_window_hide, 0);
    rb_define_method(rb_cGLFWwindow, "minimize", rb_glfw_window_minimize, 0);
    rb_define_method(rb_cGLFWwindow, "maximize", rb_glfw_window_maximize, 0);
    rb_define_method(rb_cGLFWwindow, "restore", rb_glfw_window_restore, 0);
    rb_define_method(rb_cGLFWwindow, "focus", rb_glfw_window_focus, 0);
    rb_define_method(rb_cGLFWwindow, "closing?", rb_glfw_window_closing_p, 0);
    rb_define_method(rb_cGLFWwindow, "close", rb_glfw_window_close, -1);

    rb_define_method(rb_cGLFWwindow, "swap_buffers", rb_glfw_window_swap_buffers, 0);
    rb_define_method(rb_cGLFWwindow, "make_current", rb_glfw_window_make_current, 0);
    rb_define_method(rb_cGLFWwindow, "monitor", rb_glfw_window_get_monitor, 0);
    rb_define_method(rb_cGLFWwindow, "set_monitor", rb_glfw_window_set_monitor, -1);

    rb_define_method(rb_cGLFWwindow, "dimensions", rb_glfw_window_dimensions, 0);
    rb_define_method(rb_cGLFWwindow, "position", rb_glfw_window_get_pos, 0);
    rb_define_method(rb_cGLFWwindow, "move", rb_glfw_window_set_pos, 2);
    rb_define_method(rb_cGLFWwindow, "size", rb_glfw_window_get_size, 0);
    rb_define_method(rb_cGLFWwindow, "resize", rb_glfw_window_set_size, 2);
    rb_define_method(rb_cGLFWwindow, "x", rb_glfw_window_get_x, 0);
    rb_define_method(rb_cGLFWwindow, "y", rb_glfw_window_get_y, 0);
    rb_define_method(rb_cGLFWwindow, "width", rb_glfw_window_get_width, 0);
    rb_define_method(rb_cGLFWwindow, "height", rb_glfw_window_get_height, 0);
    rb_define_method(rb_cGLFWwindow, "x=", rb_glfw_window_set_x, 1);
    rb_define_method(rb_cGLFWwindow, "y=", rb_glfw_window_set_y, 1);
    rb_define_method(rb_cGLFWwindow, "width=", rb_glfw_window_set_width, 1);
    rb_define_method(rb_cGLFWwindow, "height=", rb_glfw_window_set_height, 1);

    rb_define_method(rb_cGLFWwindow, "focused?", rb_glfw_window_focused_p, 0);
    rb_define_method(rb_cGLFWwindow, "minimized?", rb_glfw_window_minimized_p, 0);
    rb_define_method(rb_cGLFWwindow, "maximized?", rb_glfw_window_maximized_p, 0);
    rb_define_method(rb_cGLFWwindow, "visible?", rb_glfw_window_visible_p, 0);
    rb_define_method(rb_cGLFWwindow, "resizable?", rb_glfw_window_resizable_p, 0);
    rb_define_method(rb_cGLFWwindow, "decorated?", rb_glfw_window_decorated_p, 0);
    rb_define_method(rb_cGLFWwindow, "topmost?", rb_glfw_window_floating_p, 0);

    rb_define_method(rb_cGLFWwindow, "aspect_ratio", rb_glfw_window_aspect_ratio, 2);
    rb_define_method(rb_cGLFWwindow, "size_limits", rb_glfw_window_limits, 4);

    // Window Alias
    rb_define_alias(rb_cGLFWwindow, "dispose", "destroy");
    rb_define_alias(rb_cGLFWwindow, "iconify", "minimize");
    rb_define_alias(rb_cGLFWwindow, "floating?", "topmost?");
    rb_define_alias(rb_cGLFWwindow, "iconified?", "minimized?");



// glfwGetWindowUserPointer		
// glfwSetWindowUserPointer
}

static VALUE rb_glfw_window_alloc(VALUE klass) {
    GLFWwindow *w = ruby_xmalloc(SIZEOF_INTPTR_T);
    memset(w, 0, SIZEOF_INTPTR_T);
    return WRAP_WINDOW(w);
}

// initialize(width, height, title = '', **options)
VALUE rb_glfw_window_initialize(int argc, VALUE *argv, VALUE self) {
    GLFWmonitor *mon = NULL;
    GLFWwindow *window, *other = NULL;

    VALUE width, height, title, options, monitor, share;

    rb_scan_args(argc, argv, "21:", &width, &height, &title, &options);
    const char *str = NIL_P(title) ? "" : StringValueCStr(title);

    // Option Processing  // TODO: Options
    if (!NIL_P(options))
    {
        // Monitor
        monitor = RTEST(rb_hash_aref(options, STR2SYM("fullscreen"))) ?
            glfwGetPrimaryMonitor() :
            rb_hash_aref(options, STR2SYM("monitor"));
        if (!NIL_P(monitor))
            Data_Get_Struct(monitor, GLFWmonitor, mon);

        // Share
        share = rb_hash_aref(options, STR2SYM("share"));
        if (!NIL_P(share))
            Data_Get_Struct(share, GLFWwindow, other);
    }

    window = glfwCreateWindow(NUM2INT(width), NUM2INT(height), str, mon, other);
    RDATA(self)->data = window;

    return Qnil;
}

VALUE rb_glfw_window_destroy(VALUE self) {
    WINDOW();
    glfwDestroyWindow(w);
    return self;
}

VALUE rb_glfw_window_show(VALUE self) {
    WINDOW();
    glfwShowWindow(w);
    return self;
}

VALUE rb_glfw_window_hide(VALUE self) {
    WINDOW();
    glfwHideWindow(w);
    return self;
}

VALUE rb_glfw_window_minimize(VALUE self) {
    WINDOW();
    glfwIconifyWindow(w);
    return self;
}

VALUE rb_glfw_window_maximize(VALUE self) {
    WINDOW();
    glfwMaximizeWindow(w);
    return self;
}

VALUE rb_glfw_window_restore(VALUE self) {
    WINDOW();
    glfwRestoreWindow(w);
    return self;
}

VALUE rb_glfw_window_focus(VALUE self) {
    WINDOW();
    glfwFocusWindow(w);
    return self;
}

VALUE rb_glfw_window_swap_buffers(VALUE self) {
    WINDOW();
    glfwSwapBuffers(w);
    return Qnil;
}

VALUE rb_glfw_window_make_current(VALUE self) {
    WINDOW();
    glfwMakeContextCurrent(w);
    return Qnil;
}

VALUE rb_glfw_window_dimensions(VALUE self) {
    WINDOW();
    int x, y, width, height;
    glfwGetWindowPos(w, &x, &y);
    glfwGetWindowSize(w, &width, &height);
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, INT2NUM(x));
    rb_ary_store(ary, 1, INT2NUM(y));
    rb_ary_store(ary, 2, INT2NUM(width));
    rb_ary_store(ary, 3, INT2NUM(height));
    return ary;
}

VALUE rb_glfw_window_get_pos(VALUE self) {
    WINDOW();
    int x, y;
    glfwGetWindowPos(*&w, &x, &y);
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(x));
    rb_ary_store(ary, 1, INT2NUM(y));
    return ary;
}

VALUE rb_glfw_window_set_pos(VALUE self, VALUE x, VALUE y) {
    WINDOW();
    glfwSetWindowPos(w, NUM2INT(x), NUM2INT(y));
    return self;
}

VALUE rb_glfw_window_get_size(VALUE self) {
    WINDOW();
    int width, height;
    glfwGetWindowSize(w, &width, &height);
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(width));
    rb_ary_store(ary, 1, INT2NUM(height));
    return ary;
}

VALUE rb_glfw_window_set_size(VALUE self, VALUE width, VALUE height) {
    WINDOW();
    glfwSetWindowSize(w, NUM2INT(width), NUM2INT(height));
    return self;
}

VALUE rb_glfw_window_get_x(VALUE self) {
    WINDOW();
    int x;
    glfwGetWindowPos(w, &x, NULL);
    return INT2NUM(x);
}

VALUE rb_glfw_window_get_y(VALUE self) {
    WINDOW();
    int y;
    glfwGetWindowPos(w, NULL, &y);
    return INT2NUM(y);
}

VALUE rb_glfw_window_set_x(VALUE self, VALUE x) {
    WINDOW();
    int y;
    glfwGetWindowSize(w, NULL, &y);
    glfwSetWindowSize(w, NUM2INT(x), y);
    return x;
}

VALUE rb_glfw_window_set_y(VALUE self, VALUE y) {
    WINDOW();
    int x;
    glfwGetWindowSize(w, &x, NULL);
    glfwSetWindowSize(w, x, NUM2INT(y));
    return y;
}

VALUE rb_glfw_window_get_width(VALUE self) {
    WINDOW();
    int width;
    glfwGetWindowSize(w, &width, NULL);
    return INT2NUM(width);
}

VALUE rb_glfw_window_get_height(VALUE self) {
    WINDOW();
    int height;
    glfwGetWindowSize(w, NULL, &height);
    return INT2NUM(height);
}

VALUE rb_glfw_window_set_width(VALUE self, VALUE width) {
    WINDOW();
    int height;
    glfwGetWindowSize(w, NULL, &height);
    glfwSetWindowSize(w, NUM2INT(width), height);
    return width;
}

VALUE rb_glfw_window_set_height(VALUE self, VALUE height) {
    WINDOW();
    int width;
    glfwGetWindowSize(w, &width, NULL);
    glfwSetWindowSize(w, width, NUM2INT(height));
    return height;
}

VALUE rb_glfw_window_closing_p(VALUE self) {
    WINDOW();
    return glfwWindowShouldClose(w) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_close(int argc, VALUE *argv, VALUE self) {
    WINDOW();
    switch (argc)
    {
        case 0:
            glfwSetWindowShouldClose(w, 1);
            break;
        case 1:
            glfwSetWindowShouldClose(w, RTEST(argv[0]));
            break;
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 1)", argc);
            break;
    }
    return self;
}

VALUE rb_glfw_window_get_monitor(VALUE self) {
    WINDOW();
    GLFWmonitor *monitor = glfwGetWindowMonitor(w);
    return Data_Wrap_Struct(rb_cGLFWmonitor, NULL, RUBY_DEFAULT_FREE, monitor);
}

VALUE rb_glfw_window_set_monitor(int argc, VALUE *argv, VALUE self) {
    WINDOW();
    switch (argc)
    {
        case 2: // monitor, refresh_rate (fullscreen)
        {
            GLFWmonitor *m = NULL;
            Data_Get_Struct(argv[0], GLFWmonitor, m);
            glfwSetWindowMonitor(w, m, 0, 0, 0, 0, NUM2INT(argv[1]));
            break;
        }
        case 4: // x, y, width, height (windowed)
        {
            int mx = NUM2INT(argv[0]), my = NUM2INT(argv[1]), mw = NUM2INT(argv[2]), mh = NUM2INT(argv[3]);
            glfwSetWindowMonitor(w, NULL, mx, my, mw, mh, 0);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2, 4)", argc);
            break;
    }
    return self;
}

VALUE rb_glfw_window_set_title(VALUE self, volatile VALUE title) {
    WINDOW();
    const char* str = rb_string_value_cstr(&title);
    glfwSetWindowTitle(w, str);
    return title;
}

VALUE rb_glfw_window_focused_p(VALUE self) {
    WINDOW();
    return glfwGetWindowAttrib(w, GLFW_FOCUSED) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_minimized_p(VALUE self) {
    WINDOW();
    return glfwGetWindowAttrib(w, GLFW_ICONIFIED) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_maximized_p(VALUE self) {
    WINDOW();
    return glfwGetWindowAttrib(w, GLFW_MAXIMIZED) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_visible_p(VALUE self) {
    WINDOW();
    return glfwGetWindowAttrib(w, GLFW_VISIBLE) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_resizable_p(VALUE self) {
    WINDOW();
    return glfwGetWindowAttrib(w, GLFW_RESIZABLE) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_decorated_p(VALUE self) {
    WINDOW();
    return glfwGetWindowAttrib(w, GLFW_DECORATED) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_floating_p(VALUE self) {
    WINDOW();
    return glfwGetWindowAttrib(w, GLFW_FLOATING) ? Qtrue : Qfalse;
}

VALUE rb_glfw_window_aspect_ratio(VALUE self, VALUE numerator, VALUE denominator) {
    WINDOW();
    glfwSetWindowAspectRatio(w, NUM2INT(numerator), NUM2INT(denominator));
    return Qnil;
}

VALUE rb_glfw_window_limits(VALUE self, VALUE minWidth, VALUE minHeight, VALUE maxWidth, VALUE maxHeight) {
    WINDOW();
    glfwSetWindowSizeLimits(w, NUM2INT(minWidth), NUM2INT(minHeight), NUM2INT(maxWidth), NUM2INT(maxHeight));
    return Qnil;
}




/////////////////////////////////////////////////////////////////////////////
// Callbacks
/////////////////////////////////////////////////////////////////////////////


/*

glfwSetWindowCloseCallback	
glfwSetWindowFocusCallback	
glfwSetWindowIconifyCallback	
glfwSetWindowPosCallback	
glfwSetWindowRefreshCallback	
glfwSetWindowSizeCallback	
glfwSetCharCallback	
glfwSetCharModsCallback	
glfwSetCursorEnterCallback		
glfwSetCursorPosCallback	
glfwSetDropCallback		
glfwSetFramebufferSizeCallback	
glfwSetJoystickCallback	
glfwSetKeyCallback	
glfwSetMonitorCallback	
glfwSetMouseButtonCallback	
glfwSetScrollCallback

*/