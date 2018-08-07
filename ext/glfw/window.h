
#ifndef GLFW_RB_WINDOW_H
#define GLFW_RB_WINDOW_H 1

#include "common.h"

#define WIN2VALUE(window) ((VALUE) glfwGetWindowUserPointer(window))


void Init_glfw_window(VALUE mmodule);

static VALUE rb_glfw_window_alloc(VALUE klass);
VALUE rb_glfw_window_initialize(int argc, VALUE *argv, VALUE self);
VALUE rb_glfw_window_destroy(VALUE self);
VALUE rb_glfw_window_show(VALUE self);
VALUE rb_glfw_window_hide(VALUE self);
VALUE rb_glfw_window_minimize(VALUE self);
VALUE rb_glfw_window_maximize(VALUE self);
VALUE rb_glfw_window_restore(VALUE self);
VALUE rb_glfw_window_focus(VALUE self);
VALUE rb_glfw_window_swap_buffers(VALUE self);
VALUE rb_glfw_window_make_current(VALUE self);
VALUE rb_glfw_window_dimensions(VALUE self);
VALUE rb_glfw_window_get_pos(VALUE self);
VALUE rb_glfw_window_set_pos(VALUE self, VALUE x, VALUE y);
VALUE rb_glfw_window_get_size(VALUE self);
VALUE rb_glfw_window_set_size(VALUE self, VALUE width, VALUE height);
VALUE rb_glfw_window_get_x(VALUE self);
VALUE rb_glfw_window_get_y(VALUE self);
VALUE rb_glfw_window_set_x(VALUE self, VALUE x);
VALUE rb_glfw_window_set_y(VALUE self, VALUE y);
VALUE rb_glfw_window_get_width(VALUE self);
VALUE rb_glfw_window_get_height(VALUE self);
VALUE rb_glfw_window_set_width(VALUE self, VALUE width);
VALUE rb_glfw_window_set_height(VALUE self, VALUE height);
VALUE rb_glfw_window_closing_p(VALUE self);
VALUE rb_glfw_window_close(int argc, VALUE *argv, VALUE self);
VALUE rb_glfw_window_get_monitor(VALUE self);
VALUE rb_glfw_window_set_monitor(int argc, VALUE *argv, VALUE self);
VALUE rb_glfw_window_set_title(VALUE self, volatile VALUE title);
VALUE rb_glfw_window_focused_p(VALUE self);
VALUE rb_glfw_window_minimized_p(VALUE self);
VALUE rb_glfw_window_maximized_p(VALUE self);
VALUE rb_glfw_window_visible_p(VALUE self);
VALUE rb_glfw_window_resizable_p(VALUE self);
VALUE rb_glfw_window_decorated_p(VALUE self);
VALUE rb_glfw_window_floating_p(VALUE self);
VALUE rb_glfw_window_aspect_ratio(VALUE self, VALUE numerator, VALUE denominator);
VALUE rb_glfw_window_limits(VALUE self, VALUE minWidth, VALUE minHeight, VALUE maxWidth, VALUE maxHeight);

/////////////////////////////////////////////////////////////////////////////
// Callbacks
/////////////////////////////////////////////////////////////////////////////



#endif /* GLFW_RB_WINDOW_H */