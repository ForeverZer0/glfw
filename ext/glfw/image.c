
#include "image.h"

VALUE rb_cGLFWimage;

void Init_glfw_image(VALUE module) {
    rb_cGLFWimage = rb_define_class_under(module, "Image", rb_cObject);
    rb_define_alloc_func(rb_cGLFWimage, rb_glfw_image_alloc);
    rb_define_method(rb_cGLFWimage, "initialize", rb_glfw_image_initialize, -1);
    
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
    if (argc == 2 || argc == 3)
    {
        GLFWimage *image = ALLOC(GLFWimage);
        image->width = NUM2INT(argv[0]);
        image->height = NUM2INT(argv[1]);

        if (argc == 3)
        {
            if (RB_TYPE_P(argv[2], T_STRING))
            {
                image->pixels = StringValuePtr(argv[2]);
            }
            else 
            {
                uint32_t packed = NUM2UINT(argv[2]);
                int size = sizeof(uint32_t) * image->width * image->height;
                image->pixels = malloc(size);
                memset(image->pixels, packed, size);
            }
        }
        else
        {
            int size = 4 * image->width * image->height;
            image->pixels = malloc(size);
            memset(image->pixels, 0, size);
        }
        RDATA(self)->data = image;
        return Qnil;
    }

    rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2, 3)", argc);
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