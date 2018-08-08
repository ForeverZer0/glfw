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
VALUE rb_glfw_load_default_hints(VALUE klass);
VALUE rb_glfw_window_hint(VALUE klass, VALUE hint, VALUE value);
VALUE rb_glfw_key_name(VALUE klass, VALUE key, VALUE scancode);
VALUE rb_glfw_vulkan_p(VALUE klass);
VALUE rb_glfw_post_empty(VALUE klass);
VALUE rb_glfw_timer_frequency(VALUE klass);
VALUE rb_glfw_timer_value(VALUE klass);
VALUE rb_glfw_joystick_p(VALUE klass, VALUE joystick);
VALUE rb_glfw_joystick_name(VALUE klass, VALUE joystick);
VALUE rb_glfw_joystick_axes(VALUE klass, VALUE joystick);
VALUE rb_glfw_joystick_buttons(VALUE klass, VALUE joystick);

#endif /* GLFW_RB_H */
