
#include "cursor.h"

VALUE rb_cGLFWcursor;

void Init_glfw_cursor(VALUE module) {
    rb_cGLFWcursor = rb_define_class_under(module, "Cursor", rb_cObject);
    rb_define_alloc_func(rb_cGLFWcursor, rb_glfw_cursor_alloc);
    
    rb_define_method(rb_cGLFWcursor, "initialize", rb_glfw_cursor_initialize, 3);
    rb_define_method(rb_cGLFWcursor, "destroy", rb_glfw_cursor_destroy, 0);

    rb_define_alias(rb_cGLFWcursor, "dispose", "destroy");

    rb_define_singleton_method(rb_cGLFWcursor, "create", rb_glfw_cursor_standard, 1);
}

static VALUE rb_glfw_cursor_alloc(VALUE klass) {
    GLFWcursor *c = ruby_xmalloc(SIZEOF_INTPTR_T);
    memset(c, 0, SIZEOF_INTPTR_T);
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, c);
}

VALUE rb_glfw_cursor_initialize(VALUE self, VALUE image, VALUE xhot, VALUE yhot) {
    GLFWimage *img;
    Data_Get_Struct(image, GLFWimage, img);
    RDATA(self)->data = glfwCreateCursor(img, NUM2INT(xhot), NUM2INT(yhot));
    return Qnil;
}

VALUE rb_glfw_cursor_standard(VALUE klass, VALUE shape) {
    GLFWcursor *cursor = glfwCreateStandardCursor(NUM2INT(shape));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, cursor);
}

VALUE rb_glfw_cursor_destroy(VALUE self) {
    GLFWcursor *cursor;
    Data_Get_Struct(self, GLFWcursor, cursor);

    glfwDestroyCursor(cursor);
    return Qnil;
}
