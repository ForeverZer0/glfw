
#ifndef GLFW_RB_MONITOR_H
#define GLFW_RB_MONITOR_H 1

#include "common.h"
#include "monitor.h"

#define MONITOR() \
    GLFWmonitor *m; \
    Data_Get_Struct(self, GLFWmonitor, m)

void Init_glfw_monitor(VALUE module);
static VALUE rb_glfw_monitor_alloc(VALUE klass);
VALUE rb_glfw_monitor_name(VALUE self);
VALUE rb_glfw_monitor_pos(VALUE self);
VALUE rb_glfw_monitor_size(VALUE self);
VALUE rb_glfw_monitor_x(VALUE self);
VALUE rb_glfw_monitor_y(VALUE self);
VALUE rb_glfw_monitor_width(VALUE self);
VALUE rb_glfw_monitor_height(VALUE self);
VALUE rb_glfw_monitor_dimensions(VALUE self);
VALUE rb_glfw_monitor_get_gamma_ramp(VALUE self);
VALUE rb_glfw_monitor_set_gamma_ramp(int argc, VALUE *argv, VALUE self);
VALUE rb_glfw_monitor_gamma(VALUE self, VALUE exponent);

VALUE rb_glfw_monitor_primary(VALUE klass);

#endif /* GLFW_RB_MONITOR_H */