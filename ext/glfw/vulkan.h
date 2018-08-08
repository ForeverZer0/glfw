
#ifndef GLFW_RB_VULKAN_H
#define GLFW_RB_VULKAN_H 1

#include "common.h"

void Init_glfw_vulkan(VALUE module);

VALUE rb_glfw_vulkan_supported(VALUE klass);
VALUE rb_glfw_vulkan_required_ext(VALUE klass);

VALUE rb_glfw_vulkan_create_surface(VALUE self, VALUE window, VALUE allocator);
VALUE rb_glfw_vulkan_proc_address(VALUE self, VALUE name);
VALUE rb_glfw_vulkan_device_support(VALUE self, VALUE device, VALUE family);

#endif /* GLFW_RB_VULKAN_H */