
#ifndef GLFW_RB_CURSOR_H
#define GLFW_RB_CURSOR_H 1

#include "common.h"
#include "image.h"

void Init_glfw_cursor(VALUE module);
static VALUE rb_glfw_cursor_alloc(VALUE klass);
VALUE rb_glfw_cursor_initialize(VALUE self, VALUE image, VALUE xhot, VALUE yhot);
VALUE rb_glfw_cursor_standard(VALUE klass, VALUE shape);
VALUE rb_glfw_cursor_destroy(VALUE self);

#endif /* GLFW_RB_CURSOR_H */