#ifndef GLFW_RB_VIDEOMODE_H
#define GLFW_RB_VIDEOMODE_H 1

#include "common.h"

#define VIDMODE()   \
    GLFWvidmode *v; \
    Data_Get_Struct(self, GLFWvidmode, v)

void Init_glfw_vidmode(VALUE module);
static VALUE rb_glfw_vidmode_alloc(VALUE klass);

VALUE rb_glfw_vidmode_width(VALUE self);
VALUE rb_glfw_vidmode_height(VALUE self);
VALUE rb_glfw_vidmode_red_bits(VALUE self);
VALUE rb_glfw_vidmode_green_bits(VALUE self);
VALUE rb_glfw_vidmode_blue_bits(VALUE self);
VALUE rb_glfw_vidmode_refresh_rate(VALUE self);
VALUE rb_glfw_vidmode_to_s(VALUE self);

#endif /* GLFW_RB_VIDEOMODE_H */