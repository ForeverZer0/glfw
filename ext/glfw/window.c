
#include "glfw.h"

#define CB_WINDOW_RESIZE      (0)
#define CB_FRAMEBUFFER_RESIZE (1)
#define CB_WINDOW_MOVE        (2)
#define CB_WINDOW_CLOSE       (3)
#define CB_WINDOW_REFRESH     (4)
#define CB_WINDOW_FOCUS       (5)
#define CB_WINDOW_MINIMIZE    (6)
#define CB_WINDOW_MAXIMIZE    (7)
#define CB_WINDOW_FILE_DROP   (8)
#define CB_CURSOR_MOVE        (9)
#define CB_SCROLL             (10)
#define CB_KEY                (11)
#define CB_BUTTON             (12)
#define CB_CURSOR_ENTER       (13)
#define CB_CHAR               (14)
#define CB_WINDOW_SCALE       (15)

#define CB_COUNT (16)

#define GET_WINDOW_ATTRIB(name, constant, to_ruby)                     \
    static VALUE name(VALUE self)                                      \
    {                                                                  \
        return to_ruby(glfwGetWindowAttrib(DATA_PTR(self), constant)); \
    }

#define SET_WINDOW_ATTRIB(name, constant, to_c)                     \
    static VALUE name(VALUE self, VALUE value)                      \
    {                                                               \
        glfwSetWindowAttrib(DATA_PTR(self), constant, to_c(value)); \
        return value;                                               \
    }

#define WINDOW_ATTRIBUTE(name, constant, to_ruby, to_c)             \
    GET_WINDOW_ATTRIB(rb_glfw_window_get_##name, constant, to_ruby) \
    SET_WINDOW_ATTRIB(rb_glfw_window_set_##name, constant, to_c)

#define CALLBACK_PROC(name, glfw_callback, index)            \
    static VALUE rb_glfw_window_on_##name(VALUE self)        \
    {                                                        \
        GLFWwindow *window = DATA_PTR(self);                 \
        GLFWruby *data = glfwGetWindowUserPointer(window);   \
        VALUE current = data->procs[index];                  \
        if (rb_block_given_p())                              \
        {                                                    \
            data->procs[index] = rb_block_proc();            \
            glfw_callback(window, rb_glfw_window_cb_##name); \
        }                                                    \
        else                                                 \
        {                                                    \
            data->procs[index] = Qnil;                       \
            glfw_callback(window, NULL);                     \
        }                                                    \
        return RTEST(current) ? current : Qnil;              \
    }

#define WINDOW_INPUT_ATTR(name, constant)                           \
    static VALUE rb_glfw_window_get_##name(VALUE self)              \
    {                                                               \
        return RB_BOOL(glfwGetInputMode(DATA_PTR(self), constant)); \
    }                                                               \
    static VALUE rb_glfw_window_set_##name(VALUE self, VALUE value) \
    {                                                               \
        glfwSetInputMode(DATA_PTR(self), constant, RTEST(value));   \
        return value;                                               \
    }

WINDOW_INPUT_ATTR(sticky_keys, GLFW_STICKY_KEYS)
WINDOW_INPUT_ATTR(sticky_buttons, GLFW_STICKY_MOUSE_BUTTONS)
WINDOW_INPUT_ATTR(lock_modifiers, GLFW_LOCK_KEY_MODS)
WINDOW_INPUT_ATTR(raw_mouse_motion, GLFW_RAW_MOUSE_MOTION)

typedef struct
{
    VALUE window;
    VALUE title;
    VALUE icon;
    VALUE cursor;
    VALUE procs[CB_COUNT];
} GLFWruby;

VALUE cWindow;

static void rb_glfw_window_mark(void *window)
{
    if (window)
    {
        GLFWruby *data = glfwGetWindowUserPointer(window);
        if (data)
        {
            rb_gc_mark(data->window);
            if (RTEST(data->title))
                rb_gc_mark(data->title);
            if (RTEST(data->icon))
                rb_gc_mark(data->icon);
            if (RTEST(data->cursor))
                rb_gc_mark(data->cursor);
            for (int i = 0; i < CB_COUNT; i++)
            {
                if (RTEST(data->procs[i]))
                    rb_gc_mark(data->procs[i]);
            }
        }
    }
}

static void rb_glfw_window_cb_framebuffer_resize(GLFWwindow *window, int width, int height)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_FRAMEBUFFER_RESIZE]))
    {
        rb_proc_call(data->procs[CB_FRAMEBUFFER_RESIZE], rb_ary_new_from_args(2, INT2NUM(width), INT2NUM(height)));
    }
}

static void rb_glfw_window_cb_resize(GLFWwindow *window, int width, int height)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_RESIZE]))
    {
        rb_proc_call(data->procs[CB_WINDOW_RESIZE], rb_ary_new_from_args(2, INT2NUM(width), INT2NUM(height)));
    }
}

static void rb_glfw_window_cb_move(GLFWwindow *window, int x, int y)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_MOVE]))
    {
        rb_proc_call(data->procs[CB_WINDOW_MOVE], rb_ary_new_from_args(2, INT2NUM(x), INT2NUM(y)));
    }
}

static void rb_glfw_window_cb_focus(GLFWwindow *window, int focused)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_FOCUS]))
    {
        rb_proc_call(data->procs[CB_WINDOW_FOCUS], rb_ary_new_from_args(1, RB_BOOL(focused)));
    }
}

static void rb_glfw_window_cb_close(GLFWwindow *window)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_CLOSE]))
    {
        rb_proc_call(data->procs[CB_WINDOW_CLOSE], rb_ary_new());
    }
}

static void rb_glfw_window_cb_refresh(GLFWwindow *window)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_REFRESH]))
    {
        rb_proc_call(data->procs[CB_WINDOW_REFRESH], rb_ary_new());
    }
}

static void rb_glfw_window_cb_minimize(GLFWwindow *window, int minimized)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_MINIMIZE]))
    {
        rb_proc_call(data->procs[CB_WINDOW_MINIMIZE], rb_ary_new_from_args(1, RB_BOOL(minimized)));
    }
}

static void rb_glfw_window_cb_maximize(GLFWwindow *window, int maximized)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_MAXIMIZE]))
    {
        rb_proc_call(data->procs[CB_WINDOW_MAXIMIZE], rb_ary_new_from_args(1, RB_BOOL(maximized)));
    }
}

static void rb_glfw_window_cb_file_drop(GLFWwindow *window, int count, const char **paths)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_FILE_DROP]))
    {
        VALUE ary = rb_ary_new_capa(count);
        for (int i = 0; i < count; i++)
        {
            rb_ary_store(ary, i, rb_str_new_cstr(paths[i]));
        }
        rb_proc_call(data->procs[CB_WINDOW_FILE_DROP], rb_ary_new_from_args(1, ary));
    }
}

static void rb_glfw_window_cb_cursor_move(GLFWwindow *window, double x, double y)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_CURSOR_MOVE]))
    {
        rb_proc_call(data->procs[CB_CURSOR_MOVE], rb_ary_new_from_args(2, DBL2NUM(x), DBL2NUM(y)));
    }
}

static void rb_glfw_window_cb_scroll(GLFWwindow *window, double x, double y)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_SCROLL]))
    {
        rb_proc_call(data->procs[CB_SCROLL], rb_ary_new_from_args(2, DBL2NUM(x), DBL2NUM(y)));
    }
}

static void rb_glfw_window_cb_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_KEY]))
    {
        VALUE args = rb_ary_new_from_args(4, INT2NUM(key), INT2NUM(scancode), INT2NUM(action), INT2NUM(mods));
        rb_proc_call(data->procs[CB_KEY], args);
    }
}

static void rb_glfw_window_cb_mouse_button(GLFWwindow *window, int key, int action, int mods)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_BUTTON]))
    {
        VALUE args = rb_ary_new_from_args(3, INT2NUM(key), INT2NUM(action), INT2NUM(mods));
        rb_proc_call(data->procs[CB_BUTTON], args);
    }
}

static void rb_glfw_window_cb_cursor_enter(GLFWwindow *window, int entered)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_CURSOR_ENTER]))
    {
        rb_proc_call(data->procs[CB_CURSOR_ENTER], rb_ary_new_from_args(1, RB_BOOL(entered)));
    }
}

static void rb_glfw_window_cb_char(GLFWwindow *window, unsigned int codepoint)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_CHAR]))
    {
        rb_proc_call(data->procs[CB_CHAR], rb_ary_new_from_args(1, UINT2NUM(codepoint)));
    }
}

static void rb_glfw_window_cb_scale(GLFWwindow *window, float x, float y)
{
    GLFWruby *data = glfwGetWindowUserPointer(window);
    if (RTEST(data->procs[CB_WINDOW_SCALE]))
    {
        rb_proc_call(data->procs[CB_WINDOW_SCALE], rb_ary_new_from_args(2, DBL2NUM(x), DBL2NUM(y)));
    }
}

CALLBACK_PROC(resize, glfwSetWindowSizeCallback, CB_WINDOW_RESIZE)
CALLBACK_PROC(framebuffer_resize, glfwSetFramebufferSizeCallback, CB_FRAMEBUFFER_RESIZE)
CALLBACK_PROC(move, glfwSetWindowPosCallback, CB_WINDOW_MOVE)
CALLBACK_PROC(focus, glfwSetWindowFocusCallback, CB_WINDOW_FOCUS)
CALLBACK_PROC(close, glfwSetWindowCloseCallback, CB_WINDOW_CLOSE)
CALLBACK_PROC(refresh, glfwSetWindowRefreshCallback, CB_WINDOW_REFRESH)
CALLBACK_PROC(minimize, glfwSetWindowIconifyCallback, CB_WINDOW_MINIMIZE)
CALLBACK_PROC(maximize, glfwSetWindowMaximizeCallback, CB_WINDOW_MAXIMIZE)
CALLBACK_PROC(file_drop, glfwSetDropCallback, CB_WINDOW_FILE_DROP)
CALLBACK_PROC(cursor_move, glfwSetCursorPosCallback, CB_CURSOR_MOVE)
CALLBACK_PROC(scroll, glfwSetScrollCallback, CB_SCROLL)
CALLBACK_PROC(key, glfwSetKeyCallback, CB_KEY)
CALLBACK_PROC(mouse_button, glfwSetMouseButtonCallback, CB_BUTTON)
CALLBACK_PROC(cursor_enter, glfwSetCursorEnterCallback, CB_CURSOR_ENTER)
CALLBACK_PROC(char, glfwSetCharCallback, CB_CHAR)
CALLBACK_PROC(scale, glfwSetWindowContentScaleCallback, CB_WINDOW_SCALE)

static VALUE rb_glfw_window_alloc(VALUE klass)
{
    // GLFW handles allocating/freeing window pointers
    return Data_Wrap_Struct(klass, rb_glfw_window_mark, NULL, NULL);
}

static VALUE rb_glfw_window_default_hints(VALUE glfw)
{
    glfwDefaultWindowHints();
    return Qnil;
}

static VALUE rb_glfw_window_hint(VALUE glfw, VALUE hint, VALUE value)
{
    int h = NUM2INT(hint);

    if (FIXNUM_P(value))
    {
        glfwWindowHint(h, NUM2INT(value));
    }
    else if (RB_TYPE_P(value, T_STRING))
    {
        glfwWindowHintString(h, StringValueCStr(value));
    }
    else
    {
        glfwWindowHint(h, RTEST(value));
    }

    return Qnil;
}

static VALUE rb_glfw_window_eql(VALUE self, VALUE other)
{
    if (CLASS_OF(self) != CLASS_OF(other))
        return Qfalse;

    return RB_BOOL(DATA_PTR(self) == DATA_PTR(other));
}

static VALUE rb_glfw_window_current(VALUE klass)
{
    GLFWwindow *window = glfwGetCurrentContext();
    return window ? Data_Wrap_Struct(klass, NULL, NULL, window) : Qnil;
}

static VALUE rb_glfw_window_make_current(VALUE self)
{
    glfwMakeContextCurrent(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_center(VALUE self)
{
    GLFWwindow *window = DATA_PTR(self);
    GLFWmonitor *monitor = glfwGetWindowMonitor(window);

    // If monitor is not NULL, then window is fullscreen, do nothing.
    if (!monitor)
    {
        monitor = glfwGetPrimaryMonitor();

        int x, y, w, h, width, height;
        glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
        glfwGetWindowSize(window, &width, &height);

        x += ((w - width) / 2);
        y += ((h - height) / 2);
        glfwSetWindowPos(window, x, y);
    }
    return self;
}

static VALUE rb_glfw_window_get_opacity(VALUE self)
{
    return DBL2NUM(glfwGetWindowOpacity(DATA_PTR(self)));
}

static VALUE rb_glfw_window_set_opacity(VALUE self, VALUE value)
{
    glfwSetWindowOpacity(DATA_PTR(self), NUM2FLT(value));
    return value;
}

static VALUE rb_glfw_window_initialize(int argc, VALUE *argv, VALUE self)
{
    if (!glfwInit())
        rb_raise(eGLFWError, "failed to initialize GLFW");

    VALUE w, h, title, opts;
    rb_scan_args(argc, argv, "21:", &w, &h, &title, &opts);

    // Validate width/height
    int width, height;
    width = NUM2INT(w);
    height = NUM2INT(h);
    if (width < 1)
        rb_raise(rb_eArgError, "width must be greater than 0");
    if (height < 1)
        rb_raise(rb_eArgError, "height must be greater than 0");

    GLFWwindow *window = NULL;
    GLFWmonitor *monitor = NULL;
    GLFWwindow *shared = NULL;

    int center = GLFW_TRUE;
    int vsync = GLFW_TRUE;

    if (RTEST(opts))
    {
        VALUE opt = rb_hash_aref(opts, STR2SYM("center"));
        if (opt != Qnil)
            center = opt != Qfalse;

        opt = rb_hash_aref(opts, STR2SYM("vsync"));
        if (opt != Qnil)
            vsync = opt != Qfalse;

        opt = rb_hash_aref(opts, STR2SYM("monitor"));
        if (RTEST(opt))
            monitor = DATA_PTR(opt);

        opt = rb_hash_aref(opts, STR2SYM("shared"));
        if (RTEST(shared))
            shared = DATA_PTR(opt);

        if (RTEST(rb_hash_aref(opts, STR2SYM("full_window"))))
        {
            if (!monitor)
                monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);

            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            width = mode->width;
            height = mode->height;
        }
        else if (RTEST(rb_hash_aref(opts, STR2SYM("fullscreen"))) && !monitor)
        {
            monitor = glfwGetPrimaryMonitor();
        }
    }

    const char *caption = RTEST(title) ? StringValueCStr(title) : "";
    window = glfwCreateWindow(width, height, caption, monitor, shared);
    if (!window)
        rb_raise(eGLFWError, "failed to create OpenGL context");

    GLFWruby *data = ALLOC(GLFWruby);
    memset(data, 0, sizeof(GLFWruby));
    data->window = self;
    data->title = title;
    glfwSetWindowUserPointer(window, data);

    RDATA(self)->data = window;
    glfwMakeContextCurrent(window);

    if (vsync)
        glfwSwapInterval(1);
    if (center)
        rb_glfw_window_center(self);

    if (rb_block_given_p())
    {
        rb_yield(self);
        glfwDestroyWindow(window);
    }

    return Qnil;
}

static VALUE rb_glfw_window_close(int argc, VALUE *argv, VALUE self)
{
    int close = argc > 0 ? RTEST(argv[0]) : GLFW_TRUE;
    glfwSetWindowShouldClose(DATA_PTR(self), close);
    return self;
}

static VALUE rb_glfw_window_closing(VALUE self)
{
    return RB_BOOL(glfwWindowShouldClose(DATA_PTR(self)));
}

static VALUE rb_glfw_window_swap_buffers(VALUE self)
{
    glfwSwapBuffers(DATA_PTR(self));
    return Qnil;
}

static VALUE rb_glfw_window_is_current(VALUE self)
{
    return RB_BOOL(glfwGetCurrentContext() == DATA_PTR(self));
}

static VALUE rb_glfw_window_show(VALUE self)
{
    glfwShowWindow(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_hide(VALUE self)
{
    glfwHideWindow(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_focus(VALUE self)
{
    glfwFocusWindow(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_minimize(VALUE self)
{
    glfwIconifyWindow(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_maximize(VALUE self)
{
    glfwMaximizeWindow(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_restore(VALUE self)
{
    glfwRestoreWindow(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_destroy(VALUE self)
{
    glfwDestroyWindow(DATA_PTR(self));
    return Qnil;
}

static VALUE rb_glfw_window_request_attention(VALUE self)
{
    glfwRequestWindowAttention(DATA_PTR(self));
    return self;
}

static VALUE rb_glfw_window_monitor(VALUE self)
{
    GLFWmonitor *monitor = glfwGetWindowMonitor(DATA_PTR(self));
    return monitor ? Data_Wrap_Struct(cMonitor, NULL, NULL, monitor) : Qnil;
}

static VALUE rb_glfw_window_get_title(VALUE self)
{
    GLFWruby *data = glfwGetWindowUserPointer(DATA_PTR(self));
    return data ? data->title : Qnil;
}

static VALUE rb_glfw_window_set_title(VALUE self, VALUE title)
{
    GLFWwindow *window = DATA_PTR(self);
    GLFWruby *data = glfwGetWindowUserPointer(window);
    data->title = title;
    glfwSetWindowTitle(window, RTEST(title) ? StringValueCStr(title) : "");
    return title;
}

static VALUE rb_glfw_window_framebuffer_size(VALUE self)
{
    int w, h;
    glfwGetFramebufferSize(DATA_PTR(self), &w, &h);
    return rb_glfw_ivec2_create(cSize, w, h);
}

static VALUE rb_glfw_window_get_size(VALUE self)
{
    int w, h;
    glfwGetWindowSize(DATA_PTR(self), &w, &h);
    return rb_glfw_ivec2_create(cSize, w, h);
}

static VALUE rb_glfw_window_set_size(VALUE self, VALUE size)
{
    RBivec2 *v = DATA_PTR(size);
    glfwSetWindowSize(DATA_PTR(self), v->x, v->y);
    return size;
}

static VALUE rb_glfw_window_get_position(VALUE self)
{
    int x, y;
    glfwGetWindowPos(DATA_PTR(self), &x, &y);
    return rb_glfw_ivec2_create(cSize, x, y);
}

static VALUE rb_glfw_window_set_position(VALUE self, VALUE size)
{
    RBivec2 *v = DATA_PTR(size);
    glfwSetWindowPos(DATA_PTR(self), v->x, v->y);
    return size;
}

static VALUE rb_glfw_window_aspect_ratio(VALUE self, VALUE numerator, VALUE denominator)
{
    glfwSetWindowAspectRatio(DATA_PTR(self), NUM2INT(numerator), NUM2INT(denominator));
    return Qnil;
}

static VALUE rb_glfw_window_size_limits(VALUE self, VALUE minimum, VALUE maximum)
{
    RBivec2 *min = DATA_PTR(minimum), *max = DATA_PTR(maximum);
    glfwSetWindowSizeLimits(DATA_PTR(self), min->x, min->y, max->x, max->y);
    return Qnil;
}

static VALUE rb_glfw_window_frame_size(VALUE self)
{
    int left, top, right, bottom;
    glfwGetWindowFrameSize(DATA_PTR(self), &left, &top, &right, &bottom);
    return rb_ary_new_from_args(4, INT2NUM(left), INT2NUM(top), INT2NUM(right), INT2NUM(bottom));
}

static VALUE rb_glfw_window_get_icon(VALUE self)
{
    GLFWruby *data = glfwGetWindowUserPointer(DATA_PTR(self));
    return RTEST(data->icon) ? data->icon : Qnil;
}

static VALUE rb_glfw_window_set_icon(VALUE self, VALUE icon)
{
    GLFWwindow *window = DATA_PTR(self);
    if (!RTEST(icon))
    {
        glfwSetWindowIcon(window, 0, NULL);
    }
    else if (RB_TYPE_P(icon, T_DATA))
    {
        GLFWimage *image = DATA_PTR(icon);
        glfwSetWindowIcon(window, 1, image);
    }
    else // Array
    {
        long len = rb_array_len(icon);
        GLFWimage images[len];
        for (long i = 0; i < len; i++)
        {
            VALUE img = rb_ary_entry(icon, i);
            images[i] = *(GLFWimage *)(DATA_PTR(img));
        }
        glfwSetWindowIcon(window, (int)len, images);
    }

    GLFWruby *data = glfwGetWindowUserPointer(window);
    data->icon = icon;
    return icon;
}

static VALUE rb_glfw_window_get_cursor(VALUE self)
{
    GLFWruby *data = glfwGetWindowUserPointer(DATA_PTR(self));
    return RTEST(data->cursor) ? data->cursor : Qnil;
}

static VALUE rb_glfw_window_set_cursor(VALUE self, VALUE cursor)
{
    GLFWwindow *window = DATA_PTR(self);
    GLFWruby *data = glfwGetWindowUserPointer(window);

    glfwSetCursor(window, DATA_PTR(cursor));
    data->cursor = cursor;

    return cursor;
}

static VALUE rb_glfw_window_content_scale(VALUE self)
{
    float x, y;
    glfwGetWindowContentScale(DATA_PTR(self), &x, &y);
    return rb_glfw_vec2_create(cVec2, x, y);
}

static VALUE rb_glfw_window_get_cursor_pos(VALUE self)
{
    double x, y;
    glfwGetCursorPos(DATA_PTR(self), &x, &y);
    return rb_glfw_vec2_create(cVec2, x, y);
}

static VALUE rb_glfw_window_set_cursor_pos(VALUE self, VALUE position)
{
    RBvec2 *vec = DATA_PTR(position);
    glfwSetCursorPos(DATA_PTR(self), vec->x, vec->y);
    return position;
}

static VALUE rb_glfw_window_cursor_move(VALUE self, VALUE x, VALUE y)
{
    glfwSetCursorPos(DATA_PTR(self), NUM2DBL(x), NUM2DBL(y));
    return Qnil;
}

static VALUE rb_glfw_window_get_clipboard(VALUE self)
{
    const char *str = glfwGetClipboardString(DATA_PTR(self));
    return str ? rb_str_new_cstr(str) : Qnil;
}

static VALUE rb_glfw_window_set_clipboard(VALUE self, VALUE str)
{
    const char *s = RTEST(str) ? StringValueCStr(str) : "";
    glfwSetClipboardString(DATA_PTR(self), s);
    return str;
}

static VALUE rb_glfw_window_change_monitor(VALUE self, VALUE monitor, VALUE position, VALUE size, VALUE hz)
{
    GLFWmonitor *m = RTEST(monitor) ? DATA_PTR(monitor) : NULL;
    RBivec2 *pos = DATA_PTR(position);
    RBivec2 *sz = DATA_PTR(size);

    glfwSetWindowMonitor(DATA_PTR(self), m, pos->x, pos->y, sz->x, sz->y, NUM2INT(hz));
    return Qnil;
}

static VALUE rb_glfw_window_is_key(VALUE self, VALUE key)
{
    return RB_BOOL(glfwGetKey(DATA_PTR(self), NUM2INT(key)));
}

static VALUE rb_glfw_window_is_button(VALUE self, VALUE button)
{
    return RB_BOOL(glfwGetMouseButton(DATA_PTR(self), NUM2INT(button)));
}

static VALUE rb_glfw_window_get_cursor_mode(VALUE self)
{
    return INT2NUM(glfwGetInputMode(DATA_PTR(self), GLFW_CURSOR));
}

static VALUE rb_glfw_window_set_cursor_mode(VALUE self, VALUE mode)
{
    glfwSetInputMode(DATA_PTR(self), GLFW_CURSOR, NUM2INT(mode));
    return mode;
}

static VALUE rb_glfw_window_is_fullscreen(VALUE self)
{
    GLFWmonitor *monitor = glfwGetWindowMonitor(DATA_PTR(self));
    return RB_BOOL(monitor != NULL);
}

WINDOW_ATTRIBUTE(topmost, GLFW_FLOATING, RB_BOOL, RTEST)
WINDOW_ATTRIBUTE(decorated, GLFW_DECORATED, RB_BOOL, RTEST)
WINDOW_ATTRIBUTE(resizable, GLFW_RESIZABLE, RB_BOOL, RTEST)
WINDOW_ATTRIBUTE(auto_focus, GLFW_FOCUS_ON_SHOW, RB_BOOL, RTEST)
WINDOW_ATTRIBUTE(visible, GLFW_VISIBLE, RB_BOOL, RTEST)

GET_WINDOW_ATTRIB(rb_glfw_window_is_focused, GLFW_FOCUSED, RB_BOOL)
GET_WINDOW_ATTRIB(rb_glfw_window_is_minimized, GLFW_ICONIFIED, RB_BOOL)
GET_WINDOW_ATTRIB(rb_glfw_window_is_maximized, GLFW_MAXIMIZED, RB_BOOL)
GET_WINDOW_ATTRIB(rb_glfw_window_is_hovered, GLFW_HOVERED, RB_BOOL)

void rb_glfw_window_init(void)
{

    cWindow = rb_define_class_under(mGLFW, "Window", rb_cObject);
    rb_define_alloc_func(cWindow, rb_glfw_window_alloc);

    rb_define_singleton_method(cWindow, "hint", rb_glfw_window_hint, 2);
    rb_define_singleton_method(cWindow, "default_hints", rb_glfw_window_default_hints, 0);
    rb_define_singleton_method(cWindow, "current", rb_glfw_window_current, 0);

    rb_define_method(cWindow, "initialize", rb_glfw_window_initialize, -1);
    rb_define_method(cWindow, "destroy", rb_glfw_window_destroy, 0);
    rb_define_method(cWindow, "make_current", rb_glfw_window_make_current, 0);
    rb_define_method(cWindow, "current?", rb_glfw_window_is_current, 0);
    rb_define_method(cWindow, "monitor", rb_glfw_window_monitor, 0);
    rb_define_method(cWindow, "content_scale", rb_glfw_window_content_scale, 0);

    rb_define_method(cWindow, "title", rb_glfw_window_get_title, 0);
    rb_define_method(cWindow, "title=", rb_glfw_window_set_title, 1);
    rb_define_method(cWindow, "icon", rb_glfw_window_get_icon, 0);
    rb_define_method(cWindow, "icon=", rb_glfw_window_set_icon, 1);
    rb_define_method(cWindow, "size", rb_glfw_window_get_size, 0);
    rb_define_method(cWindow, "size=", rb_glfw_window_set_size, 1);
    rb_define_method(cWindow, "position", rb_glfw_window_get_position, 0);
    rb_define_method(cWindow, "position=", rb_glfw_window_set_position, 1);
    rb_define_method(cWindow, "cursor", rb_glfw_window_get_cursor, 0);
    rb_define_method(cWindow, "cursor=", rb_glfw_window_set_cursor, 1);
    rb_define_method(cWindow, "cursor_pos", rb_glfw_window_get_cursor_pos, 0);
    rb_define_method(cWindow, "cursor_pos=", rb_glfw_window_set_cursor_pos, 1);
    rb_define_method(cWindow, "opacity", rb_glfw_window_get_opacity, 0);
    rb_define_method(cWindow, "opacity=", rb_glfw_window_set_opacity, 1);
    rb_define_method(cWindow, "topmost", rb_glfw_window_get_topmost, 0);
    rb_define_method(cWindow, "topmost=", rb_glfw_window_set_topmost, 1);
    rb_define_method(cWindow, "decorated", rb_glfw_window_get_decorated, 0);
    rb_define_method(cWindow, "decorated=", rb_glfw_window_set_decorated, 1);
    rb_define_method(cWindow, "resizable", rb_glfw_window_get_resizable, 0);
    rb_define_method(cWindow, "resizable=", rb_glfw_window_set_resizable, 1);
    rb_define_method(cWindow, "auto_focus", rb_glfw_window_get_auto_focus, 0);
    rb_define_method(cWindow, "auto_focus=", rb_glfw_window_set_auto_focus, 1);
    rb_define_method(cWindow, "visible", rb_glfw_window_get_visible, 0);
    rb_define_method(cWindow, "visible=", rb_glfw_window_set_visible, 1);
    rb_define_method(cWindow, "clipboard", rb_glfw_window_get_clipboard, 0);
    rb_define_method(cWindow, "clipboard=", rb_glfw_window_set_clipboard, 1);
    rb_define_method(cWindow, "cursor_mode", rb_glfw_window_get_cursor_mode, 0);
    rb_define_method(cWindow, "cursor_mode=", rb_glfw_window_set_cursor_mode, 1);

    rb_define_method(cWindow, "focused?", rb_glfw_window_is_focused, 0);
    rb_define_method(cWindow, "minimized?", rb_glfw_window_is_minimized, 0);
    rb_define_method(cWindow, "maximized?", rb_glfw_window_is_maximized, 0);
    rb_define_method(cWindow, "hovered?", rb_glfw_window_is_hovered, 0);
    rb_define_method(cWindow, "fullscreen?", rb_glfw_window_is_fullscreen, 0);

    rb_define_method(cWindow, "aspect_ratio", rb_glfw_window_aspect_ratio, 2);
    rb_define_method(cWindow, "size_limits", rb_glfw_window_size_limits, 2);
    rb_define_method(cWindow, "frame_size", rb_glfw_window_frame_size, 0);

    rb_define_method(cWindow, "move_cursor", rb_glfw_window_cursor_move, 2);
    rb_define_method(cWindow, "framebuffer_size", rb_glfw_window_framebuffer_size, 0);
    rb_define_method(cWindow, "center", rb_glfw_window_center, 0);
    rb_define_method(cWindow, "close", rb_glfw_window_close, -1);
    rb_define_method(cWindow, "closing?", rb_glfw_window_closing, 0);
    rb_define_method(cWindow, "swap_buffers", rb_glfw_window_swap_buffers, 0);
    rb_define_method(cWindow, "show", rb_glfw_window_show, 0);
    rb_define_method(cWindow, "hide", rb_glfw_window_hide, 0);
    rb_define_method(cWindow, "focus", rb_glfw_window_focus, 0);
    rb_define_method(cWindow, "minimize", rb_glfw_window_minimize, 0);
    rb_define_method(cWindow, "maximize", rb_glfw_window_maximize, 0);
    rb_define_method(cWindow, "restore", rb_glfw_window_restore, 0);
    rb_define_method(cWindow, "request_attention", rb_glfw_window_request_attention, 0);
    rb_define_method(cWindow, "change_monitor", rb_glfw_window_change_monitor, 4);

    rb_define_method(cWindow, "key?", rb_glfw_window_is_key, 1);
    rb_define_method(cWindow, "mouse_button?", rb_glfw_window_is_button, 1);
    rb_define_method(cWindow, "sticky_keys", rb_glfw_window_get_sticky_keys, 0);
    rb_define_method(cWindow, "sticky_keys=", rb_glfw_window_set_sticky_keys, 1);
    rb_define_method(cWindow, "sticky_buttons", rb_glfw_window_get_sticky_buttons, 0);
    rb_define_method(cWindow, "sticky_buttons=", rb_glfw_window_set_sticky_buttons, 1);
    rb_define_method(cWindow, "lock_modifiers", rb_glfw_window_get_lock_modifiers, 0);
    rb_define_method(cWindow, "lock_modifiers=", rb_glfw_window_set_lock_modifiers, 1);
    rb_define_method(cWindow, "raw_mouse_motion", rb_glfw_window_get_raw_mouse_motion, 0);
    rb_define_method(cWindow, "raw_mouse_motion=", rb_glfw_window_set_raw_mouse_motion, 1);

    rb_define_method(cWindow, "on_framebuffer_resize", rb_glfw_window_on_framebuffer_resize, 0);
    rb_define_method(cWindow, "on_resize", rb_glfw_window_on_resize, 0);
    rb_define_method(cWindow, "on_move", rb_glfw_window_on_move, 0);
    rb_define_method(cWindow, "on_focus", rb_glfw_window_on_focus, 0);
    rb_define_method(cWindow, "on_refresh", rb_glfw_window_on_refresh, 0);
    rb_define_method(cWindow, "on_close", rb_glfw_window_on_close, 0);
    rb_define_method(cWindow, "on_minimize", rb_glfw_window_on_minimize, 0);
    rb_define_method(cWindow, "on_maximize", rb_glfw_window_on_maximize, 0);
    rb_define_method(cWindow, "on_file_drop", rb_glfw_window_on_file_drop, 0);
    rb_define_method(cWindow, "on_cursor_move", rb_glfw_window_on_cursor_move, 0);
    rb_define_method(cWindow, "on_scroll", rb_glfw_window_on_scroll, 0);
    rb_define_method(cWindow, "on_key", rb_glfw_window_on_key, 0);
    rb_define_method(cWindow, "on_mouse_button", rb_glfw_window_on_mouse_button, 0);
    rb_define_method(cWindow, "on_cursor_enter", rb_glfw_window_on_cursor_enter, 0);
    rb_define_method(cWindow, "on_char", rb_glfw_window_on_char, 0);
    rb_define_method(cWindow, "on_scale", rb_glfw_window_on_scale, 0);

    rb_define_method(cWindow, "==", rb_glfw_window_eql, 1);
    rb_define_method(cWindow, "eql?", rb_glfw_window_eql, 1);

    rb_define_alias(cWindow, "dispose", "destroy");
}