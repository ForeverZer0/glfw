
#include "glfw.h"

VALUE cCursor;

static void rb_glfw_cursor_free(void *cursor)
{
    if (cursor)
        glfwDestroyCursor(cursor);
}

static VALUE rb_glfw_cursor_alloc(VALUE klass)
{
    return Data_Wrap_Struct(klass, NULL, rb_glfw_cursor_free, NULL);
}

static VALUE rb_glfw_cursor_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE img, x, y;
    rb_scan_args(argc, argv, "12", &img, &x, &y);

    GLFWcursor *cursor;

    if (RB_TYPE_P(img, T_DATA))
    {
        GLFWimage *image = DATA_PTR(img);
        int xhot = RTEST(x) ? NUM2INT(x) : 0;
        int yhot = RTEST(y) ? NUM2INT(y) : 0;
        cursor = glfwCreateCursor(image, xhot, yhot);
    }
    else
    {
        int shape = NUM2INT(img);
        cursor = glfwCreateStandardCursor(shape);
    }

    RDATA(self)->data = cursor;
    return Qnil;
}

void rb_glfw_cursor_init(void) {
    cCursor = rb_define_class_under(mGLFW, "Cursor", rb_cObject);

    rb_define_method(cCursor, "initialize", rb_glfw_cursor_initialize, -1);
    rb_define_alloc_func(cCursor, rb_glfw_cursor_alloc);
}