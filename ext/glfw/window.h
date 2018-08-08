
#ifndef GLFW_RB_WINDOW_H
#define GLFW_RB_WINDOW_H 1

#include "common.h"

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
VALUE rb_glfw_window_get_framebuffer_size(VALUE self);
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
VALUE  rb_glfw_window_frame_size(VALUE self);
VALUE rb_glfw_window_get_clipboard(VALUE self);
VALUE rb_glfw_window_set_clipboard(VALUE self, VALUE str);
VALUE rb_glfw_window_set_icon(VALUE self, VALUE args);
VALUE rb_glfw_window_get_input_cursor(VALUE self);
VALUE rb_glfw_window_set_input_cursor(VALUE self, VALUE value);
VALUE rb_glfw_window_get_input_sticky_keys(VALUE self);
VALUE rb_glfw_window_set_input_sticky_keys(VALUE self, VALUE value);
VALUE rb_glfw_window_get_input_sticky_mouse(VALUE self);
VALUE rb_glfw_window_set_input_sticky_mouse(VALUE self, VALUE value);
VALUE rb_glfw_window_cursor_pos(VALUE self);
VALUE rb_glfw_window_set_cursor_pos(VALUE self, VALUE x, VALUE y);
VALUE rb_glfw_window_set_cursor(VALUE self, VALUE cursor);
VALUE rb_glfw_window_get_key(VALUE self, VALUE key);
VALUE rb_glfw_window_get_mouse_button(VALUE self, VALUE mbtn);




/////////////////////////////////////////////////////////////////////////////
// Callbacks
/////////////////////////////////////////////////////////////////////////////

VALUE rb_glfw_window_enable_callback(VALUE self, VALUE sym, VALUE enable);
VALUE rb_glfw_window_empty_method(int argc, VALUE *argv, VALUE self);

static void rb_glfw_window_closing(GLFWwindow *window);
static void rb_glfw_window_moved(GLFWwindow *window, int x, int y);
static void rb_glfw_window_resized(GLFWwindow *window, int width, int height);
static void rb_glfw_window_refreshed(GLFWwindow *window);
static void rb_glfw_window_focus_changed(GLFWwindow *window, int focus);
static void rb_glfw_window_minimize_changed(GLFWwindow *window, int minimized);
static void rb_glfw_window_frame_buffer_resized(GLFWwindow *window, int width, int height);
static void rb_glfw_window_cursor_mouse_move(GLFWwindow *window, double x, double y);
static void rb_glfw_window_cursor_mouse_button(GLFWwindow *window, int button, int action, int mods);
static void rb_glfw_window_cursor_mouse_scroll(GLFWwindow *window, double xoffset, double yoffset);
static void rb_glfw_window_key(GLFWwindow *window, int key, int scancode, int action, int mods);
static void rb_glfw_window_char(GLFWwindow *window, unsigned int codepoint);
static void rb_glfw_window_char_mods(GLFWwindow *window, unsigned int codepoint, int mods);
static void rb_glfw_window_file_drop(GLFWwindow *window, int count, const char** files);
static void rb_glfw_window_mouse_enter(GLFWwindow *window, int entered);

#endif /* GLFW_RB_WINDOW_H */