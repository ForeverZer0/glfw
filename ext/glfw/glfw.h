#ifndef GLFW_RB_H
#define GLFW_RB_H 1

#include "common.h"
#include "window.h"
#include "monitor.h"
#include "image.h"
#include "cursor.h"
#include "video_mode.h"

void rb_glfw_error_callback(int error, const char *message);

VALUE rb_glfw_init(VALUE klass);
VALUE rb_glfw_terminate(VALUE klass);
VALUE rb_glfw_poll_events(VALUE klass);
VALUE rb_glfw_wait_events(VALUE klass);
VALUE rb_glfw_get_time(VALUE klass);
VALUE rb_glfw_set_time(VALUE klass, VALUE t);
VALUE rb_glfw_swap_interval(VALUE klass, VALUE interval);
VALUE rb_glfe_event_timeout(VALUE klass, VALUE timeout);
VALUE rb_glfw_current_context(VALUE klass);
VALUE rb_glfw_supported_p(VALUE klass, volatile VALUE extension);
VALUE rb_glfw_monitors(VALUE klass);

#endif /* GLFW_RB_H */
