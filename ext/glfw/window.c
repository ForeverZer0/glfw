
#include "window.h"

VALUE rb_cGLFWwindow;

ID id_moved;
ID id_resized;
ID id_framebuffer_resized;
ID id_closing;
ID id_refreshed;
ID id_focus_changed;
ID id_minimize_changed;
ID id_mouse_move;
ID id_mouse_scroll;
ID id_mouse_button;
ID id_mouse_enter;
ID id_key;
ID id_char;
ID id_char_mods;
ID id_file_drop;

#define RB_CALLBACK(id, name) \
    id = rb_intern(name);     \
    rb_define_method_id(rb_cGLFWwindow, id, rb_glfw_window_empty_method, -1)

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
    rb_define_method(rb_cGLFWwindow, "framebuffer_size", rb_glfw_window_get_framebuffer_size, 0);
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
    rb_define_method(rb_cGLFWwindow, "set_icon", rb_glfw_window_set_icon, -2);
    rb_define_method(rb_cGLFWwindow, "enable_callback", rb_glfw_window_enable_callback, 2);

    rb_define_method(rb_cGLFWwindow, "aspect_ratio", rb_glfw_window_aspect_ratio, 2);
    rb_define_method(rb_cGLFWwindow, "size_limits", rb_glfw_window_limits, 4);
    rb_define_method(rb_cGLFWwindow, "frame_size", rb_glfw_window_frame_size, 0);

    rb_define_method(rb_cGLFWwindow, "set_cursor", rb_glfw_window_set_cursor, 1);
    rb_define_method(rb_cGLFWwindow, "cursor_pos", rb_glfw_window_cursor_pos, 0);
    rb_define_method(rb_cGLFWwindow, "set_cursor_pos", rb_glfw_window_set_cursor_pos, 2);
    rb_define_method(rb_cGLFWwindow, "cursor", rb_glfw_window_get_input_cursor, 0);
    rb_define_method(rb_cGLFWwindow, "cursor=", rb_glfw_window_set_input_cursor, 1);
    rb_define_method(rb_cGLFWwindow, "sticky_keys", rb_glfw_window_get_input_sticky_keys, 0);
    rb_define_method(rb_cGLFWwindow, "sticky_keys=", rb_glfw_window_set_input_sticky_keys, 1);
    rb_define_method(rb_cGLFWwindow, "sticky_mouse", rb_glfw_window_get_input_sticky_mouse, 0);
    rb_define_method(rb_cGLFWwindow, "sticky_mouse=", rb_glfw_window_set_input_sticky_mouse, 1);

    rb_define_method(rb_cGLFWwindow, "key_down?", rb_glfw_window_get_key, 1);
    rb_define_method(rb_cGLFWwindow, "mouse_down?", rb_glfw_window_get_mouse_button, 1);

    // Callbacks
    RB_CALLBACK(id_moved, "moved");
    RB_CALLBACK(id_refreshed, "resized");
    RB_CALLBACK(id_framebuffer_resized, "framebuffer_resized");
    RB_CALLBACK(id_closing, "closing");
    RB_CALLBACK(id_refreshed, "refreshed");
    RB_CALLBACK(id_focus_changed, "focus_changed");
    RB_CALLBACK(id_minimize_changed, "minimize_changed");
    RB_CALLBACK(id_mouse_move, "mouse_move");
    RB_CALLBACK(id_mouse_scroll, "mouse_scroll");
    RB_CALLBACK(id_mouse_button, "mouse_button");
    RB_CALLBACK(id_mouse_enter, "mouse_enter");
    RB_CALLBACK(id_key, "key");
    RB_CALLBACK(id_char, "char");
    RB_CALLBACK(id_char_mods, "char_mods");
    RB_CALLBACK(id_file_drop, "file_drop");

    // Alias
    rb_define_alias(rb_cGLFWwindow, "dispose", "destroy");
    rb_define_alias(rb_cGLFWwindow, "iconify", "minimize");
    rb_define_alias(rb_cGLFWwindow, "floating?", "topmost?");
    rb_define_alias(rb_cGLFWwindow, "iconified?", "minimized?");
    rb_define_alias(rb_cGLFWwindow, "iconify_changed", "minimize_changed");
}

static VALUE rb_glfw_window_alloc(VALUE klass) {
    GLFWwindow *w = ruby_xmalloc(SIZEOF_INTPTR_T);
    memset(w, 0, SIZEOF_INTPTR_T);
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, w);
}

// initialize(width, height, title = '', **options)
VALUE rb_glfw_window_initialize(int argc, VALUE *argv, VALUE self) {
    // Initialize GLFW (does nothing and returns immediately if already called)
    glfwInit();

    GLFWmonitor *mon = NULL;
    GLFWwindow *window, *other = NULL;

    VALUE width, height, title, options, monitor, share;

    rb_scan_args(argc, argv, "21:", &width, &height, &title, &options);
    const char *str = NIL_P(title) ? "" : StringValueCStr(title);

    if (!NIL_P(options)) {
        // Monitor
        if (RTEST(rb_hash_aref(options, STR2SYM("fullscreen")))) {
            mon = glfwGetPrimaryMonitor();
        } else {
            monitor = rb_hash_aref(options, STR2SYM("monitor"));
            if (!NIL_P(monitor))
                Data_Get_Struct(monitor, GLFWmonitor, mon);
        }

        // Share
        share = rb_hash_aref(options, STR2SYM("share"));
        if (!NIL_P(share))
            Data_Get_Struct(share, GLFWwindow, other);
    }

    window = glfwCreateWindow(NUM2INT(width), NUM2INT(height), str, mon, other);
    RDATA(self)->data = window;

    // Store the Ruby VALUE as a "user pointer" to get the Ruby instance from the C struct
    glfwSetWindowUserPointer(window, (void *)self);

    if (rb_block_given_p()) {
        rb_yield(self);
        glfwDestroyWindow(window);
    }

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

VALUE rb_glfw_window_get_framebuffer_size(VALUE self) {
    WINDOW();
    int width, height;
    glfwGetFramebufferSize(w, &width, &height);
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(width));
    rb_ary_store(ary, 1, INT2NUM(height));
    return ary;
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
    switch (argc) {
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
    switch (argc) {
        case 2:  // monitor, refresh_rate (fullscreen)
        {
            GLFWmonitor *m = NULL;
            Data_Get_Struct(argv[0], GLFWmonitor, m);
            glfwSetWindowMonitor(w, m, 0, 0, 0, 0, NUM2INT(argv[1]));
            break;
        }
        case 4:  // x, y, width, height (windowed)
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
    const char *str = rb_string_value_cstr(&title);
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

VALUE rb_glfw_window_frame_size(VALUE self) {
    WINDOW();
    int left, top, right, bottom;
    glfwGetWindowFrameSize(w, &left, &top, &right, &bottom);
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, INT2NUM(left));
    rb_ary_store(ary, 1, INT2NUM(top));
    rb_ary_store(ary, 2, INT2NUM(right));
    rb_ary_store(ary, 3, INT2NUM(bottom));
    return ary;
}

VALUE rb_glfw_window_get_clipboard(VALUE self) {
    WINDOW();
    const char *str = glfwGetClipboardString(w);
    return rb_utf8_str_new_cstr(str);
}

VALUE rb_glfw_window_set_clipboard(VALUE self, VALUE str) {
    WINDOW();
    volatile VALUE utf8 = rb_funcall(str, rb_intern("encode"), 1, rb_str_new_cstr("utf-8"));
    glfwSetClipboardString(w, StringValueCStr(utf8));
    return str;
}

VALUE rb_glfw_window_set_icon(VALUE self, VALUE args) {
    WINDOW();
    int argc = rb_array_len(args);
    GLFWimage *images = malloc(sizeof(GLFWimage) * argc);

    for (int i = 0; i < argc; i++) {
        VALUE img = rb_ary_entry(args, i);
        images[i] = *(GLFWimage *)RDATA(img)->data;
    }

    glfwSetWindowIcon(w, argc, images);

    free(images);
    return self;
}

VALUE rb_glfw_window_get_input_cursor(VALUE self) {
    WINDOW();
    return INT2BOOL(glfwGetInputMode(w, GLFW_CURSOR));
}

VALUE rb_glfw_window_set_input_cursor(VALUE self, VALUE value) {
    WINDOW();
    glfwSetInputMode(w, GLFW_CURSOR, RTEST(value));
    return value;
}

VALUE rb_glfw_window_get_input_sticky_keys(VALUE self) {
    WINDOW();
    return INT2BOOL(glfwGetInputMode(w, GLFW_STICKY_KEYS));
}

VALUE rb_glfw_window_set_input_sticky_keys(VALUE self, VALUE value) {
    WINDOW();
    glfwSetInputMode(w, GLFW_STICKY_KEYS, RTEST(value));
    return value;
}

VALUE rb_glfw_window_get_input_sticky_mouse(VALUE self) {
    WINDOW();
    return INT2BOOL(glfwGetInputMode(w, GLFW_STICKY_MOUSE_BUTTONS));
}

VALUE rb_glfw_window_set_input_sticky_mouse(VALUE self, VALUE value) {
    WINDOW();
    glfwSetInputMode(w, GLFW_STICKY_MOUSE_BUTTONS, RTEST(value));
    return value;
}

VALUE rb_glfw_window_cursor_pos(VALUE self) {
    WINDOW();
    double x, y;
    glfwGetCursorPos(w, &x, &y);
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, DBL2NUM(x));
    rb_ary_store(ary, 1, DBL2NUM(y));
    return ary;
}

VALUE rb_glfw_window_set_cursor_pos(VALUE self, VALUE x, VALUE y) {
    WINDOW();
    glfwSetCursorPos(w, NUM2DBL(x), NUM2DBL(y));
    return self;
}

VALUE rb_glfw_window_set_cursor(VALUE self, VALUE cursor) {
    WINDOW();
    GLFWcursor *c;
    Data_Get_Struct(cursor, GLFWcursor, c);
    glfwSetCursor(w, c);
    return self;
}

VALUE rb_glfw_window_get_key(VALUE self, VALUE key) {
    WINDOW();
    return RTEST(glfwGetKey(w, NUM2INT(key)));
}

VALUE rb_glfw_window_get_mouse_button(VALUE self, VALUE mbtn) {
    WINDOW();
    return RTEST(glfwGetMouseButton(w, NUM2INT(mbtn)));
}

/////////////////////////////////////////////////////////////////////////////
// Callbacks
/////////////////////////////////////////////////////////////////////////////

VALUE rb_glfw_window_empty_method(int argc, VALUE *argv, VALUE self) {
    // Empty method stub, as NULL causes segfaults
    return Qnil;
}

VALUE rb_glfw_window_enable_callback(VALUE self, VALUE cbtype, VALUE enable) {
    WINDOW();
    enum GLFW_RB_CALLBACK_TYPE type = NUM2INT(cbtype);
    int state = RTEST(enable);
    switch (type) {
        case GLFW_RB_MOVED:
            glfwSetWindowPosCallback(w, state ? rb_glfw_window_moved : NULL);
            break;
        case GLFW_RB_RESIZED:
            glfwSetWindowSizeCallback(w, state ? rb_glfw_window_resized : NULL);
            break;
        case GLFW_RB_FRAMEBUFFER_RESIZED:
            glfwSetFramebufferSizeCallback(w, state ? rb_glfw_window_frame_buffer_resized : NULL);
            break;
        case GLFW_RB_CLOSING:
            glfwSetWindowCloseCallback(w, state ? rb_glfw_window_closing : NULL);
            break;
        case GLFW_RB_REFRESHED:
            glfwSetWindowRefreshCallback(w, state ? rb_glfw_window_refreshed : NULL);
            break;
        case GLFW_RB_FOCUS_CHANGED:
            glfwSetWindowFocusCallback(w, state ? rb_glfw_window_focus_changed : NULL);
            break;
        case GLFW_RB_MINIMIZE_CHANGED:
            glfwSetWindowIconifyCallback(w, state ? rb_glfw_window_minimize_changed : NULL);
            break;
        case GLFW_RB_MOUSE_MOVE:
            glfwSetCursorPosCallback(w, state ? rb_glfw_window_cursor_mouse_move : NULL);
            break;
        case GLFW_RB_MOUSE_SCROLL:
            glfwSetScrollCallback(w, state ? rb_glfw_window_cursor_mouse_scroll : NULL);
            break;
        case GLFW_RB_MOUSE_BUTTON:
            glfwSetMouseButtonCallback(w, state ? rb_glfw_window_cursor_mouse_button : NULL);
            break;
        case GLFW_RB_MOUSE_ENTER:
            glfwSetCursorEnterCallback(w, state ? rb_glfw_window_mouse_enter : NULL);
            break;
        case GLFW_RB_KEY:
            glfwSetKeyCallback(w, state ? rb_glfw_window_key : NULL);
            break;
        case GLFW_RB_CHAR:
            glfwSetCharCallback(w, state ? rb_glfw_window_char : NULL);
            break;
        case GLFW_RB_CHAR_MODS:
            glfwSetCharModsCallback(w, state ? rb_glfw_window_char_mods : NULL);
            break;
        case GLFW_RB_FILE_DROP:
            glfwSetDropCallback(w, state ? rb_glfw_window_file_drop : NULL);
            break;
        default:
            rb_raise(rb_eArgError, "invalid callback identifier - %d", type);
            break;
    }

    return Qnil;
}

static void rb_glfw_window_closing(GLFWwindow *window) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_closing, 0);
}

static void rb_glfw_window_moved(GLFWwindow *window, int x, int y) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_moved, 2, INT2NUM(x), INT2NUM(y));
}

static void rb_glfw_window_resized(GLFWwindow *window, int width, int height) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_resized, 2, INT2NUM(width), INT2NUM(height));
}

static void rb_glfw_window_refreshed(GLFWwindow *window) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_refreshed, 0);
}

static void rb_glfw_window_focus_changed(GLFWwindow *window, int focused) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_focus_changed, 1, INT2BOOL(focused));
}

static void rb_glfw_window_minimize_changed(GLFWwindow *window, int minimized) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_minimize_changed, 1, INT2BOOL(minimized));
}

static void rb_glfw_window_frame_buffer_resized(GLFWwindow *window, int width, int height) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_framebuffer_resized, 2, INT2NUM(width), INT2NUM(height));
}

static void rb_glfw_window_cursor_mouse_move(GLFWwindow *window, double x, double y) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_mouse_move, 2, DBL2NUM(x), DBL2NUM(y));
}

static void rb_glfw_window_cursor_mouse_button(GLFWwindow *window, int button, int action, int mods) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_mouse_button, 3, INT2NUM(button), INT2NUM(action), INT2NUM(mods));
}

static void rb_glfw_window_cursor_mouse_scroll(GLFWwindow *window, double xoffset, double yoffset) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_mouse_scroll, 2, DBL2NUM(xoffset), DBL2NUM(yoffset));
}

static void rb_glfw_window_mouse_enter(GLFWwindow *window, int entered) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_mouse_enter, 1, INT2BOOL(entered));
}

static void rb_glfw_window_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_key, 4, INT2NUM(key), INT2NUM(scancode), INT2NUM(action), INT2NUM(mods));
}

static void rb_glfw_window_char(GLFWwindow *window, unsigned int codepoint) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_char, 1, UINT2NUM(codepoint));
}

static void rb_glfw_window_char_mods(GLFWwindow *window, unsigned int codepoint, int mods) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w))
        rb_funcall(w, id_char_mods, 2, UINT2NUM(codepoint), INT2NUM(mods));
}

static void rb_glfw_window_file_drop(GLFWwindow *window, int count, const char **files) {
    VALUE w = (VALUE)glfwGetWindowUserPointer(window);
    if (RTEST(w)) {
        VALUE ary = rb_ary_new_capa(count);
        for (int i = 0; i < count; i++) {
            char *pos = strchr(files[i], '\\');
            while (pos) {
                *pos = '/';
                pos = strchr(pos, '\\');
            }
            rb_ary_store(ary, i, rb_utf8_str_new_cstr(files[i]));
        }
        rb_funcall(w, id_file_drop, 1, ary);
    }
}
