
#ifndef GLFW_RB_IMAGE_H
#define GLFW_RB_IMAGE_H 1

#include "common.h"

void Init_glfw_image(VALUE module);
static VALUE rb_glfw_image_alloc(VALUE klass);
VALUE rb_glfw_image_initialize(int argc, VALUE *argv, VALUE self);
VALUE rb_glfw_image_width(VALUE self);
VALUE rb_glfw_image_height(VALUE self);
VALUE rb_glfw_image_pixels(VALUE self);

#endif /* GLFW_RB_IMAGE_H */