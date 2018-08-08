
#include "video_mode.h"

VALUE rb_cGLFWvidmode;

void Init_glfw_vidmode(VALUE module) {
    rb_cGLFWvidmode = rb_define_class_under(module, "VideoMode", rb_cObject);

    rb_define_method(rb_cGLFWvidmode, "width", rb_glfw_vidmode_width, 0);
    rb_define_method(rb_cGLFWvidmode, "height", rb_glfw_vidmode_height, 0);
    rb_define_method(rb_cGLFWvidmode, "red_bits", rb_glfw_vidmode_red_bits, 0);
    rb_define_method(rb_cGLFWvidmode, "green_bits", rb_glfw_vidmode_green_bits, 0);
    rb_define_method(rb_cGLFWvidmode, "blue_bits", rb_glfw_vidmode_blue_bits, 0);
    rb_define_method(rb_cGLFWvidmode, "refresh_rate", rb_glfw_vidmode_refresh_rate, 0);

    rb_define_method(rb_cGLFWvidmode, "to_s", rb_glfw_vidmode_to_s, 0);
    rb_funcall(rb_cGLFWvidmode, rb_intern("private_class_method"), 1, STR2SYM("new"));
}

static VALUE rb_glfw_vidmode_alloc(VALUE klass) {
    GLFWvidmode *v = ALLOC(GLFWvidmode);
    memset(v, 0, sizeof(GLFWvidmode));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, v);
}

VALUE rb_glfw_vidmode_width(VALUE self) {
    VIDMODE();
    return INT2NUM(v->width);
}

VALUE rb_glfw_vidmode_height(VALUE self) {
    VIDMODE();
    return INT2NUM(v->height);
}

VALUE rb_glfw_vidmode_red_bits(VALUE self) {
    VIDMODE();
    return INT2NUM(v->redBits);
}

VALUE rb_glfw_vidmode_green_bits(VALUE self) {
    VIDMODE();
    return INT2NUM(v->greenBits);
}

VALUE rb_glfw_vidmode_blue_bits(VALUE self) {
    VIDMODE();
    return INT2NUM(v->blueBits);
}

VALUE rb_glfw_vidmode_refresh_rate(VALUE self) {
    VIDMODE();
    return INT2NUM(v->refreshRate);
}

VALUE rb_glfw_vidmode_to_s(VALUE self) {
    VIDMODE();
    return rb_sprintf("<%s: width:%d, height:%d, r:%d, g:%d, b:%d, rate:%dhz", 
        rb_class2name(CLASS_OF(self)), v->width, v->height, v->redBits, v->greenBits, v->blueBits, v->refreshRate);
}
