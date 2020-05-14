
#include "glfw.h"

#ifdef GLFW_IMAGE_LOADER
#define STBI_MALLOC xmalloc
#define STBI_REALLOC xrealloc
#define STBI_FREE xfree
#define STB_IMAGE_IMPLEMENTATION 1
#include "stb_image.h"
#define ARG_PATTERN "12"
#else
#define ARG_PATTERN "21"
#endif

#define BYTES_PER_PIXEL (4)

VALUE cImage;

static void rb_glfw_image_free(void *image)
{
    GLFWimage *img = image;
    if (img->pixels)
        xfree(img->pixels);
    xfree(img);
}

static VALUE rb_glfw_image_alloc(VALUE klass)
{
    GLFWimage *img = ALLOC(GLFWimage);
    memset(img, 0, sizeof(GLFWimage));
    return Data_Wrap_Struct(klass, NULL, rb_glfw_image_free, img);
}

static VALUE rb_glfw_image_width(VALUE self)
{
    return INT2NUM(((GLFWimage *)DATA_PTR(self))->width);
}

static VALUE rb_glfw_image_height(VALUE self)
{
    return INT2NUM(((GLFWimage *)DATA_PTR(self))->height);
}

static VALUE rb_glfw_image_pixels(VALUE self)
{
    GLFWimage *img = DATA_PTR(self);
    long len = img->width * img->height * BYTES_PER_PIXEL;
    return rb_str_new(img->pixels, len);
}

static VALUE rb_glfw_image_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE w, h, blob;
    rb_scan_args(argc, argv, ARG_PATTERN, &w, &h, &blob);
    GLFWimage *image = DATA_PTR(self);

    switch (argc)
    {
#ifdef GLFW_IMAGE_LOADER
    case 1:
    {
        const char *filename = StringValueCStr(w);
        image->pixels = stbi_load(filename, &image->width, &image->height, NULL, 4);
        break;
    }
#endif
    case 2:
    {
        image->width = NUM2INT(w);
        image->height = NUM2INT(h);
        size_t size = image->width * image->height * BYTES_PER_PIXEL;
        if (size <= 0)
            rb_raise(rb_eArgError, "invalid image size specified");

        image->pixels = xcalloc(size, 1);
        break;
    }
    case 3:
    {
        image->width = NUM2INT(w);
        image->height = NUM2INT(h);
        size_t size = image->width * image->height * BYTES_PER_PIXEL;

        if (size <= 0)
            rb_raise(rb_eArgError, "invalid image size specified");

        image->pixels = xmalloc(size);
        memcpy(image->pixels, StringValuePtr(blob), size);
        break;
    }
    }

    return Qnil;
}

void rb_glfw_image_init(void)
{
    cImage = rb_define_class_under(mGLFW, "Image", rb_cObject);
    rb_define_alloc_func(cImage, rb_glfw_image_alloc);
    rb_define_method(cImage, "initialize", rb_glfw_image_initialize, -1);

    rb_define_method(cImage, "width", rb_glfw_image_width, 0);
    rb_define_method(cImage, "height", rb_glfw_image_height, 0);
    rb_define_method(cImage, "pixels", rb_glfw_image_pixels, 0);

    rb_define_alias(cImage, "columns", "width");
    rb_define_alias(cImage, "rows", "height");
    rb_define_alias(cImage, "to_blob", "pixels");
}