
#include "vulkan.h"

VALUE rb_cGLFWvulkan;

void Init_glfw_vulkan(VALUE module) {
    rb_cGLFWvulkan = rb_define_class_under(module, "Vulkan", rb_cObject);

    rb_define_method(rb_cGLFWvulkan, "create_surface", rb_glfw_vulkan_create_surface, 2);
    rb_define_method(rb_cGLFWvulkan, "proc_address", rb_glfw_vulkan_proc_address, 1);
    rb_define_method(rb_cGLFWvulkan, "device_support", rb_glfw_vulkan_device_support, 2);

    rb_define_singleton_method(rb_cGLFWvulkan, "supported?", rb_glfw_vulkan_supported, 0);
    rb_define_singleton_method(rb_cGLFWvulkan, "required_extensions", rb_glfw_vulkan_required_ext, 0);

    // TODO: Implement once Vulkan support is better in GLFW
    rb_funcall(rb_cGLFWvulkan, rb_intern("private_class_method"), 1, STR2SYM("new")); 
}



VALUE rb_glfw_vulkan_supported(VALUE klass) {
    return glfwVulkanSupported() ? Qtrue : Qfalse;
}

VALUE rb_glfw_vulkan_required_ext(VALUE klass) {
    uint32_t count;
    const char **exts = glfwGetRequiredInstanceExtensions(&count);
    VALUE ary = rb_ary_new_capa(count);
    for (int i = 0; i < count; i++)
        rb_ary_store(ary, i, rb_str_new_cstr(exts[i]));
    return ary;
}

VALUE rb_glfw_vulkan_create_surface(VALUE self, VALUE window, VALUE allocator) {
    // TODO: glfwCreateWindowSurface
    return Qnil;
}

VALUE rb_glfw_vulkan_proc_address(VALUE self, VALUE name) {
    // TODO: glfwGetInstanceProcAddress
    return Qnil;
}

VALUE rb_glfw_vulkan_device_support(VALUE self, VALUE device, VALUE family) {
    // TODO: glfwGetPhysicalDevicePresentationSupport	
    return Qnil;
}
