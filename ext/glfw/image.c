
#include "image.h"

VALUE rb_cGLFWimage;

void Init_glfw_image(VALUE module) {
    rb_cGLFWimage = rb_define_class_under(module, "Image", rb_cObject);
    rb_define_alloc_func(rb_cGLFWimage, rb_glfw_image_alloc);
    
    rb_define_method(rb_cGLFWimage, "width", rb_glfw_image_width, 0);
    rb_define_method(rb_cGLFWimage, "height", rb_glfw_image_height, 0);
    rb_define_method(rb_cGLFWimage, "pixels", rb_glfw_image_pixels, 0);

    rb_define_alias(rb_cGLFWimage, "columns", "width");
    rb_define_alias(rb_cGLFWimage, "rows", "height");
    rb_define_alias(rb_cGLFWimage, "to_blob", "pixels");
}

static VALUE rb_glfw_image_alloc(VALUE klass) {
    GLFWimage *image = ALLOC(GLFWimage);
    memset(image, 0, sizeof(GLFWimage));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, image);
}

VALUE rb_glfw_image_initialize(int argc, VALUE *argv, VALUE self) {
    // TODO: Implement
}

VALUE rb_glfw_image_width(VALUE self) {
    GLFWimage *image;
    Data_Get_Struct(self, GLFWimage, image);
    return INT2NUM(image->width);
}

VALUE rb_glfw_image_height(VALUE self) {
    GLFWimage *image;
    Data_Get_Struct(self, GLFWimage, image);
    return INT2NUM(image->height);
}

VALUE rb_glfw_image_pixels(VALUE self) {
    GLFWimage *image;
    Data_Get_Struct(self, GLFWimage, image);
    int size = image->width * image->height * 4;
    return rb_str_new(image->pixels, size);
}